#ifndef KK2_CORE_ARRAY_H
#define KK2_CORE_ARRAY_H

#include <kk2/core/alloc.h>
#include <kk2/core/range_index.h>

KK2_OBJ_BEGIN(kk2_array_behaviour)
    KK2_OBJ_CALLBACK(capacity, kk2_size_t, (kk2_size_t))
    KK2_OBJ_CALLBACK(insert, void, (kk2_pointer_t))
    KK2_OBJ_CALLBACK(remove, void, (kk2_pointer_t))
KK2_OBJ_END(kk2_array_behaviour)

KK2_OBJ_BEGIN(kk2_array_buff)
    KK2_OBJ_FIELD(pointer, kk2_pointer_t)
    KK2_OBJ_FIELD(count, kk2_size_t)
KK2_OBJ_END(kk2_array_buff)

KK2_OBJ_BEGIN(kk2_array)
    KK2_OBJ_FIELD(alloc, kk2_alloc_cpt)
    KK2_OBJ_FIELD(behaviour, kk2_array_behaviour_cpt)
    KK2_OBJ_FIELD(element_size, kk2_size_t)
    KK2_OBJ_FIELD(count, kk2_size_t)
    KK2_OBJ_FIELD(capacity, kk2_size_t)
    KK2_OBJ_FIELD(pointer, kk2_pointer_t)
KK2_OBJ_END(kk2_array)

extern kk2_array_t kk2_array(
    kk2_alloc_cpt alloc,
    kk2_array_behaviour_cpt behaviour
);

extern kk2_array_t kk2_array_with(
    kk2_alloc_cpt alloc,
    kk2_array_behaviour_cpt behaviour,
    kk2_array_buff_t other
);

extern kk2_array_t kk2_array_with_array(
    kk2_alloc_cpt alloc,
    kk2_array_behaviour_cpt behaviour,
    kk2_array_cpt other
);

extern void kk2_array_free(
    kk2_array_pt self
);

extern kk2_bool_t kk2_array_fit(
    kk2_array_pt self
);

extern kk2_pointer_t kk2_array_pointer(
    kk2_array_cpt self
);

extern kk2_size_t kk2_array_length(
    kk2_array_cpt self
);

extern kk2_size_t kk2_array_count(
    kk2_array_cpt self
);

extern kk2_size_t kk2_array_capacity(
    kk2_array_cpt self
);

extern kk2_range_index_t kk2_array_range(
    kk2_array_cpt self
);

extern kk2_index_t kk2_array_start_index(
    kk2_array_cpt self
);

extern kk2_index_t kk2_array_end_index(
    kk2_array_cpt self
);

extern kk2_bool_t kk2_array_is_empty(
    kk2_array_cpt self
);

extern kk2_bool_t kk2_array_is_not_empty(
    kk2_array_cpt self
);

extern kk2_bool_t kk2_array_is_equal(
    kk2_array_cpt self,
    kk2_array_buff_t other
);

extern kk2_bool_t kk2_array_is_equal_array(
    kk2_array_cpt self,
    kk2_array_cpt other
);

extern kk2_bool_t kk2_array_is_prefix(
    kk2_array_cpt self,
    kk2_array_buff_t find
);

extern kk2_bool_t kk2_array_is_prefix_array(
    kk2_array_cpt self,
    kk2_array_cpt find
);

extern kk2_bool_t kk2_array_is_suffix(
    kk2_array_cpt self,
    kk2_array_buff_t find
);

extern kk2_bool_t kk2_array_is_suffix_array(
    kk2_array_cpt self,
    kk2_array_cpt find
);

extern kk2_range_index_t kk2_array_find_start(
    kk2_array_cpt self,
    kk2_range_index_t range,
    kk2_array_buff_t find
);

extern kk2_range_index_t kk2_array_find_start_array(
    kk2_array_cpt self,
    kk2_range_index_t range,
    kk2_array_cpt find
);

extern kk2_range_index_t kk2_array_find_end(
    kk2_array_cpt self,
    kk2_range_index_t range,
    kk2_array_buff_t find
);

extern kk2_range_index_t kk2_array_find_end_array(
    kk2_array_cpt self,
    kk2_range_index_t range,
    kk2_array_cpt find
);

extern kk2_bool_t kk2_array_insert(
    kk2_array_pt self,
    kk2_index_t index,
    kk2_array_buff_t insert
);

extern kk2_bool_t kk2_array_insert_array(
    kk2_array_pt self,
    kk2_index_t index,
    kk2_array_cpt insert
);

extern kk2_bool_t kk2_array_remove_range(
    kk2_array_pt self,
    kk2_range_index_t range
);

extern kk2_bool_t kk2_array_remove_first(
    kk2_array_pt self,
    kk2_range_index_t range,
    kk2_array_buff_t find
);

extern kk2_bool_t kk2_array_remove_first_array(
    kk2_array_pt self,
    kk2_range_index_t range,
    kk2_array_cpt find
);

extern kk2_bool_t kk2_array_remove_last(
    kk2_array_pt self,
    kk2_range_index_t range,
    kk2_array_buff_t find
);

extern kk2_bool_t kk2_array_remove_last_array(
    kk2_array_pt self,
    kk2_range_index_t range,
    kk2_array_cpt find
);

extern kk2_size_t kk2_array_remove_all(
    kk2_array_pt self,
    kk2_range_index_t range,
    kk2_array_buff_t find
);

extern kk2_size_t kk2_array_remove_all_array(
    kk2_array_pt self,
    kk2_range_index_t range,
    kk2_array_cpt find
);

extern kk2_bool_t kk2_array_replace_range(
    kk2_array_pt self,
    kk2_range_index_t range,
    kk2_array_buff_t to
);

extern kk2_bool_t kk2_array_replace_range_array(
    kk2_array_pt self,
    kk2_range_index_t range,
    kk2_array_cpt to
);

extern kk2_bool_t kk2_array_replace_first(
    kk2_array_pt self,
    kk2_range_index_t range,
    kk2_array_buff_t find,
    kk2_array_buff_t to
);

extern kk2_bool_t kk2_array_replace_first_array(
    kk2_array_pt self,
    kk2_range_index_t range,
    kk2_array_cpt find,
    kk2_array_cpt to
);

extern kk2_bool_t kk2_array_replace_last(
    kk2_array_pt self,
    kk2_range_index_t range,
    kk2_array_buff_t find,
    kk2_array_buff_t to
);

extern kk2_bool_t kk2_array_replace_last_array(
    kk2_array_pt self,
    kk2_range_index_t range,
    kk2_array_cpt find,
    kk2_array_cpt to
);

extern kk2_size_t kk2_array_replace_all(
    kk2_array_pt self,
    kk2_range_index_t range,
    kk2_array_buff_t find,
    kk2_array_buff_t to
);

extern kk2_size_t kk2_array_replace_all_array(
    kk2_array_pt self,
    kk2_range_index_t range,
    kk2_array_cpt find,
    kk2_array_cpt to
);

#endif
