#include <vector>
#include <string>

#include <dictionary/dictionary.h>

namespace test {
    extern const std::string mock_serialization_data;
    extern const std::vector<std::string> mock_deserialization_data_vector;
    extern const dictionary::Dictionary mock_deserialization_data;

    dictionary::Dictionary setup_deserialization_data();

    bool test_serialization();

    bool test_deserialization();

    bool run_all_serialization_tests();
}