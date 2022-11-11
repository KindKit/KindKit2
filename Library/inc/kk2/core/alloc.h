#ifndef KK2_CORE_ALLOC_H
#define KK2_CORE_ALLOC_H

#include <kk2/std.h>

KK2_OBJ_BEGIN(kk2_alloc)
    KK2_OBJ_CALLBACK(new, kk2_pointer_t, (kk2_size_t))
    KK2_OBJ_CALLBACK(free, void, (kk2_pointer_t))
KK2_OBJ_END(kk2_alloc)

extern kk2_alloc_t kk2_alloc_default();

extern kk2_alloc_t kk2_alloc_validate(
    kk2_alloc_ct input
);

#endif
