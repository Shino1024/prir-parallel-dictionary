#ifndef PRIR_DICTIONARY_H
#define PRIR_DICTIONARY_H

#include <tuple>
#include <map>
#include <string>

namespace dictionary {
    enum class DictionaryError : uint8_t {
        NoError,
        NonexistentKeyError,
        AlreadyExistingKeyError,
        ParseError,
        OtherError
    };

    enum class DictionaryOperation : uint8_t {
        Insertion,
        Update,
        Removal,
        Search,
        WrongOp
    };

    class Dictionary {
    private:
        void initialize();
        std::map<std::string, std::string> cache{}; // how to divide it for parallel search???

    public:
        Dictionary();
        Dictionary(const dictionary::Dictionary &dictionary);
        // Dictionary(const dictionary::Dictionary &dictionary) = default;
        DictionaryError insert(const std::string &key, const std::string &value);
        DictionaryError update(const std::string &key, const std::string &value);
        DictionaryError remove(const std::string &key);
        std::pair<std::string, DictionaryError> find(const std::string &key);
        void clear();

        const std::map<std::string, std::string> get_cache() const;
    };
}

#endif // PRIR_DICTIONARY_H
