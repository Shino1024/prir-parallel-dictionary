#include <tuple>

#include <dictionary/dictionary.h>

namespace dictionary {
    void Dictionary::initialize() {
        //
    }

    Dictionary::Dictionary() {
        //
    }

    DictionaryError Dictionary::insert(const std::string &key, const std::string &value) {
        if (this->cache.find(key) != this->cache.end()) {
            return DictionaryError::AlreadyExistingKeyError;
        }

        this->cache.insert({key, value});

        return DictionaryError::NoError;
    }

    DictionaryError Dictionary::update(const std::string &key, const std::string &value) {
        if (this->cache.find(key) == this->cache.end()) {
            return DictionaryError::NonexistentKeyError;
        }

        this->cache[key] = value;

        return DictionaryError::NoError;
    }

    DictionaryError Dictionary::remove(const std::string &key) {
        if (this->cache.find(key) == this->cache.end()) {
            return DictionaryError::NonexistentKeyError;
        }

        this->cache.erase(key);

        return DictionaryError::NoError;
    }

    std::pair<std::string, DictionaryError> Dictionary::find(const std::string &key) {
        if (this->cache.find(key) == this->cache.end()) {
            return std::make_pair("", DictionaryError::NonexistentKeyError);
        }

        return std::make_pair((*this->cache.find(key)).second, DictionaryError::NoError);
    }

    void Dictionary::clear() {
        this->cache.clear();
    }

    const std::map<std::string, std::string> & Dictionary::get_cache() const {
        return this->cache;
    }
}
