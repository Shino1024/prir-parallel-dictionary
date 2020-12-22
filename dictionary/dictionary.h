#ifndef PRIR_DICTIONARY
#define PRIR_DICTIONARY

#include <map>
#include <string>
#include <iostream>

namespace dictionary {
    class Dictionary {
        public:
        Dictionary();

        private:
        void initialize();
        std::map<std::string, std::string> cache;
    };
}

#endif // PRIR_DICTIONARY
