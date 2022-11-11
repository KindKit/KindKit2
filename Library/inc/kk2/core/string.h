#ifndef KK2_CORE_STRING_H
#define KK2_CORE_STRING_H

#include <kk2/core/alloc.h>
#include <kk2/core/memory.h>
#include <kk2/core/range_index.h>
#include <kk2/core/string_encoding.h>
#include <kk2/core/string_behaviour.h>
#include <kk2/core/string_scalar.h>
#include <kk2/core/string_view.h>

KK2_OBJ_BEGIN(kk2_string)
    KK2_OBJ_FIELD(alloc, kk2_alloc_t)
    KK2_OBJ_FIELD(behaviour, kk2_string_behaviour_t)
    KK2_OBJ_FIELD(encoding, kk2_string_encoding_t)
    KK2_OBJ_FIELD(range, kk2_range_index_t)
    KK2_OBJ_FIELD(capacity, kk2_size_t)
    KK2_OBJ_UNION_BEGIN()
        KK2_OBJ_FIELD(builtin, kk2_string_builtin_t)
        KK2_OBJ_FIELD(chars, kk2_string_chars_t)
    KK2_OBJ_UNION_END()
KK2_OBJ_END(kk2_string)

extern kk2_string_t kk2_string(
    kk2_alloc_ct alloc,
    kk2_string_behaviour_ct behaviour,
    kk2_string_encoding_t encoding
);

extern kk2_string_t kk2_string_with(
    kk2_alloc_ct alloc,
    kk2_string_behaviour_ct behaviour,
    kk2_string_encoding_t encoding,
    kk2_string_view_t buff
);

extern kk2_string_t kk2_string_with_cstring(
    kk2_alloc_ct alloc,
    kk2_string_behaviour_ct behaviour,
    kk2_string_encoding_t encoding,
    kk2_cstring_t cstring
);

extern void kk2_string_free(
    kk2_string_pt self
);

extern kk2_string_encoding_t kk2_string_encoding(
    kk2_string_cpt self
);

extern kk2_pointer_t kk2_string_chars(
    kk2_string_cpt self
);

extern kk2_size_t kk2_string_length(
    kk2_string_cpt self
);

extern kk2_size_t kk2_string_count(
    kk2_string_cpt self
);

extern kk2_size_t kk2_string_capacity(
    kk2_string_cpt self
);

extern kk2_string_view_t kk2_string_as_view(
    kk2_string_cpt self,
    kk2_range_index_t range
);

extern kk2_bool_t kk2_string_is_empty(
    kk2_string_cpt self
);

extern kk2_bool_t kk2_string_is_equal(
    kk2_string_cpt self,
    kk2_string_view_t other
);

extern kk2_bool_t kk2_string_is_equal_cstring(
    kk2_string_cpt self,
    kk2_cstring_t other
);

extern kk2_bool_t kk2_string_is_prefix(
    kk2_string_cpt self,
    kk2_string_view_t find
);

extern kk2_bool_t kk2_string_is_prefix_cstring(
    kk2_string_cpt self,
    kk2_cstring_t find
);

extern kk2_bool_t kk2_string_is_suffix(
    kk2_string_cpt self,
    kk2_string_view_t find
);

extern kk2_bool_t kk2_string_is_suffix_cstring(
    kk2_string_cpt self,
    kk2_cstring_t find
);

extern kk2_range_index_t kk2_string_find_start(
    kk2_string_cpt self,
    kk2_range_index_t range,
    kk2_string_view_t find
);

extern kk2_range_index_t kk2_string_find_start_cstring(
    kk2_string_cpt self,
    kk2_range_index_t range,
    kk2_cstring_t find
);

extern kk2_range_index_t kk2_string_find_end(
    kk2_string_cpt self,
    kk2_range_index_t range,
    kk2_string_view_t find
);

extern kk2_range_index_t kk2_string_find_end_cstring(
    kk2_string_cpt self,
    kk2_range_index_t range,
    kk2_cstring_t find
);

extern kk2_bool_t kk2_string_insert(
    kk2_string_pt self,
    kk2_string_view_t insert,
    kk2_index_t index
);

extern kk2_bool_t kk2_string_insert_cstring(
    kk2_string_pt self,
    kk2_cstring_t insert,
    kk2_index_t index
);

extern kk2_size_t kk2_string_remove_range(
    kk2_string_pt self,
    kk2_range_index_t range
);

extern kk2_size_t kk2_string_remove_first(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_string_view_t find
);

extern kk2_size_t kk2_string_remove_first_cstring(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_cstring_t find
);

extern kk2_size_t kk2_string_remove_last(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_string_view_t find
);

extern kk2_size_t kk2_string_remove_last_cstring(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_cstring_t find
);

extern kk2_size_t kk2_string_remove_all(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_string_view_t find
);

extern kk2_size_t kk2_string_remove_all_cstring(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_cstring_t find
);

extern kk2_bool_t kk2_string_replace_range(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_string_view_t to
);

extern kk2_bool_t kk2_string_replace_first(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_string_view_t find,
    kk2_string_view_t to
);

extern kk2_bool_t kk2_string_replace_first_cstring(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_cstring_t find,
    kk2_cstring_t to
);

extern kk2_bool_t kk2_string_replace_last(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_string_view_t find,
    kk2_string_view_t to
);

extern kk2_bool_t kk2_string_replace_last_cstring(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_cstring_t find,
    kk2_cstring_t to
);

extern kk2_size_t kk2_string_replace_all(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_string_view_t find,
    kk2_string_view_t to
);

extern kk2_size_t kk2_string_replace_all_cstring(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_cstring_t find,
    kk2_cstring_t to
);

extern kk2_bool_t kk2_string_fit(
    kk2_string_pt self
);

#endif
