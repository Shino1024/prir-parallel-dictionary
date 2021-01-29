#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include <dictionary/dictionary.h>
#include <parallel/finder.h>

#include <utils/benchmark.h>
#include <utils/file.h>
#include <utils/report_creation.h>
#include <utils/serialization.h>
#include <utils/command_line.h>

bool runDictionaryMPIService(dictionary::Dictionary &dictionary);
bool runCommandLineService(dictionary::Dictionary &dictionary);

void printMPICommunicationError(const int mpiError, const dictionary::DictionaryOperation other_rank, const std::string type, const std::string tag);

int dictionaryMPInumtasks, dictionaryMPIrank;

int main(int argc, char *argv[]) {
    dictionary::Dictionary dictionary{};

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &dictionaryMPInumtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &dictionaryMPIrank);
    std::cout << "My rank is " << dictionaryMPIrank << std::endl;
    if (dictionaryMPIrank == 0) {
        runCommandLineService(dictionary);
    } else {
        runDictionaryMPIService(dictionary);
    }

// CommandLine commandLine;

// //performance_reporter.show_time_report();

// commandLine.ProcessUserCommands();

    MPI_Finalize();

}

bool runDictionaryMPIService(dictionary::Dictionary &dictionary) {
    MPI_Status status{};
    int dictionaryMPIcount{}, tag{}, source{};
    char *buffer{};
    dictionary::DictionaryError dictionary_error{dictionary::DictionaryError::NoError};

    while (true) {
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if (status.MPI_ERROR != MPI_SUCCESS) {
            printMPICommunicationError(status.MPI_ERROR, dictionary::DictionaryOperation::WrongOp, "probing", "[all data]");
        }
        dictionaryMPIcount = status._ucount;
        tag = status.MPI_TAG;
        source = status.MPI_SOURCE;
        buffer = new char[dictionaryMPIcount + 1];
        MPI_Recv(buffer, dictionaryMPIcount, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if (status.MPI_ERROR != MPI_SUCCESS) {
            printMPICommunicationError(status.MPI_ERROR, dictionary::DictionaryOperation::WrongOp, "receiving", "[all data]");
        }
        const std::string data{buffer};
        
        switch (tag) {
            case static_cast<int>(dictionary::DictionaryOperation::Insertion): {
                if (std::count(data.begin(), data.end(), *(serialization::InsideSeparator.c_str())) != 1) {
                    std::cout << "The received value:" << std::endl <<
                                 data << std::endl <<
                                 "does not have the required inner separator "
                                 << serialization::InsideSeparator << std::endl;
                                 dictionary_error = dictionary::DictionaryError::ParseError;
                    break;
                }
                const auto pair = serialization::split_string(data, serialization::InsideSeparator);
                if (pair.size() != 2) {
                    std::cout << "String splitting error" << std::endl;
                    dictionary_error = dictionary::DictionaryError::OtherError;
                    break;
                }
                const std::string key = pair[0];
                const std::string value = pair[1];
                if (dictionary.find(key).second != dictionary::DictionaryError::NonexistentKeyError) {
                    std::cout << "Key " << key << " already exists in dictionary" << std::endl;
                    dictionary_error = dictionary::DictionaryError::AlreadyExistingKeyError;
                    break;
                }
                dictionary.insert(key, value);
                break;
            }
            
            case static_cast<int>(dictionary::DictionaryOperation::Update): {
                if (std::count(data.begin(), data.end(), *(serialization::InsideSeparator.c_str())) != 1) {
                    std::cout << "The received value:" << std::endl <<
                                 data << std::endl <<
                                 "does not have the required inner separator "
                                 << serialization::InsideSeparator << std::endl;
                    break;
                }
                const auto pair = serialization::split_string(data, serialization::InsideSeparator);
                if (pair.size() != 2) {
                    std::cout << "String splitting error" << std::endl;
                    break;
                }
                const std::string key = pair[0];
                const std::string value = pair[1];
                if (dictionary.find(key).second != dictionary::DictionaryError::NonexistentKeyError) {
                    std::cout << "Key " << key << " not found in dictionary" << std::endl;
                    dictionary_error = dictionary::DictionaryError::NonexistentKeyError;
                    break;
                }
                dictionary.update(key, value);
                break;
            }
            
            case static_cast<int>(dictionary::DictionaryOperation::Removal): {
                if (std::count(data.begin(), data.end(), *(serialization::InsideSeparator.c_str())) != 0) {
                    std::cout << "The received value:" << std::endl <<
                                 data << std::endl <<
                                 "contains a separator" << serialization::InsideSeparator <<
                                 " and it should not appear in a key" << std::endl;
                    break;
                }
                if (dictionary.find(data).second == dictionary::DictionaryError::NonexistentKeyError) {
                    std::cout << "Key " << data << " not found in dictionary" << std::endl;
                    dictionary_error = dictionary::DictionaryError::NonexistentKeyError;
                    break;
                }
                dictionary.remove(data);
                break;
            }
            
            case static_cast<int>(dictionary::DictionaryOperation::Search): {
                const auto find_result = dictionary.find(data);
                if (find_result.second == dictionary::DictionaryError::NonexistentKeyError) {
                    std::cout << "Key " << data << " not found in dictionary" << std::endl;
                    dictionary_error = dictionary::DictionaryError::NonexistentKeyError;
                    break;
                } else {
                    std::cout << "For key" << std::endl <<
                                data << std::endl <<
                                "there is value" << std::endl <<
                                find_result.first << std::endl;
                    delete[] buffer;
                    buffer = new char[find_result.first.size() + 1];
                    std::memcpy(buffer, find_result.first.c_str(), find_result.first.size() + 1);
                }
                break;
            }
            
            default: {
                break;
            }
        }

        MPI_Send(&dictionary_error, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD);
        if (tag == static_cast<int>(dictionary::DictionaryOperation::Search)) {
            MPI_Send(buffer, std::strlen(buffer) + 1, MPI_CHAR, source, static_cast<int>(dictionary::DictionaryOperation::Search), MPI_COMM_WORLD);
        }

        dictionary_error = dictionary::DictionaryError::NoError;
        delete[] buffer;
        buffer = nullptr;
    }
}

bool runCommandLineService(dictionary::Dictionary &dictionary) {
    while (true) {
        CommandLine commandLine{};
        const auto input = commandLine.ProcessUserCommands();

        unsigned int currentInsertWorkerNum{1};

        char *sendBuffer{};
        sendBuffer = new char[input.second.size() + 1];
        // std::memncpy(sendBuffer, input.second.c_str(), input.second.size());
        char *recvBuffer{};
        int sendSize{0};
        int recvSize{0};
        dictionary::DictionaryError dictionaryError;

        MPI_Status status;

        switch (input.first) {
            case dictionary::DictionaryOperation::Insertion: {
                const auto pair = serialization::split_string(input.second, " ");
                const std::string key = pair[0];
                const std::string value = pair[1];
                std::sprintf(sendBuffer, "%s;%s", key.c_str(), value.c_str());
                sendSize = std::strlen(sendBuffer);

                if (currentInsertWorkerNum == dictionaryMPInumtasks - 1) {
                    currentInsertWorkerNum = 1;
                } else {
                    ++currentInsertWorkerNum;
                }
                std::cout << "putting" << std::endl;
                MPI_Send(sendBuffer, sendSize, MPI_CHAR, currentInsertWorkerNum, static_cast<int>(dictionary::DictionaryOperation::Insertion), MPI_COMM_WORLD);
                std::cout << "sent" << std::endl;

                MPI_Recv(&dictionaryError, 1, MPI_CHAR, currentInsertWorkerNum, static_cast<int>(dictionary::DictionaryOperation::Insertion), MPI_COMM_WORLD, &status);
                if (status.MPI_ERROR != MPI_SUCCESS) {
                    printMPICommunicationError(status.MPI_ERROR, dictionary::DictionaryOperation::Insertion, "receiving", "inserting");
                    continue;
                }

                std::cout << "Insertion of key " << key << " in process rank " << currentInsertWorkerNum << " has been successful" << std::endl;

                break;
            }
            case dictionary::DictionaryOperation::Update: {
                const auto pair = serialization::split_string(input.second, " ");
                const std::string key = pair[0];
                const std::string value = pair[1];
                std::sprintf(sendBuffer, "%s;%s", key.c_str(), value.c_str());
                sendSize = std::strlen(sendBuffer);

                bool updateSuccessful{false};
                for (int other_rank = 1; other_rank < dictionaryMPInumtasks; ++other_rank) {
                    MPI_Send(sendBuffer, sendSize, MPI_CHAR, other_rank, static_cast<int>(dictionary::DictionaryOperation::Update), MPI_COMM_WORLD);
                }
                for (int other_rank = 1; other_rank < dictionaryMPInumtasks; ++other_rank) {
                    MPI_Recv(&dictionaryError, 1, MPI_CHAR, other_rank, static_cast<int>(dictionary::DictionaryOperation::Update), MPI_COMM_WORLD, &status);
                    if (status.MPI_ERROR != MPI_SUCCESS) {
                        printMPICommunicationError(status.MPI_ERROR, dictionary::DictionaryOperation::Update, "receiving", "updating");
                        
                        continue;
                    }

                    if (dictionaryError == dictionary::DictionaryError::NoError) {
                        std::cout << "Process rank " << other_rank << " has been updated successfully with the key " << key << std::endl;
                        updateSuccessful = true;
                    }
                }

                if (!updateSuccessful) {
                    std::cout << "No process has updated the key " << key << std::endl << "Operation failed" << std::endl;
                }

                break;
            }
            case dictionary::DictionaryOperation::Removal: {
                const std::string key = input.second;
                std::sprintf(sendBuffer, "%s", key.c_str());
                sendSize = std::strlen(sendBuffer);

                bool removalSuccessful{false};
                for (int other_rank = 1; other_rank < dictionaryMPInumtasks; ++other_rank) {
                    MPI_Send(sendBuffer, sendSize, MPI_CHAR, other_rank, static_cast<int>(dictionary::DictionaryOperation::Removal), MPI_COMM_WORLD);
                }

                for (int other_rank = 1; other_rank < dictionaryMPInumtasks; ++other_rank) {
                    MPI_Recv(&dictionaryError, 1, MPI_CHAR, other_rank, static_cast<int>(dictionary::DictionaryOperation::Removal), MPI_COMM_WORLD, &status);
                    if (status.MPI_ERROR != MPI_SUCCESS) {
                        printMPICommunicationError(status.MPI_ERROR, dictionary::DictionaryOperation::Removal, "receiving", "removing");
                        continue;
                    }

                    if (dictionaryError == dictionary::DictionaryError::NoError) {
                        std::cout << "Process rank " << other_rank << " has successfully removed the key " << key << std::endl;
                        removalSuccessful = true;
                    }
                }

                if (!removalSuccessful) {
                    std::cout << "No process has removed the key " << key << std::endl << "Operation failed" << std::endl;
                }

                break;
            }
            case dictionary::DictionaryOperation::Search: {
                const std::string key = input.second;
                std::cout << "kurwa key to jest: " << key << std::endl;
                std::sprintf(sendBuffer, "%s", key.c_str());
                std::cout << "kurwa sendBuffer to jest: " << sendBuffer << std::endl;
                sendSize = key.size() + 1;

                bool searchSuccessful{false};
                int processWithKey{0};
                for (int other_rank = 1; other_rank < dictionaryMPInumtasks; ++other_rank) {
                    MPI_Send(sendBuffer, sendSize, MPI_CHAR, other_rank, static_cast<int>(dictionary::DictionaryOperation::Search), MPI_COMM_WORLD);
                }

                for (int other_rank = 1; other_rank < dictionaryMPInumtasks; ++other_rank) {
                    MPI_Recv(&dictionaryError, 1, MPI_CHAR, other_rank, static_cast<int>(dictionary::DictionaryOperation::Search), MPI_COMM_WORLD, &status);
                    if (status.MPI_ERROR != MPI_SUCCESS) {
                        printMPICommunicationError(status.MPI_ERROR, dictionary::DictionaryOperation::Search, "receiving", "searching");

                        continue;
                    }

                    if (dictionaryError == dictionary::DictionaryError::NoError) {
                        std::cout << "Process rank " << other_rank << " has successfully found the key " << key << std::endl;
                        searchSuccessful = true;
                        processWithKey = other_rank;
                    }
                }

                if (!searchSuccessful) {
                    std::cout << "No process has found the key " << key << std::endl << "Operation failed" << std::endl;
                    continue;
                } else {
                    std::cout << "Found in: " << processWithKey << std::endl;
                    MPI_Probe(processWithKey, static_cast<int>(dictionary::DictionaryOperation::Search), MPI_COMM_WORLD, &status);
                    if (status.MPI_ERROR != MPI_SUCCESS) {
                        printMPICommunicationError(status.MPI_ERROR, dictionary::DictionaryOperation::Search, "probing", "searching (2nd step)");

                        continue;
                    }

                    recvBuffer = new char[status._ucount];
                    MPI_Recv(recvBuffer, status._ucount, MPI_CHAR, processWithKey, static_cast<int>(dictionary::DictionaryOperation::Search), MPI_COMM_WORLD, &status);
                    if (status.MPI_ERROR != MPI_SUCCESS) {
                        printMPICommunicationError(status.MPI_ERROR, dictionary::DictionaryOperation::Search, "receiving", "searching (2nd step)");

                        continue;
                    }

                    delete[] recvBuffer;
                    recvBuffer = nullptr;
                }
                
                break;
            }
        }

        delete[] sendBuffer;
        sendBuffer = nullptr;
        delete[] recvBuffer;
        recvBuffer = nullptr;
    }
}

void printMPICommunicationError(const int mpiError, const dictionary::DictionaryOperation other_rank, const std::string type, const std::string tag) {
    char *mpiErrorString;
    int mpiErrorStringLength;
    MPI_Error_string(mpiError, mpiErrorString, &mpiErrorStringLength);
    std::cout << "There has been a problem while " << type << " the " << tag << " response message from the process rank " << static_cast<int>(other_rank) <<
                    ": " << mpiErrorString << std::endl;
}
