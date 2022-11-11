#include <kk2/core/alloc.h>

kk2_alloc_t kk2_alloc_default() {
    return (kk2_alloc_t){
        .new = malloc,
        .free = free
    };
}

kk2_alloc_t kk2_alloc_validate(
    kk2_alloc_ct input
) {
    return (kk2_alloc_t){
        .new = input.new != NULL ? input.new : malloc,
        .free = input.free != NULL ? input.free : free
    };
}
