#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "serialization.h"

namespace serialization {
    const std::string InsideSeparator{";"};
    const std::string OutsideSeparator{"\n"};

    DictSerializer::DictSerializer(const dictionary::Dictionary &dictionary) : dictionary{dictionary} {
        //
    }

    bool DictSerializer::serialize() {
        std::string draft_data{};

        for (const auto &[key, value] : this->dictionary.get_cache()) {
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
            draft_data += (key + InsideSeparator + value + OutsideSeparator);
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

    std::vector<std::string> DictDeserializer::split_string(const std::string &string_to_split,
                                                            const std::string &separator) {
        std::vector<std::string> string_parts{};

        std::stringstream stream{string_to_split};
        std::string buffer{};
        if (string_to_split.find(separator) == std::string::npos) {
            return string_parts;
        }
        while (std::getline(stream, buffer, *(separator.c_str()))) {
            if (buffer == "") {
                break;
            }
            string_parts.push_back(buffer);
        }

        return string_parts;
    }

    bool DictDeserializer::deserialize() {
        dictionary::Dictionary draft_dictionary{};
        
        if (this->data.find(OutsideSeparator) == std::string::npos) {
            return false;
        }

        const auto value_pairs = this->split_string(this->data, OutsideSeparator);
        for (const auto &value_pair : value_pairs) {
            if (value_pair == "") {
                break;
            }
            if (std::count(value_pair.begin(), value_pair.end(), *InsideSeparator.c_str()) != 1) {
                return false;
            }
            const auto pair = this->split_string(value_pair, InsideSeparator);
            if (pair.size() != 2) {
                return false;
            }
            const auto key = pair[0];
            const auto value = pair[1];
            draft_dictionary.insert(key, value);
        }

        this->dictionary = draft_dictionary;

        return true;
    }

    dictionary::Dictionary DictDeserializer::get_dictionary() {
        return this->dictionary;
    }
}
