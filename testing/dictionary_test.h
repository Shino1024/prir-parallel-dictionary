#include <dictionary/dictionary.h>

namespace test {
    extern dictionary::Dictionary mock_dictionary;

    bool setup_test_dictionary();

    bool test_dictionary_insertion();

    bool test_dictionary_update();
    
    bool test_dictionary_deletion();

    bool test_dictionary_search();

    bool cleanup_test_dictionary();

    bool run_all_dictionary_tests();
}