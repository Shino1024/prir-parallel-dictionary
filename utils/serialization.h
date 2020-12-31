#ifndef PRIR_SERIALIZATION_H
#define PRIR_SERIALIZATION_H

#include <iostream>
#include <vector>
#include <string>

#include <dictionary/dictionary.h>

namespace serialization {
    constexpr std::string_view InsideSeparator = '\01';
    constexpr std::string_view OutsideSeparator = '\02';

    class DictSerializer {
    private:
        dictionary::Dictionary dictionary{};
        std::string data{};

    public:
        DictSerializer(const dictionary::Dictionary &dictionary);
        bool serialize();
        std::string get_data();
    };

    class DictDeserializer {
    private:
        dictionary::Dictionary dictionary{};
        std::string data{};

        std::vector<std::string> split_string(const std::string &string_to_split,
                                              const std::string &separator);
        
    public:
        DictDeserializer(const std::string &data);
        bool deserialize();
        dictionary::Dictionary get_dictionary();
    };
}

#endif // PRIR_SERIALIZATION_H
