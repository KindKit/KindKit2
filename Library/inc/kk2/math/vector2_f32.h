#ifndef KK2_MATH_VECTOR2_F32_H
#define KK2_MATH_VECTOR2_F32_H

#include <kk2/std.h>

KK2_OBJ_BEGIN(kk2_vector2_f32)
    KK2_OBJ_UNION_BEGIN()
        KK2_OBJ_STRUCT_BEGIN()
            KK2_OBJ_FIELD(x, kk2_f32_t)
            KK2_OBJ_FIELD(y, kk2_f32_t)
        KK2_OBJ_STRUCT_END()
        KK2_OBJ_FIELD(v, kk2_f32_t)
    KK2_OBJ_UNION_END()
KK2_OBJ_END(kk2_vector2_f32)

#define KK2_VECTOR2_F32(X, Y) (kk2_vector2_f32_t){ .x = (X), .y = (Y) }

#define KK2_VECTOR2_F32_ZERO KK2_VECTOR2_F32(0, 0)

#endif
