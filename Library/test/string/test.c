#include <kk2/core/string.h>

kk2_bool_t test_init() {
    {
        kk2_string_t str = kk2_string_with_cstring(
            kk2_alloc_default(),
            kk2_string_behaviour_default(),
            "H e l l o W o r l d"
        );
        if(kk2_string_is_equal_cstring(&str, "H e l l o W o r l d") == false) {
            return false;
        }
        kk2_string_free(&str);
    }
    return true;
}

kk2_bool_t test_length() {
    {
        kk2_string_t str = kk2_string_with_cstring(
            kk2_alloc_default(),
            kk2_string_behaviour_default(),
            "Hello World"
        );
        if(kk2_string_length(&str) != 11) {
            return false;
        }
        kk2_string_free(&str);
    }
    {
        kk2_string_t str = kk2_string_with_cstring(
            kk2_alloc_default(),
            kk2_string_behaviour_default(),
            "Hello World ©"
        );
        if(kk2_string_length(&str) != 13) {
            return false;
        }
        kk2_string_free(&str);
    }
    return true;
}

kk2_bool_t test_check() {
    {
        kk2_string_t str = kk2_string_with_cstring(
            kk2_alloc_default(),
            kk2_string_behaviour_default(),
            "Hello W o r l d"
        );
        if(kk2_string_is_prefix_cstring(&str, "Hello") == false) {
            return false;
        }
        kk2_string_free(&str);
    }
    {
        kk2_string_t str = kk2_string_with_cstring(
            kk2_alloc_default(),
            kk2_string_behaviour_default(),
            "H e l l o World"
        );
        if(kk2_string_is_suffix_cstring(&str, "World") == false) {
            return false;
        }
        kk2_string_free(&str);
    }
    return true;
}

kk2_bool_t test_insert() {
    {
        kk2_string_t a = kk2_string_with_cstring(
            kk2_alloc_default(),
            kk2_string_behaviour_default(),
            "H e l l o"
        );
        kk2_string_insert_cstring(&a, kk2_string_end_index(&a), " W o r l d"b);
        if(kk2_string_is_equal_cstring(&a, "H e l l o W o r l d") == false) {
            return false;
        }
        kk2_string_free(&a);
        kk2_string_free(&b);
    }
    return true;
}

kk2_bool_t test_remove() {
    {
        kk2_string_t str = kk2_string_with_cstring(
            kk2_alloc_default(),
            kk2_string_behaviour_default(),
            "  H e l l o  W o r l d  "
        );
        if(kk2_string_remove_first_cstring(&str, kk2_string_range(&str), "  ") == false) {
            return false;
        }
        if(kk2_string_is_equal_cstring(&str, "H e l l o  W o r l d  ") == false) {
            return false;
        }
        if(kk2_string_fit(&str) == false) {
            return false;
        }
        kk2_string_free(&str);
    }
    {
        kk2_string_t str = kk2_string_with_cstring(
            kk2_alloc_default(),
            kk2_string_behaviour_default(),
            "  H e l l o  W o r l d  "
        );
        if(kk2_string_remove_last_cstring(&str, kk2_string_range(&str), "  ") == false) {
            return false;
        }
        if(kk2_string_is_equal_cstring(&str, "  H e l l o  W o r l d") == false) {
            return false;
        }
        if(kk2_string_fit(&str) == false) {
            return false;
        }
        kk2_string_free(&str);
    }
    {
        kk2_string_t str = kk2_string_with_cstring(
            kk2_alloc_default(),
            kk2_string_behaviour_default(),
            "  H e l l o   W o r l d  "
        );
        if(kk2_string_remove_cstring(&str, kk2_string_range(&str), "  ") == 0) {
            return false;
        }
        if(kk2_string_is_equal_cstring(&str, "H e l l o W o r l d") == false) {
            return false;
        }
        if(kk2_string_fit(&str) == false) {
            return false;
        }
        kk2_string_free(&str);
    }
    return true;
}

kk2_bool_t test_replace() {
    {
        kk2_string_t str = kk2_string_with_cstring(
            kk2_alloc_default(),
            kk2_string_behaviour_default(),
            " H e l l o  W o r l d "
        );
        if(kk2_string_replace_all_cstring(&str, kk2_string_range(&str), " ", "-") == false) {
            return false;
        }
        if(kk2_string_is_equal_cstring(&str, "-H-e-l-l-o--W-o-r-l-d-") == false) {
            return false;
        }
        if(kk2_string_fit(&str) == false) {
            return false;
        }
        kk2_string_free(&str);
    }
    return true;
}

int main() {
    for(int i = 0; i < 1000000; i++) {
        if(test_init() != true) {
            return EXIT_FAILURE;
        }
        if(test_length() != true) {
            return EXIT_FAILURE;
        }
        if(test_check() != true) {
            return EXIT_FAILURE;
        }
        if(test_insert() != true) {
            return EXIT_FAILURE;
        }
        if(test_remove() != true) {
            return EXIT_FAILURE;
        }
        if(test_replace() != true) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
