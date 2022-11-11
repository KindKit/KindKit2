#ifndef KK2_STD_H
#define KK2_STD_H

#include <stdalign.h>
#include <stdarg.h>
#ifndef __STDC_NO_ATOMICS__
#include <stdatomic.h>
#endif
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

#include <assert.h>
#include <string.h>

#define KK2_TYPEDEF_T(RAW, NAME) typedef RAW NAME##_t;
#define KK2_TYPEDEF_CT(RAW, NAME) typedef const NAME##_t NAME##_ct;
#define KK2_TYPEDEF_PT(RAW, NAME) typedef NAME##_t* NAME##_pt;
#define KK2_TYPEDEF_CPT(RAW, NAME) typedef NAME##_ct* NAME##_cpt;
#define KK2_TYPEDEF(RAW, NAME) KK2_TYPEDEF_T(RAW, NAME) KK2_TYPEDEF_CT(RAW, NAME) KK2_TYPEDEF_PT(RAW, NAME) KK2_TYPEDEF_CPT(RAW, NAME)

KK2_TYPEDEF(bool, kk2_bool);

KK2_TYPEDEF_T(void*, kk2_pointer);

KK2_TYPEDEF(uintptr_t, kk2_index);
KK2_TYPEDEF(uintptr_t, kk2_size);

KK2_TYPEDEF(int8_t, kk2_i8);
KK2_TYPEDEF(int16_t, kk2_i16);
KK2_TYPEDEF(int32_t, kk2_i32);
KK2_TYPEDEF(int64_t, kk2_i64);

KK2_TYPEDEF(uint8_t, kk2_u8);
KK2_TYPEDEF(uint16_t, kk2_u16);
KK2_TYPEDEF(uint32_t, kk2_u32);
KK2_TYPEDEF(uint64_t, kk2_u64);

KK2_TYPEDEF(float, kk2_f32);
KK2_TYPEDEF(double, kk2_f64);
KK2_TYPEDEF(long double, kk2_f80);

#define KK2_OBJ_BEGIN(NAME) struct NAME {
#define KK2_OBJ_FIELD(NAME, TYPE) TYPE NAME;
#define KK2_OBJ_ARRAY(NAME, TYPE, COUNT) TYPE NAME[COUNT];
#define KK2_OBJ_CALLBACK(NAME, OUTPUT, INPUT) OUTPUT (*NAME)INPUT;
#define KK2_OBJ_STRUCT_BEGIN(NAME) struct NAME {
#define KK2_OBJ_STRUCT_END() };
#define KK2_OBJ_UNION_BEGIN(NAME) union {
#define KK2_OBJ_UNION_END() };
#define KK2_OBJ_END(NAME) }; KK2_TYPEDEF(struct NAME, NAME);

#define KK2_ENUM_BEGIN(NAME) enum NAME {
#define KK2_ENUM_END(NAME) }; KK2_TYPEDEF(enum NAME, NAME);

#define KK2_UNION_BEGIN(NAME) union NAME {
#define KK2_UNION_END(NAME) }; KK2_TYPEDEF(union NAME, NAME);

#endif
