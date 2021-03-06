#ifndef NUMERIX_QUATERNION_H
#define NUMERIX_QUATERNION_H 1

#include "common.h"
#include "vector_base.h"

#define QUATERNION() \
    Quaternion *q;   \
    Data_Get_Struct(self, Quaternion, q);

void Init_quaternion(VALUE outer);
VALUE rb_quaternion_alloc(VALUE klass);
VALUE rb_quaternion_initialize(int argc, VALUE *argv, VALUE self);

// Instance
VALUE rb_quaternion_identity_p(VALUE self);
VALUE rb_quaternion_length(VALUE self);
VALUE rb_quaternion_length_squared(VALUE self);
VALUE rb_quaternion_negate(VALUE self);
VALUE rb_quaternion_add(VALUE self, VALUE other);
VALUE rb_quaternion_subtract(VALUE self, VALUE other);
VALUE rb_quaternion_multiply(VALUE self, VALUE other);
VALUE rb_quaternion_divide(VALUE self, VALUE other);
VALUE rb_quaternion_equal(VALUE self, VALUE other);
VALUE rb_quaternion_normalize(VALUE self);
VALUE rb_quaternion_normalize_bang(VALUE self);
VALUE rb_quaternion_conjugate(VALUE self);
VALUE rb_quaternion_conjugate_bang(VALUE self);
VALUE rb_quaternion_inverse(VALUE self);
VALUE rb_quaternion_dot(VALUE self, VALUE other);
VALUE rb_quaternion_concatenate(VALUE self, VALUE other);
VALUE rb_quaternion_concatenate_bang(VALUE self, VALUE other);
VALUE rb_quaternion_lerp(VALUE self, VALUE other, VALUE amount);
VALUE rb_quaternion_lerp_bang(VALUE self, VALUE other, VALUE amount);
VALUE rb_quaternion_slerp(VALUE self, VALUE other, VALUE amount);
VALUE rb_quaternion_slerp_bang(VALUE self, VALUE other, VALUE amount);

// Conversion
VALUE rb_quaternion_to_s(VALUE self);
VALUE rb_quaternion_to_a(VALUE self);
VALUE rb_quaternion_to_h(VALUE self);
VALUE rb_quaternion_to_vec4(VALUE self);

// Class
VALUE rb_quaternion_identity(VALUE klass);
VALUE rb_quaternion_from_axis_angle(VALUE klass, VALUE vec3, VALUE angle);
VALUE rb_quaternion_from_yaw_pitch_roll(VALUE klass, VALUE yaw, VALUE pitch, VALUE roll);
VALUE rb_quaternion_from_rotation_matrix(VALUE klass, VALUE matrix);

static inline VALUE rb_quaternion_slerp_s(VALUE klass, VALUE quaternion1, VALUE quaternion2, VALUE amount);
static inline VALUE rb_quaternion_lerp_s(VALUE klass, VALUE quaternion1, VALUE quaternion2, VALUE amount);

#endif /* NUMERIX_QUATERNION_H */