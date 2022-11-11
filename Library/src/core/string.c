#include <kk2/core/string.h>

#define _CHARS_(SELF) \
    ((SELF)->capacity > 0) ? (kk2_u8_pt)((SELF)->chars) : (kk2_u8_pt)&((SELF)->builtin)

#define _CHARS_EX_(SELF, OFFSET) \
    ((SELF)->capacity > 0) ? (kk2_u8_pt)((SELF)->chars) + (OFFSET) : (kk2_u8_pt)&((SELF)->builtin[(OFFSET)])

#define _MEMORY_EX_(POINTER, OFFSET, COUNT) \
    KK2_MEMORY((kk2_u8_pt)(POINTER) + (OFFSET), COUNT)

#define _CHARS_MEMORY_(SELF, COUNT) \
    KK2_MEMORY(_CHARS_(SELF), COUNT)

#define _CHARS_MEMORY_EX_(SELF, OFFSET, COUNT) \
    KK2_MEMORY(_CHARS_EX_(SELF, OFFSET), COUNT)

kk2_string_t kk2_string(
    kk2_alloc_ct alloc,
    kk2_string_behaviour_ct behaviour,
    kk2_string_encoding_t encoding
) {
    return (kk2_string_t){
        .alloc = kk2_alloc_validate(alloc),
        .behaviour = kk2_string_behaviour_validate(behaviour),
        .encoding = encoding,
        .range = KK2_RANGE_INDEX_ZERO,
        .capacity = 0,
        .builtin = { 0 }
    };
}

kk2_string_t kk2_string_with(
    kk2_alloc_ct alloc,
    kk2_string_behaviour_ct behaviour,
    kk2_string_encoding_t encoding,
    kk2_string_view_t view
) {
    kk2_string_t self = kk2_string(alloc, behaviour, encoding);
    if (view.count >= KK2_STRING_BUILTIN_BYTES) {
        kk2_size_t capacity = self.behaviour.capacity(view.count);
        self.chars.pointer = self.alloc.new(capacity * sizeof(kk2_u8_t));
        if (self.chars.pointer != NULL) {
            kk2_memory_copy(
                KK2_MEMORY(self.chars.pointer, capacity),
                KK2_MEMORY(view.cchars, view.count)
            );
            self.range.upper = view.count;
            self.capacity = capacity;
        }
    } else {
        kk2_memory_copy(
            KK2_MEMORY(self.builtin, KK2_STRING_BUILTIN_BYTES),
            KK2_MEMORY(view.cchars, view.count)
        );
        self.range.upper = view.count;
        self.capacity = 0;
    }
    return self;
}

kk2_string_t kk2_string_with_cstring(
    kk2_alloc_ct alloc,
    kk2_string_behaviour_ct behaviour,
    kk2_string_encoding_t encoding,
    kk2_cstring_t cstring
) {
    return kk2_string_with(alloc, behaviour, encoding, KK2_STRING_VIEW_CSTRING(cstring));
}

void kk2_string_free(
    kk2_string_pt self
) {
    assert(self);
    self->range = KK2_RANGE_INDEX_ZERO;
    if (self->capacity > 0) {
        self->alloc.free(self->chars.pointer, self->capacity);
        self->chars.pointer = NULL;
        self->capacity = 0;
    }
}

kk2_string_encoding_t kk2_string_encoding(
    kk2_string_cpt self
) {
    assert(self);
    return self->encoding;
}

kk2_pointer_t kk2_string_chars(
    kk2_string_cpt self
) {
    assert(self);
    return _CHARS_EX_(self, self->range.lower);
}

kk2_size_t kk2_string_length(
    kk2_string_cpt self
) {
    assert(self);
    kk2_size_t result = 0;
    kk2_u8_cpt chars = _CHARS_EX_(self, self->range.lower);
    while (*chars != '\0') {
        if ((*chars & 0xc0) != 0x80) {
            ++result;
        }
        ++chars;
    }
    return result;
}

kk2_size_t kk2_string_count(
    kk2_string_cpt self
) {
    assert(self);
    return self->range.upper - self->range.lower;
}

kk2_size_t kk2_string_capacity(
    kk2_string_cpt self
) {
    assert(self);
    return self->capacity;
}

