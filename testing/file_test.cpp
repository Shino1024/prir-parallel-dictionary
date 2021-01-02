#include <string>
#include <iostream>

#include <utils/file.h>

namespace test {
    namespace {
        const std::string mock_file_filename{"mock_data.csv"};
        file::FileReader mock_file_reader{mock_file_filename};
        file::FileWriter mock_file_writer{mock_file_filename};

        bool test_file_read_file() {
            //
        }

        bool test_file_write_file() {
            //
        }
    }

    bool run_all_file_tests() {
        bool test_result{true};

        test_result &= test_file_read_file();
        test_result &= test_file_write_file();
        if (test_result) {
            std::cout << "File tests: OK" << std::endl;
        } else {
            std::cout << "File tests: ERROR" << std::endl;
        }

        return test_result;
    }
}
