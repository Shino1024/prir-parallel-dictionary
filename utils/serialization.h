#ifndef PRIR_SERIALIZATION_H
#define PRIR_SERIALIZATION_H

#include <iostream>
#include <vector>
#include <string>

#include <dictionary/dictionary.h>

namespace serialization {
    extern const std::string InsideSeparator;
    extern const std::string OutsideSeparator;

    std::vector<std::string> split_string(const std::string &string_to_split,
                                                 const std::string &separator);

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

    public:
        DictDeserializer(const std::string &data);
        bool deserialize();
        dictionary::Dictionary get_dictionary();
    };
}

#endif // PRIR_SERIALIZATION_H