kk2_string_view_t kk2_string_as_view(
    kk2_string_cpt self,
    kk2_range_index_t range
) {
    assert(self);
    kk2_size_t scount = self->range.upper - self->range.lower;
    kk2_size_t rcount = range.upper - range.lower;
    kk2_size_t count = (scount > rcount) ? rcount : scount;
    return KK2_STRING_VIEW(
        _CHARS_EX_(self, self->range.lower + range.lower),
        count
    );
}

kk2_bool_t kk2_string_is_empty(
    kk2_string_cpt self
) {
    assert(self);
    return self->range.lower == self->range.upper;
}

kk2_bool_t kk2_string_is_equal(
    kk2_string_cpt self,
    kk2_string_view_t other
) {
    assert(self);
    kk2_size_t count = self->range.upper - self->range.lower;
    if (count != other.count) {
        return false;
    }
    return kk2_memory_is_equal(
        _CHARS_MEMORY_EX_(self, self->range.lower, count),
        KK2_MEMORY(other.chars, other.count),
        sizeof(kk2_u8_t)
    );
}

kk2_bool_t kk2_string_is_equal_cstring(
    kk2_string_cpt self,
    kk2_cstring_t other
) {
    return kk2_string_is_equal(self, KK2_STRING_VIEW_CSTRING(other));
}

kk2_bool_t kk2_string_is_prefix(
    kk2_string_cpt self,
    kk2_string_view_t find
) {
    assert(self);
    kk2_size_t count = self->range.upper - self->range.lower;
    if (count < find.count) {
        return false;
    }
    return kk2_memory_is_equal(
        _CHARS_MEMORY_EX_(self, self->range.lower, find.count),
        KK2_MEMORY(find.chars, find.count),
        sizeof(kk2_u8_t)
    );
}

kk2_bool_t kk2_string_is_prefix_cstring(
    kk2_string_cpt self,
    kk2_cstring_t find
) {
    return kk2_string_is_prefix(self, KK2_STRING_VIEW_CSTRING(find));
}

kk2_bool_t kk2_string_is_suffix(
    kk2_string_cpt self,
    kk2_string_view_t find
) {
    assert(self);
    kk2_size_t count = self->range.upper - self->range.lower;
    if (count < find.count) {
        return false;
    }
    return kk2_memory_is_equal(
        _CHARS_MEMORY_EX_(self, self->range.upper - find.count, find.count),
        KK2_MEMORY(find.chars, find.count),
        sizeof(kk2_u8_t)
    );
}

kk2_bool_t kk2_string_is_suffix_cstring(
    kk2_string_cpt self,
    kk2_cstring_t find
) {
    return kk2_string_is_suffix(self, KK2_STRING_VIEW_CSTRING(find));
}

kk2_range_index_t kk2_string_find_start(
    kk2_string_cpt self,
    kk2_range_index_t range,
    kk2_string_view_t find
) {
    assert(self);
    kk2_size_t scount = self->range.upper - self->range.lower;
    kk2_size_t rcount = range.upper - range.lower;
    kk2_size_t count = (scount > rcount) ? rcount : scount;
    if (count < find.count) {
        return KK2_RANGE_INDEX_ZERO;
    }
    kk2_range_index_t found_range = kk2_memory_find_forward(
        _CHARS_MEMORY_EX_(self, self->range.lower + range.lower, count),
        KK2_MEMORY(find.chars, find.count),
        sizeof(kk2_u8_t)
    );
    return KK2_RANGE_INDEX(
        range.lower + found_range.lower,
        range.lower + found_range.upper
    );
}

kk2_range_index_t kk2_string_find_end(
    kk2_string_cpt self,
    kk2_range_index_t range,
    kk2_string_view_t find
) {
    assert(self);
    kk2_size_t scount = self->range.upper - self->range.lower;
    kk2_size_t rcount = range.upper - range.lower;
    kk2_size_t count = (scount > rcount) ? rcount : scount;
    if (count < find.count) {
        return KK2_RANGE_INDEX_ZERO;
    }
    kk2_range_index_t found_range = kk2_memory_find_backward(
        _CHARS_MEMORY_EX_(self, self->range.lower + range.lower, count),
        KK2_MEMORY(find.chars, find.count),
        sizeof(kk2_u8_t)
    );
    return KK2_RANGE_INDEX(
        range.lower + found_range.lower,
        range.lower + found_range.upper
    );
}

