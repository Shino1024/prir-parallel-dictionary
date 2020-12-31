#include <algorithm>
#include <string>
#include <vector>

#include "serialization.h"

namespace serialization {
    DictSerializer::DictSerializer(const dictionary::Dictionary &dictionary) : dictionary{dictionary} {
        //
    }

    bool DictSerializer::serialize() {
        std::string draft_data{};

        for (const auto &[key, value] : this->dictionary) {
            if (key.find(InsideSeparator) != std::string::npos) {
                return false;
            }
            if (key.find(OutsideSeparator) != std::string::npos) {
                return false;
            }
            if (value.find(InsideSeparator) != std::string::npos) {
                return false;
            }
            if (value.find(OutsideSeparator) != std::string::npos) {
                return false;
            }
            draft_data += key += InsideSeparator += value += OutsideSeparator;
        }

        this->data = draft_data;

        return true;
    }

    std::string DictSerializer::get_data() {
        return this->data;
    }

    DictDeserializer::DictDeserializer(const std::string &data) : data{data} {
        //
    }

    std::vector<std::string> split_string(const std::string &string_to_split,
                                          const std::string &separator) {
        std::vector<std::string> string_parts{};
        size_t current_position = 0;
        size_t new_position = 0;
        std::string current_token{};
        while ((new_position = string_to_split.find(separator)) != std::string::npos) {
            current_token = string_to_split.substr(current_position, new_position);
            string_parts.push_back(current_token);
            current_position = new_position;
        }
    }

    bool DictDeserializer::deserialize() {
        dictionary::Dictionary draft_dictionary{};
        
        if (this->data.find(OutsideSeparator) == std::string::npos) {
            return false;
        }

        const auto value_pairs = this->split_string(this->data, OutsideSeparator);
        for (const auto &value_pair : value_pairs) {
            if (std::count(value_pair.begin(), value_pair.end(), InsideSeparator) != 1) {
                return false;
            }
            const auto pair = this->split_string(value_pair, InsideSeparator);
            if (pair.size() != 2) {
                return false;
            }
            const auto key = value_pair[0];
            const auto value = value_pair[1];
            draft_dictionary.insert(key, value);
        }

        this->dictionary = draft_dictionary;

        return true;
    }

    dictionary::Dictionary DictDeserializer::get_dictionary() {
        return this->dictionary;
    }
}
