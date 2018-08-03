#ifndef NUMERIX_MATRIX_BASE_H
#define NUMERIX_MATRIX_BASE_H 1

#include "common.h"

#define MATRIX3X2() \
    Matrix3x2 *m;   \
    Data_Get_Struct(self, Matrix3x2, m)

#define MATRIX4X4() \
    Matrix4x4 *m;   \
    Data_Get_Struct(self, Matrix4x4, m)

void Init_matrix_base(VALUE outer);

VALUE rb_matrix3x2_m11(VALUE self);
VALUE rb_matrix3x2_m12(VALUE self);
VALUE rb_matrix3x2_m21(VALUE self);
VALUE rb_matrix3x2_m22(VALUE self);
VALUE rb_matrix3x2_m31(VALUE self);
VALUE rb_matrix3x2_m32(VALUE self);

VALUE rb_matrix4x4_m11(VALUE self);
VALUE rb_matrix4x4_m12(VALUE self);
VALUE rb_matrix4x4_m13(VALUE self);
VALUE rb_matrix4x4_m14(VALUE self);

VALUE rb_matrix4x4_m21(VALUE self);
VALUE rb_matrix4x4_m22(VALUE self);
VALUE rb_matrix4x4_m23(VALUE self);
VALUE rb_matrix4x4_m24(VALUE self);

VALUE rb_matrix4x4_m31(VALUE self);
VALUE rb_matrix4x4_m32(VALUE self);
VALUE rb_matrix4x4_m33(VALUE self);
VALUE rb_matrix4x4_m34(VALUE self);

VALUE rb_matrix4x4_m41(VALUE self);
VALUE rb_matrix4x4_m42(VALUE self);
VALUE rb_matrix4x4_m43(VALUE self);
VALUE rb_matrix4x4_m44(VALUE self);

VALUE rb_matrix3x2_m11_set(VALUE self, VALUE value);
VALUE rb_matrix3x2_m12_set(VALUE self, VALUE value);
VALUE rb_matrix3x2_m21_set(VALUE self, VALUE value);
VALUE rb_matrix3x2_m22_set(VALUE self, VALUE value);
VALUE rb_matrix3x2_m31_set(VALUE self, VALUE value);
VALUE rb_matrix3x2_m32_set(VALUE self, VALUE value);

VALUE rb_matrix4x4_m11_set(VALUE self, VALUE value);
VALUE rb_matrix4x4_m12_set(VALUE self, VALUE value);
VALUE rb_matrix4x4_m13_set(VALUE self, VALUE value);
VALUE rb_matrix4x4_m14_set(VALUE self, VALUE value);

VALUE rb_matrix4x4_m21_set(VALUE self, VALUE value);
VALUE rb_matrix4x4_m22_set(VALUE self, VALUE value);
VALUE rb_matrix4x4_m23_set(VALUE self, VALUE value);
VALUE rb_matrix4x4_m24_set(VALUE self, VALUE value);

VALUE rb_matrix4x4_m31_set(VALUE self, VALUE value);
VALUE rb_matrix4x4_m32_set(VALUE self, VALUE value);
VALUE rb_matrix4x4_m33_set(VALUE self, VALUE value);
VALUE rb_matrix4x4_m34_set(VALUE self, VALUE value);

VALUE rb_matrix4x4_m41_set(VALUE self, VALUE value);
VALUE rb_matrix4x4_m42_set(VALUE self, VALUE value);
VALUE rb_matrix4x4_m43_set(VALUE self, VALUE value);
VALUE rb_matrix4x4_m44_set(VALUE self, VALUE value);

VALUE rb_matrix_base_map(VALUE self);
VALUE rb_matrix_base_map_bang(VALUE self);
VALUE rb_matrix_base_pow(VALUE self, VALUE exponent);

static inline VALUE rb_matrix_base_pow_s(VALUE klass, VALUE matrix, VALUE exponent);

#endif /* NUMERIX_MATRIX_BASE_H */