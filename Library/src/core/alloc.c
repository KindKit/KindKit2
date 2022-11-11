#include <kk2/core/alloc.h>

kk2_pointer_t _kk2_alloc_new_(kk2_size_t count, kk2_size_t size_of) {
    return malloc(count * size_of);
}

void _kk2_alloc_free_(kk2_pointer_t pointer, kk2_size_t count) {
    free(pointer);
}

kk2_alloc_t kk2_alloc_default() {
    return (kk2_alloc_t){
        .new = _kk2_alloc_new_,
        .free = _kk2_alloc_free_
    };
}

kk2_alloc_t kk2_alloc_validate(
    kk2_alloc_ct input
) {
    return (kk2_alloc_t){
        .new = input.new != NULL ? input.new : _kk2_alloc_new_,
        .free = input.free != NULL ? input.free : _kk2_alloc_free_
    };
}
