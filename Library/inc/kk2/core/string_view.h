#ifndef KK2_CORE_STRING_VIEW_H
#define KK2_CORE_STRING_VIEW_H

#include <kk2/core/memory.h>
#include <kk2/core/range_index.h>
#include <kk2/core/string_encoding.h>
#include <kk2/core/string_scalar.h>

KK2_OBJ_BEGIN(kk2_string_view)
    KK2_OBJ_FIELD(encoding, kk2_string_encoding_t)
    KK2_OBJ_UNION_BEGIN()
        KK2_OBJ_FIELD(pointer, kk2_pointer_t)
        KK2_OBJ_FIELD(cchars, kk2_cstring_t)
        KK2_OBJ_FIELD(wchars, kk2_wstring_t)
    KK2_OBJ_UNION_END()
    KK2_OBJ_FIELD(count, kk2_size_t)
KK2_OBJ_END(kk2_string_view)

#define KK2_CSTRING_VIEW(ENCODING, CHARS, COUNT) \
    (kk2_string_view_t){ .chars = (kk2_string_char_t){ .encoding = (ENCODING), .cchars = (kk2_cstring_t)(CHARS) }, .count = (COUNT) }

#define KK2_WSTRING_VIEW(ENCODING, CHARS, COUNT) \
    (kk2_string_view_t){ .chars = (kk2_string_char_t){ .encoding = (ENCODING), .wchars = (kk2_wstring_t)(CHARS) }, .count = (COUNT) }

#define KK2_STRING_VIEW_CSTRING(CHARS) \
    KK2_CSTRING_VIEW(CHARS, strlen(CHARS))

#define KK2_STRING_VIEW_WSTRING(CHARS) \
    KK2_WSTRING_VIEW(CHARS, wstrlen(CHARS))

extern kk2_bool_t kk2_string_view_is_empty(
    kk2_string_view_t self
);

extern kk2_bool_t kk2_string_view_is_equal(
    kk2_string_view_t self,
    kk2_string_view_t other
);

extern kk2_bool_t kk2_string_view_is_prefix(
    kk2_string_view_t self,
    kk2_string_view_t find
);

extern kk2_bool_t kk2_string_view_is_suffix(
    kk2_string_view_t self,
    kk2_string_view_t find
);

extern kk2_range_index_t kk2_string_view_find_start(
    kk2_string_view_t self,
    kk2_string_view_t find
);

extern kk2_range_index_t kk2_string_view_find_end(
    kk2_string_view_t self,
    kk2_string_view_t find
);

#endif
