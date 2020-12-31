#ifndef PRIR_DICTIONARY_H
#define PRIR_DICTIONARY_H

#include <map>
#include <string>

namespace dictionary {
    namespace {
        enum class DictionaryErrorEnum : uint8_t {
            NoError,
            NonexistentKeyError,
            AlreadyExistingKeyError,
        };
    }

    class DictionaryError {
    public:
        //
    private:
        //
    };

    class Dictionary {
    public:
        Dictionary();
        DictionaryError insert(const std::string &key, const std::string &value);
        DictionaryError update(const std::string &key, const std::string &value);
        DictionaryError remove(const std::string &key);
        void clear();

    private:
        void initialize();
        std::map<std::string, std::string> cache; // how to divide it for parallel search???
    };
}

#endif // PRIR_DICTIONARY_H
