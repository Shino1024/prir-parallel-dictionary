#include <string>
#include <iostream>
#include <fstream>

#include <utils/file.h>

namespace test {
    const std::string mock_file_filename{"mock_data.csv"};
    const std::string mock_file_data{
        "abc;def\n/.,;[]\\{}|\n"
    };
    file::FileReader mock_file_reader{mock_file_filename};
    file::FileWriter mock_file_writer{mock_file_filename};

    bool test_file() {
        mock_file_writer.set_buffer(mock_file_data);
        bool write_file_result = mock_file_writer.write_file();
        bool read_file_result = mock_file_reader.read_file();
        const auto read_data = mock_file_reader.get_buffer();
        return read_data == mock_file_data;
    }

    void cleanup_test_file() {
        std::remove(mock_file_filename.c_str());
    }

    bool run_all_file_tests() {
        bool test_result{true};

        std::cout << "===============" << std::endl;

        if (test_file()) {
            std::cout << "test_file: OK" << std::endl;
        } else {
            std::cout << "test_file: ERROR" << std::endl;
            test_result = false;
        }

        cleanup_test_file();

        if (test_result) {
            std::cout << "File tests: OK" << std::endl;
        } else {
            std::cout << "File tests: ERROR" << std::endl;
        }

        std::cout << "===============" << std::endl;

        return test_result;
    }
}
