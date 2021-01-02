#include <vector>
#include <string>

#include <dictionary/dictionary.h>

#include <utils/serialization.h>

namespace test {
    namespace {
        const std::string mock_serialization_data{
            "aaa\01bbb\02"
            "ccc\01ddd\02"
            ",./\01[]|\02"
        };

        dictionary::Dictionary setup_mock_dictionary() {
            dictionary::Dictionary mock_dictionary{};
        }

        dictionary::Dictionary mock_dictionary{setup_mock_dictionary()};
        serialization::DictSerializer mock_dict_serializer{mock_dictionary};

        bool test_serialization_serialize() {
            //
        }

        bool test_serialization_deserialize() {
            //
        }
    }

    bool run_all_serialization_tests() {
        bool test_result{true};
        test_result &= test_serialization_serialize();
        test_result &= test_serialization_deserialize();
        if (test_result) {
            std::cout << "Serialization tests: OK" << std::endl;
        } else {
            std::cout << "Serialization tests: ERROR" << std::endl;
        }
    }
}
