#include <vector>
#include <string>
#include <vector>

#include <dictionary/dictionary.h>

#include <utils/serialization.h>

namespace test {
    dictionary::Dictionary setup_serialization_data() {
        dictionary::Dictionary dictionary_deserialized{};

        dictionary_deserialized.insert("aaa", "bbb");
        dictionary_deserialized.insert("ccc", "ddd");
        dictionary_deserialized.insert(",./", "[]|");

        return dictionary_deserialized;
    }

    const dictionary::Dictionary mock_serialization_data{setup_serialization_data()};

    const std::vector<std::string> mock_deserialization_data_vector{
        "aaa;bbb\n",
        "ccc;ddd\n",
        ",./;[]|\n"
    };

    const std::string mock_deserialization_data{
        "aaa;bbb\n"
        "ccc;ddd\n"
        ",./;[]|\n"
    };

    bool test_serialization() {
        serialization::DictSerializer dict_serializer{mock_serialization_data};
        dict_serializer.serialize();
        const std::string serialized_dictionary_data{dict_serializer.get_data()};
        for (const auto string : mock_deserialization_data_vector) {
            if (serialized_dictionary_data.find(string) == std::string::npos) {
                return false;
            }
        }

        return serialized_dictionary_data.size() == mock_deserialization_data.size();
    }
    
    bool test_deserialization() {
        serialization::DictDeserializer mock_dict_deserializer{mock_deserialization_data};

        bool deserialization_result = mock_dict_deserializer.deserialize();
        if (!deserialization_result) {
            return false;
        }

        dictionary::Dictionary deserialized_dictionary{mock_dict_deserializer.get_dictionary()};
        std::map<std::string, std::string> mock_serialization_data_cache{mock_serialization_data.get_cache()};
        for (const auto [key, value] : deserialized_dictionary.get_cache()) {
            if (mock_serialization_data_cache.find(key) != mock_serialization_data_cache.end()) {
                if (mock_serialization_data_cache[key] != value) {
                    return false;
                }
            } else {
                return false;
            }
        }

        return true;
    }

    bool run_all_serialization_tests() {
        bool test_result{true};

        std::cout << "===============" << std::endl;

        if (test_serialization()) {
            std::cout << "test_serialization: OK" << std::endl;
        } else {
            std::cout << "test_serialization: ERROR" << std::endl;
            test_result = false;
        }

        if (test_deserialization()) {
            std::cout << "test_deserialization: OK" << std::endl;
        } else {
            std::cout << "test_deserialization: ERROR" << std::endl;
            test_result = false;
        }

        if (test_result) {
            std::cout << "Serialization tests: OK" << std::endl;
        } else {
            std::cout << "Serialization tests: ERROR" << std::endl;
        }

        std::cout << "===============" << std::endl;

        return test_result;
    }
}
