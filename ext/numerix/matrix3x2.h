#ifndef NUMERIX_MATRIX3X2_H
#define NUMERIX_MATRIX3X2_H 1

#include "common.h"
#include "matrix_base.h"

#define MATRIX3X2() \
    Matrix3x2 *m;   \
    Data_Get_Struct(self, Matrix3x2, m)

void Init_matrix3x2(VALUE outer);
static VALUE rb_matrix3x2_allocate(VALUE klass);
VALUE rb_matrix3x2_initialize(int argc, VALUE *argv, VALUE self);

// Instance
VALUE rb_matrix3x2_identity_p(VALUE self);
VALUE rb_matrix3x2_translation(VALUE self);
VALUE rb_matrix3x2_translation_set(VALUE self, VALUE value);
VALUE rb_matrix3x2_determinant(VALUE self);
VALUE rb_matrix3x2_negate(VALUE self);
VALUE rb_matrix3x2_add(VALUE self, VALUE other);
VALUE rb_matrix3x2_subtract(VALUE self, VALUE other);
VALUE rb_matrix3x2_multiply(VALUE self, VALUE other);
VALUE rb_matrix3x2_equal(VALUE self, VALUE other);
VALUE rb_matrix3x2_to_s(VALUE self);

// Class
VALUE rb_matrix3x2_identity(VALUE klass);
VALUE rb_matrix3x2_create_translation(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix3x2_create_scale(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix3x2_create_skew(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix3x2_create_rotation(int argc, VALUE *argv, VALUE klass);
static inline VALUE rb_matrix3x2_invert_s(VALUE klass, VALUE matrix);
static inline VALUE rb_matrix3x2_lerp_s(VALUE klass, VALUE matrix1, VALUE matrix2, VALUE amount);
static inline VALUE rb_matrix3x2_negate_s(VALUE klass, VALUE matrix);
static inline VALUE rb_matrix3x2_add_s(VALUE klass, VALUE matrix1, VALUE matrix2);
static inline VALUE rb_matrix3x2_subtract_s(VALUE klass, VALUE matrix1, VALUE matrix2);
static inline VALUE rb_matrix3x2_multiply_s(VALUE klass, VALUE matrix, VALUE other);
static inline VALUE rb_matrix3x2_equal_s(VALUE klass, VALUE matrix, VALUE other);

#endif /* NUMERIX_MATRIX3X2_H */