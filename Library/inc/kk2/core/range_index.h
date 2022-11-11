#ifndef KK2_CORE_RANGE_INDEX_H
#define KK2_CORE_RANGE_INDEX_H

#include <kk2/std.h>

KK2_OBJ_BEGIN(kk2_range_index)
    KK2_OBJ_FIELD(lower, kk2_index_t)
    KK2_OBJ_FIELD(upper, kk2_index_t)
KK2_OBJ_END(kk2_range_index)

#define KK2_RANGE_INDEX(LOWER, UPPER) \
    (kk2_range_index_t){ .lower = (LOWER), .upper = (UPPER) }

#define KK2_RANGE_INDEX_ZERO \
    KK2_RANGE_INDEX(0, 0)

#endif
