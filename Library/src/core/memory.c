#include <kk2/core/memory.h>

kk2_size_t kk2_memory_fill(
    kk2_memory_t dst,
    kk2_memory_t fill,
    kk2_size_t size_of
) {
    assert(dst.pointer != NULL);
    assert(dst.count != 0);
    
    assert(fill.pointer != NULL);
    assert(fill.count != 0);
    
    kk2_u8_pt dpointer = (kk2_u8_pt)dst.pointer;
    kk2_size_t dcount = dst.count * size_of;
    kk2_size_t result = 0;
    while (dcount > 0) {
        kk2_u8_pt fpointer = (kk2_u8_pt)fill.pointer;
        kk2_size_t fcount = fill.count * size_of;
        while (dcount >= size_of && fcount >= size_of) {
            *dpointer = *fpointer;
            ++dpointer;
            --dcount;
            ++fpointer;
            --fcount;
            ++result;
        }
    }
    return result;
}

kk2_size_t kk2_memory_copy(
    kk2_memory_t dst,
    kk2_memory_t src,
    kk2_size_t size_of
) {
    assert(dst.pointer != NULL);
    assert(dst.count != 0);
    
    assert(src.pointer != NULL);
    assert(src.count != 0);
    
    kk2_u8_pt dpointer = (kk2_u8_pt)dst.pointer;
    kk2_size_t dcount = dst.count * size_of;
    kk2_u8_pt spointer = (kk2_u8_pt)src.pointer;
    kk2_size_t scount = src.count * size_of;
    kk2_size_t result = 0;
    while (dcount >= size_of && scount >= size_of) {
        *dpointer = *spointer;
        ++dpointer;
        --dcount;
        ++spointer;
        --scount;
        ++result;
    }
    return result;
}

kk2_size_t kk2_memory_copy_fill(
    kk2_memory_t dst,
    kk2_memory_t src,
    kk2_memory_t fill,
    kk2_size_t size_of
) {
    assert(dst.pointer != NULL);
    assert(dst.count != 0);
    
    assert(src.pointer != NULL);
    assert(src.count != 0);
    
    assert(fill.pointer != NULL);
    assert(fill.count != 0);
    
    kk2_size_t copied = kk2_memory_copy(dst, src, size_of);
    if (copied < dst.count) {
        kk2_size_t filled = kk2_memory_fill(
            (kk2_memory_t) {
                .pointer = ((kk2_u8_pt)dst.pointer) + (copied * size_of),
                .count = dst.count - copied
            },
            fill,
            size_of
        );
        return copied + filled;
    }
    return copied;
}

kk2_size_t kk2_memory_copy_repeat(
    kk2_memory_t dst,
    kk2_memory_t src,
    kk2_size_t size_of,
    kk2_size_t repeat
) {
    assert(dst.pointer != NULL);
    assert(dst.count != 0);
    
    assert(src.pointer != NULL);
    assert(src.count != 0);
    
    kk2_u8_pt dpointer = (kk2_u8_pt)dst.pointer;
    kk2_size_t dcount = dst.count * size_of;
    kk2_size_t rpt = repeat;
    kk2_size_t result = 0;
    while (rpt > 0) {
        kk2_size_t copied = kk2_memory_copy((kk2_memory_t) {
            .pointer = dpointer,
            .count = dcount
        }, src, size_of);
        dpointer += copied * size_of;
        dcount -= copied;
        rpt -= 1;
        result += copied;
    }
    return result;
}

