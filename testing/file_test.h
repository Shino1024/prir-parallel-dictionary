#include <string>

#include <utils/file.h>

namespace test {
    extern const std::string mock_file_filename;
    extern file::FileReader mock_file_reader;
    extern file::FileWriter mock_file_writer;

    bool test_file();

    void cleanup_test_file();

    bool run_all_file_tests();
}
