#ifndef KK2_CORE_MEMORY_H
#define KK2_CORE_MEMORY_H

#include <kk2/core/range_index.h>

KK2_OBJ_BEGIN(kk2_memory)
    KK2_OBJ_FIELD(pointer, kk2_pointer_t)
    KK2_OBJ_FIELD(count, kk2_size_t)
KK2_OBJ_END(kk2_memory)

#define KK2_MEMORY(POINTER, COUNT) \
    (kk2_memory_t){ .pointer = (kk2_pointer_t)(POINTER), .count = (COUNT) }

extern kk2_size_t kk2_memory_fill(
    kk2_memory_t dst,
    kk2_memory_t fill
);

extern kk2_size_t kk2_memory_copy(
    kk2_memory_t dst,
    kk2_memory_t src
);

extern kk2_size_t kk2_memory_copy_fill(
    kk2_memory_t dst,
    kk2_memory_t src,
    kk2_memory_t fill
);

extern kk2_size_t kk2_memory_copy_repeat(
    kk2_memory_t dst,
    kk2_memory_t src,
    kk2_size_t repeat
);

extern kk2_size_t kk2_memory_move(
    kk2_memory_t dst,
    kk2_memory_t src
);

extern kk2_bool_t kk2_memory_is_equal(
    kk2_memory_t lhs,
    kk2_memory_t rhs
);

extern kk2_range_index_t kk2_memory_find_forward(
    kk2_memory_t memory,
    kk2_memory_t find
);

extern kk2_range_index_t kk2_memory_find_backward(
    kk2_memory_t memory,
    kk2_memory_t find
);

#endif
