#ifndef KK2_CORE_STRING_SCALAR_H
#define KK2_CORE_STRING_SCALAR_H

#include <kk2/std.h>

#define KK2_STRING_BUILTIN_BYTES 32

KK2_TYPEDEF(char, kk2_cchar);
KK2_TYPEDEF_T(kk2_cchar_pt, kk2_cstring);

KK2_TYPEDEF(wchar_t, kk2_wchar);
KK2_TYPEDEF_T(kk2_wchar_pt, kk2_wstring);

KK2_UNION_BEGIN(kk2_string_chars)
    KK2_OBJ_FIELD(pointer, kk2_pointer_t)
    KK2_OBJ_FIELD(cchars, kk2_cstring_t)
    KK2_OBJ_FIELD(wchars, kk2_wstring_t)
KK2_UNION_END(kk2_string_chars)

KK2_UNION_BEGIN(kk2_string_builtin)
    KK2_OBJ_ARRAY(cchars, kk2_cchar_t, KK2_STRING_BUILTIN_BYTES / sizeof(kk2_cchar_t))
    KK2_OBJ_ARRAY(wchars, kk2_wchar_t, KK2_STRING_BUILTIN_BYTES / sizeof(kk2_wchar_t))
KK2_UNION_END(kk2_string_builtin)

#define KK2_CSTRING_BUILTIN(CHARS) \
    (kk2_string_builtin_t){ .cchars = (CHARS) }

#define KK2_WSTRING_BUILTIN(CHARS) \
    (kk2_string_builtin_t){ .wchars = (CHARS) }

KK2_TYPEDEF(kk2_u32_t, kk2_string_scalar)

#endif
