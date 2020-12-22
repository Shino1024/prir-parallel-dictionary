#ifndef PRIR_SERIALIZATION_H
#define PRIR_SERIALIZATION_H

#include <iostream>

#include <dictionary/dictionary.h>

namespace serialization {
    class DictSerializer {
        private:
        dictionary::Dictionary dictionary;

        public:
        DictSerializer(const dictionary::Dictionary & dictionary);
    };

    class DictDeserializer {
        private:
        dictionary::Dictionary dictionary;
        
        public:
        DictDeserializer();
    };
}

#endif // PRIR_SERIALIZATION_H
