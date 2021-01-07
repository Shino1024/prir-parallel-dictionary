#ifndef PRIR_FINDER_H
#define PRIR_FINDER_H

#include <dictionary/dictionary.h>

namespace parallel {
    class Finder {
        public:
        Finder();

        std::pair<std::string, bool> parallel_find(const dictionary::Dictionary &dictionary, const std::string &search_key, const unsigned int num_threads);

        private:
        dictionary::Dictionary dictionary;
    };
}

#endif // PRIR_FINDER_H