kk2_bool_t kk2_string_insert(
    kk2_string_pt self,
    kk2_string_view_t insert,
    kk2_index_t index
) {
    assert(self);
    if (kk2_string_is_empty(self) == true) {
        *self = kk2_string_with(self->alloc, self->behaviour, self->encoding, insert);
        return kk2_string_is_empty(self) == false;
    }
    kk2_size_t old_capacity = (self->capacity > 0) ? self->capacity : KK2_STRING_BUILTIN_BYTES;
    kk2_size_t old_count = self->range.upper - self->range.lower;
    kk2_size_t new_count = old_count + insert.count;
    if ((index <= self->range.lower) && (self->range.lower >= insert.count)) {
        kk2_u8_pt chars = _CHARS_(self);
        kk2_memory_copy(
            _MEMORY_EX_(chars, self->range.lower - insert.count, insert.count),
            KK2_MEMORY(insert.chars, insert.count),
            sizeof(kk2_u8_t)
        );
        self->range.lower -= insert.count;
    } else if ((index >= self->range.upper) && (self->range.upper - old_capacity >= insert.count)) {
        kk2_u8_pt chars = _CHARS_(self);
        kk2_memory_copy(
            _MEMORY_EX_(chars, self->range.upper, insert.count + 1),
            KK2_MEMORY(insert.chars, insert.count),
            sizeof(kk2_u8_t)
        );
        self->range.upper += insert.count;
    } else {
        kk2_size_t insert_index = (index <= old_count) ? index : old_count - 1;
        if ((new_count >= self->capacity) && (new_count >= KK2_STRING_BUILTIN_BYTES)) {
            kk2_size_t new_capacity = self->behaviour.capacity(new_count) + 1;
            kk2_u8_pt new_chars = self->alloc.new(new_capacity, sizeof(kk2_u8_t));
            kk2_u8_cpt old_chars = _CHARS_(self);
            if (new_chars != NULL) {
                kk2_size_t offset = 0;
                if (insert_index > 0) {
                    offset += kk2_memory_copy(
                        KK2_MEMORY(new_chars, insert_index),
                        KK2_MEMORY(old_chars, old_count),
                        sizeof(kk2_u8_t)
                    );
                }
                offset += kk2_memory_copy(
                    KK2_MEMORY(new_chars, new_count),
                    KK2_MEMORY(insert.chars, insert.count),
                    sizeof(kk2_u8_t)
                );
                kk2_memory_copy(
                    _MEMORY_EX_(new_chars, insert_index + insert.count, new_capacity - offset),
                    _MEMORY_EX_(old_chars, insert_index, old_count - insert_index),
                    sizeof(kk2_u8_t)
                );
                if (self->capacity > 0) {
                    self->alloc.free(self->chars, self->capacity);
                }
                self->chars = new_chars;
                self->range = KK2_RANGE_INDEX(0, new_count);
                self->capacity = new_capacity;
            }
        } else {
            kk2_u8_cpt chars = _CHARS_(self);
            if (insert_index < self->range.upper) {
                kk2_size_t move_count = self->range.upper - insert_index;
                kk2_memory_move(
                    _MEMORY_EX_(chars, insert_index + insert.count, move_count),
                    _MEMORY_EX_(chars, insert_index, move_count),
                    sizeof(kk2_u8_t)
                );
            }
            kk2_memory_copy(
                _MEMORY_EX_(chars, insert_index, insert.count),
                KK2_MEMORY(insert.chars, insert.count),
                sizeof(kk2_u8_t)
            );
            self->range.upper = new_count;
        }
    }
    return (self->range.upper - self->range.lower) == new_count;
}

kk2_size_t kk2_string_remove_range(
    kk2_string_pt self,
    kk2_range_index_t range
) {
    assert(self);
    kk2_size_t scount = self->range.upper - self->range.lower;
    if (scount == 0) {
        return 0;
    }
    kk2_index_t lower = (range.lower > scount) ? scount : range.lower;
    kk2_index_t upper = (range.upper > scount) ? scount : range.upper;
    kk2_size_t rcount = upper - lower;
    if (rcount == 0) {
        return 0;
    }
    if (lower == 0) {
        self->range.lower += rcount;
    } else {
        if (upper == scount) {
            self->range.upper -= rcount;
        } else {
            kk2_u8_cpt chars = _CHARS_EX_(self, self->range.lower);
            kk2_memory_move(
                _MEMORY_EX_(chars, range.lower, scount - lower),
                _MEMORY_EX_(chars, range.upper, scount - upper),
                sizeof(kk2_u8_t)
            );
            self->range.upper -= rcount;
        }
    }
    return rcount;
}