kk2_size_t kk2_memory_move(
    kk2_memory_t dst,
    kk2_memory_t src,
    kk2_size_t size_of
) {
    assert(dst.pointer != NULL);
    assert(dst.count != 0);
    
    assert(src.pointer != NULL);
    assert(src.count != 0);
    
    kk2_size_t dcount = dst.count * size_of;
    kk2_size_t scount = src.count * size_of;
    kk2_size_t result = 0;
    if (dst.pointer <= src.pointer) {
        kk2_u8_pt dpointer = (kk2_u8_pt)dst.pointer;
        kk2_u8_pt spointer = (kk2_u8_pt)src.pointer;
        while (dcount >= size_of && scount >= size_of) {
            *dpointer = *spointer;
            dpointer += size_of;
            spointer += size_of;
            dcount -= size_of;
            scount -= size_of;
            result += 1;
        }
    } else {
        kk2_u8_pt dpointer = (kk2_u8_pt)(dst.pointer) + (dst.count - 1);
        kk2_u8_pt spointer = (kk2_u8_pt)(src.pointer) + (src.count - 1);
        while (dcount >= size_of && scount >= size_of) {
            *dpointer = *spointer;
            dpointer -= size_of;
            spointer -= size_of;
            dcount -= size_of;
            scount -= size_of;
            ++result;
        }
    }
    return result;
}

kk2_bool_t kk2_memory_is_equal(
    kk2_memory_t lhs,
    kk2_memory_t rhs,
    kk2_size_t size_of
) {
    assert(lhs.pointer != NULL);
    assert(lhs.count != 0);
    
    assert(rhs.pointer != NULL);
    assert(rhs.count != 0);
    
    if (lhs.count != rhs.count) {
        return false;
    }
    kk2_u8_pt lpointer = (kk2_u8_pt)lhs.pointer;
    kk2_u8_pt rpointer = (kk2_u8_pt)rhs.pointer;
    kk2_size_t count = lhs.count * size_of;
    while (count > 0) {
        if (*lpointer != *rpointer) {
            return false;
        }
        lpointer += size_of;
        rpointer += size_of;
        count -= 1;
    }
    return true;
}

kk2_range_index_t kk2_memory_find_forward(
    kk2_memory_t memory,
    kk2_memory_t find,
    kk2_size_t size_of
) {
    assert(memory.pointer != NULL);
    assert(memory.count != 0);

    assert(find.pointer != NULL);
    assert(find.count != 0);

    if (memory.count < find.count) {
        return KK2_RANGE_INDEX_ZERO;
    }
    kk2_u8_pt mpointer = (kk2_u8_pt)memory.pointer;
    kk2_u8_pt fpointer = (kk2_u8_pt)find.pointer;
    kk2_size_t count = (memory.count - find.count) + 1;
    kk2_size_t index = 0;
    while (count > 0) {
        if (*mpointer == *fpointer) {
            kk2_memory_t tmp = (kk2_memory_t){
                .pointer = mpointer,
                .count = find.count
            };
            if (kk2_memory_is_equal(tmp, find, size_of) == true) {
                return (kk2_range_index_t){
                    .lower = index,
                    .upper = index + find.count
                };
            }
        }
        mpointer += size_of;
        count -= 1;
        index += 1;
    }
    return KK2_RANGE_INDEX_ZERO;
}

kk2_range_index_t kk2_memory_find_backward(
    kk2_memory_t memory,
    kk2_memory_t find,
    kk2_size_t size_of
) {
    assert(memory.pointer != NULL);
    assert(memory.count != 0);

    assert(find.pointer != NULL);
    assert(find.count != 0);

    if (memory.count < find.count) {
        return KK2_RANGE_INDEX_ZERO;
    }
    kk2_u8_pt mpointer = (kk2_u8_pt)memory.pointer + ((memory.count * size_of) - size_of);
    kk2_u8_pt fpointer = (kk2_u8_pt)find.pointer + ((find.count * size_of) - size_of);
    kk2_size_t count = (memory.count - find.count) + 1;
    kk2_size_t index = memory.count;
    while (count > 0) {
        if (*mpointer == *fpointer) {
            kk2_memory_t tmp = (kk2_memory_t){
                .pointer = mpointer - ((find.count - 1) * size_of),
                .count = find.count 
            };
            if (kk2_memory_is_equal(tmp, find, size_of) == true) {
                return (kk2_range_index_t){
                    .lower = index - find.count,
                    .upper = index
                };
            }
        }
        mpointer -= size_of;
        count -= 1;
        index -= 1;
    }
    return KK2_RANGE_INDEX_ZERO;
}
