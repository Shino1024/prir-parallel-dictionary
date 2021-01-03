#include <iostream>

#include <dictionary/dictionary.h>

#include <testing/dictionary_test.h>

namespace test {
    dictionary::Dictionary mock_dictionary{};

    bool setup_test_dictionary() {
        mock_dictionary.insert("a", "1");
        mock_dictionary.insert("b", "2");
        mock_dictionary.insert("c", "3");
        mock_dictionary.insert("d", "4");
        mock_dictionary.insert("e", "5");
        mock_dictionary.insert("f", "6");

        return true;
    }

    bool test_dictionary_insertion() {
        const auto insertion_result = mock_dictionary.insert("g", "7");
        std::map<std::string, std::string> dictionary_cache = mock_dictionary.get_cache();
        return dictionary_cache.find("g") != dictionary_cache.end() && insertion_result == dictionary::DictionaryError::NoError;
    }

    bool test_dictionary_update() {
        const auto update_result = mock_dictionary.update("a", "0");
        std::map<std::string, std::string> dictionary_cache = mock_dictionary.get_cache();
        return dictionary_cache.find("a") != dictionary_cache.end() && dictionary_cache["a"] == "0" && update_result == dictionary::DictionaryError::NoError;
    }

    bool test_dictionary_deletion() {
        const auto deletion_result = mock_dictionary.remove("b");
        std::map<std::string, std::string> dictionary_cache = mock_dictionary.get_cache();
        return dictionary_cache.find("b") == dictionary_cache.end() && deletion_result == dictionary::DictionaryError::NoError;
    }

    bool test_dictionary_search() {
        const auto search_result = mock_dictionary.find("c");

        return search_result.first == "3" && search_result.second == dictionary::DictionaryError::NoError;
    }

    bool cleanup_test_dictionary() {
        mock_dictionary.clear();
        return true;
    }

    bool run_all_dictionary_tests() {
        bool test_result{true};

        std::cout << "===============" << std::endl;

        if (setup_test_dictionary()) {
            std::cout << "setup_test_dictionary: OK" << std::endl;
        } else {
            std::cout << "setup_test_dictionary: ERROR" << std::endl;
            test_result = false;
        }

        if (test_dictionary_insertion()) {
            std::cout << "test_dictionary_insertion: OK" << std::endl;
        } else {
            std::cout << "test_dictionary_insertion: ERROR" << std::endl;
            test_result = false;
        }

        if (test_dictionary_update()) {
            std::cout << "test_dictionary_update: OK" << std::endl;
        } else {
            std::cout << "test_dictionary_update: ERROR" << std::endl;
            test_result = false;
        }

        if (test_dictionary_deletion()) {
            std::cout << "test_dictionary_deletion: OK" << std::endl;
        } else {
            std::cout << "test_dictionary_deletion: ERROR" << std::endl;
            test_result = false;
        }

        if (test_dictionary_search()) {
            std::cout << "test_dictionary_search: OK" << std::endl;
        } else {
            std::cout << "test_dictionary_search: ERROR" << std::endl;
            test_result = false;
        }

        if (cleanup_test_dictionary()) {
            std::cout << "cleanup_test_dictionary: OK" << std::endl;
        } else {
            std::cout << "cleanup_test_dictionary: ERROR" << std::endl;
            test_result = false;
        }

        if (test_result) {
            std::cout << "Dictionary tests: OK" << std::endl;
        } else {
            std::cout << "Dictionary tests: ERROR" << std::endl;
        }

        std::cout << "===============" << std::endl;

        return test_result;
    }
}
