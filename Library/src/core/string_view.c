#include <kk2/core/string_view.h>
#include <kk2/core/memory.h>
/*
kk2_bool_t kk2_string_view_is_empty(
    kk2_string_view_t self
) {
    return self.count == 0;
}

kk2_bool_t kk2_string_view_is_equal(
    kk2_string_view_t self,
    kk2_string_view_t other
) {
    assert(self.chars != NULL);
    assert(self.count > 0);
    assert(other.chars != NULL);
    assert(other.count > 0);
    if (self.count != other.count) {
        return false;
    }
    return kk2_memory_is_equal((kk2_memory_t) {
        .pointer = (kk2_pointer_t)self.chars,
        .count = self.count * sizeof(kk2_u8_t)
    }, (kk2_memory_t){
        .pointer = (kk2_pointer_t)other.chars,
        .count = other.count * sizeof(kk2_u8_t)
    });
}

kk2_bool_t kk2_string_view_is_prefix(
    kk2_string_view_t self,
    kk2_string_view_t find
) {
    assert(self.chars != NULL);
    assert(self.count > 0);
    assert(find.chars != NULL);
    assert(find.count > 0);
    if (self.count < find.count) {
        return false;
    }
    return kk2_memory_is_equal((kk2_memory_t){
        .pointer = (kk2_pointer_t)self.chars,
        .count = find.count * sizeof(kk2_u8_t)
    }, (kk2_memory_t){
        .pointer = (kk2_pointer_t)find.chars,
        .count = find.count * sizeof(kk2_u8_t)
    });
}

kk2_bool_t kk2_string_view_is_suffix(
    kk2_string_view_t self,
    kk2_string_view_t find
) {
    assert(self.chars != NULL);
    assert(self.count > 0);
    assert(find.chars != NULL);
    assert(find.count > 0);
    if (self.count < find.count) {
        return false;
    }
    return kk2_memory_is_equal((kk2_memory_t){
        .pointer = (kk2_pointer_t)self.chars + (self.count - find.count),
        .count = find.count * sizeof(kk2_u8_t)
    }, (kk2_memory_t){
        .pointer = (kk2_pointer_t)find.chars,
        .count = find.count * sizeof(kk2_u8_t)
    });
}

kk2_range_index_t kk2_string_view_find_start(
    kk2_string_view_t self,
    kk2_string_view_t find
) {
    assert(self.chars != NULL);
    assert(self.count > 0);
    assert(find.chars != NULL);
    assert(find.count > 0);
    kk2_range_index_t founded = kk2_memory_find_forward((kk2_memory_t){
        .pointer = (kk2_pointer_t)self.chars,
        .count = self.count * sizeof(kk2_u8_t)
    }, (kk2_memory_t){
        .pointer = (kk2_pointer_t)find.chars,
        .count = find.count * sizeof(kk2_u8_t)
    }, sizeof(sizeof(kk2_u8_t)));
    return (kk2_range_index_t){
        .lower = founded.lower / sizeof(kk2_u8_t),
        .upper = founded.upper / sizeof(kk2_u8_t)
    };
}

kk2_range_index_t kk2_string_view_find_end(
    kk2_string_view_t self,
    kk2_string_view_t find
) {
    assert(self.chars != NULL);
    assert(self.count > 0);
    assert(find.chars != NULL);
    assert(find.count > 0);
    kk2_range_index_t founded = kk2_memory_find_backward((kk2_memory_t){
        .pointer = (kk2_pointer_t)self.chars,
        .count = self.count * sizeof(kk2_u8_t)
    }, (kk2_memory_t){
        .pointer = (kk2_pointer_t)find.chars,
        .count = find.count * sizeof(kk2_u8_t)
    });
    return (kk2_range_index_t){
        .lower = founded.lower / sizeof(kk2_u8_t),
        .upper = founded.upper / sizeof(kk2_u8_t)
    };
}
*/