kk2_size_t kk2_string_remove_first(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_string_view_t find
) {
    assert(self);
    kk2_range_index_t find_range = kk2_string_find_start(self, range, find);
    if (find_range.lower >= find_range.upper) {
        return 0;
    }
    return kk2_string_remove_range(self, find_range);
}

kk2_size_t kk2_string_remove_last(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_string_view_t find
) {
    assert(self);
    kk2_range_index_t find_range = kk2_string_find_end(self, range, find);
    if (find_range.lower == find_range.upper) {
        return 0;
    }
    return kk2_string_remove_range(self, find_range);
}

kk2_size_t kk2_string_remove_all(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_string_view_t find
) {
    assert(self);
    kk2_range_index_t final_range = range;
    kk2_size_t result = 0;
    while (true) {
        kk2_range_index_t find_range = kk2_string_find_start(self, final_range, find);
        if (find_range.lower >= find_range.upper) {
            break;
        }
        kk2_size_t removed = kk2_string_remove_range(self, find_range);
        if (removed == 0) {
            break;
        }
        final_range.lower = find_range.lower;
        final_range.upper -= find_range.upper - find_range.lower;
        result += 1;
    }
    return result;
}

kk2_bool_t kk2_string_replace_range(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_string_view_t replace
) {
    assert(self);
    kk2_size_t removed = kk2_string_remove_range(self, range);
    if (removed == 0) {
        return false;
    }
    return kk2_string_insert(self, replace, range.lower);
}

kk2_bool_t kk2_string_replace_first(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_string_view_t find,
    kk2_string_view_t replace
) {
    assert(self);
    kk2_range_index_t find_range = kk2_string_find_start(self, range, find);
    if (find_range.lower == find_range.upper) {
        return false;
    }
    kk2_size_t removed = kk2_string_remove_range(self, find_range);
    if (removed == 0) {
        return false;
    }
    return kk2_string_insert(self, replace, find_range.lower);
}

kk2_bool_t kk2_string_replace_last(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_string_view_t find,
    kk2_string_view_t replace
) {
    assert(self);
    kk2_range_index_t find_range = kk2_string_find_end(self, range, find);
    if (find_range.lower == find_range.upper) {
        return false;
    }
    kk2_size_t removed = kk2_string_remove_range(self, find_range);
    if (removed == 0) {
        return false;
    }
    return kk2_string_insert(self, replace, find_range.lower);
}

kk2_size_t kk2_string_replace_all(
    kk2_string_pt self,
    kk2_range_index_t range,
    kk2_string_view_t find,
    kk2_string_view_t replace
) {
    assert(self);
    kk2_range_index_t final_range = range;
    kk2_size_t result = 0;
    while (true) {
        kk2_range_index_t find_range = kk2_string_find_start(self, final_range, find);
        if (find_range.lower >= find_range.upper) {
            break;
        }
        kk2_size_t removed = kk2_string_remove_range(self, find_range);
        if (removed == 0) {
            break;
        }
        if (kk2_string_insert(self, replace, find_range.lower) == false) {
            break;
        }
        final_range.lower = find_range.lower + replace.count;
        final_range.upper -= (find_range.upper - find_range.lower) - replace.count;
        result += 1;
    }
    return result;
}

kk2_bool_t kk2_string_fit(
    kk2_string_pt self
) {
    assert(self);
    kk2_size_t old_capacity = self->capacity;
    if (old_capacity == 0) {
        return true;
    }
    kk2_pointer_t old_pointer = (kk2_pointer_t)self->chars;
    kk2_size_t count = self->range.upper - self->range.lower;
    if (count >= KK2_STRING_BUILTIN_BYTES) {
        kk2_u8_pt new_chars = self->alloc.new(count, sizeof(kk2_u8_t));
        if (new_chars == NULL) {
            return false;
        }
        kk2_memory_copy(
            KK2_MEMORY(new_chars, count),
            _CHARS_MEMORY_EX_(self, self->range.lower, count),
            sizeof(kk2_u8_t)
        );
        self->capacity = count;
        self->chars = new_chars;
    } else {
        kk2_memory_copy(
            KK2_MEMORY(&self->builtin, count),
            _CHARS_MEMORY_EX_(self, self->range.lower, count),
            sizeof(kk2_u8_t)
        );
        self->capacity = 0;
    }
    self->range = KK2_RANGE_INDEX(0, count);
    self->alloc.free(old_pointer, old_capacity);
    return true;
}
