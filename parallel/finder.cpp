#include <utility>
#include <iostream>

#include <omp.h>

#include <parallel/finder.h>

namespace parallel {
    Finder::Finder(dictionary::Dictionary dictionary) : dictionary{dictionary} {
        //
    }

    std::pair<std::string, bool> Finder::parallel_find(const std::string &search_key,
                                                       const unsigned int num_threads) {
        const std::map<std::string, std::string> dictionary_cache = this->dictionary.get_cache();
        std::pair<std::string, bool> search_result{"", false};
        std::map<std::string, std::string>::const_iterator dictionary_iterator = dictionary_cache.begin();
        unsigned int dictionary_index{0};
        omp_set_num_threads(num_threads);
        bool loop_ready{false};
        #pragma omp parallel for shared(search_result) firstprivate(dictionary_cache, dictionary_iterator) private(loop_ready, dictionary_index)
        for (dictionary_index = 0; dictionary_index < dictionary_cache.size(); ++dictionary_index) {
            if (!loop_ready) {
                std::advance(dictionary_iterator, dictionary_index);
                loop_ready = true;
            }
            std::cout << "Thread ID: " << omp_get_thread_num() << ", index: " << dictionary_index << std::endl;
            if (search_key == dictionary_iterator->first) {
                #pragma omp critical
                {
                    search_result = std::make_pair(dictionary_iterator->second, true);
                }
            }
            ++dictionary_iterator;
        }
        
        return search_result;
    }
}
