#ifndef KK2_CORE_STRING_BEHAVIOUR_H
#define KK2_CORE_STRING_BEHAVIOUR_H

#include <kk2/std.h>

KK2_OBJ_BEGIN(kk2_string_behaviour)
    KK2_OBJ_CALLBACK(capacity, kk2_size_t, (kk2_size_t))
KK2_OBJ_END(kk2_string_behaviour)

extern kk2_string_behaviour_t kk2_string_behaviour_default();

extern kk2_string_behaviour_t kk2_string_behaviour_validate(
    kk2_string_behaviour_ct behaviour
);

#endif
