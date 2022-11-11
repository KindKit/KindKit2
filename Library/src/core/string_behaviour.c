#include <kk2/core/string_behaviour.h>

kk2_size_t _string_behaviour_capacity_(kk2_size_t input) {
    return input * 2;
}

kk2_string_behaviour_t kk2_string_behaviour_default() {
    return (kk2_string_behaviour_t){
        .capacity = _string_behaviour_capacity_
    };
}

kk2_string_behaviour_t kk2_string_behaviour_validate(
    kk2_string_behaviour_ct input
) {
    return (kk2_string_behaviour_t){
        .capacity = input.capacity != NULL ? input.capacity : _string_behaviour_capacity_
    };
}
