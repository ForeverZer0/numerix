#ifndef NUMERIX_VECTOR4_H
#define NUMERIX_VECTOR4_H 1

#include "common.h"
#include "vector_base.h"

void Init_vector4(VALUE outer);
static VALUE rb_vector4_alloc(VALUE klass);
VALUE rb_vector4_initialize(int argc, VALUE *argv, VALUE self);

// Instance
VALUE rb_vector4_length(VALUE self);
VALUE rb_vector4_length_squared(VALUE self);
VALUE rb_vector4_add(VALUE self, VALUE other);
VALUE rb_vector4_subtract(VALUE self, VALUE other);
VALUE rb_vector4_multiply(VALUE self, VALUE other);
VALUE rb_vector4_divide(VALUE self, VALUE other);
VALUE rb_vector4_equal(VALUE self, VALUE other);
VALUE rb_vector4_negate(VALUE self);
VALUE rb_vector4_one_p(VALUE self);
VALUE rb_vector4_zero_p(VALUE self);
VALUE rb_vector4_min_value(VALUE self);
VALUE rb_vector4_max_value(VALUE self);
VALUE rb_vector4_distance(VALUE self, VALUE other);
VALUE rb_vector4_distance_squared(VALUE self, VALUE other);
VALUE rb_vector4_normalize(VALUE self);
VALUE rb_vector4_normalize_bang(VALUE self);
VALUE rb_vector4_lerp(VALUE self, VALUE other, VALUE amount);
VALUE rb_vector4_lerp_bang(VALUE self, VALUE other, VALUE amount);
VALUE rb_vector4_transform(VALUE self, VALUE other);
VALUE rb_vector4_transform_bang(VALUE self, VALUE other);
VALUE rb_vector4_abs(VALUE self);
VALUE rb_vector4_sqrt(VALUE self);
VALUE rb_vector4_dot(VALUE self, VALUE other);
VALUE rb_vector4_clamp(VALUE self, VALUE min, VALUE max);
VALUE rb_vector4_clamp_bang(VALUE self, VALUE min, VALUE max);

// Conversion
VALUE rb_vector4_to_s(VALUE self);
VALUE rb_vector4_to_a(VALUE self);
VALUE rb_vector4_to_h(VALUE self);
VALUE rb_vector4_to_vec2(VALUE self);
VALUE rb_vector4_to_vec3(VALUE self);
VALUE rb_vector4_to_quaternion(VALUE self);
VALUE rb_vector4_to_plane(VALUE self);

// Class
VALUE rb_vector4_one(VALUE klass);
VALUE rb_vector4_unit_x(VALUE klass);
VALUE rb_vector4_unit_y(VALUE klass);
VALUE rb_vector4_unit_z(VALUE klass);
VALUE rb_vector4_unit_w(VALUE klass);
VALUE rb_vector4_create_norm(VALUE klass, VALUE x, VALUE y, VALUE z, VALUE w);
static inline VALUE rb_vector4_distance_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector4_distance_squared_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector4_normalize_s(VALUE klass, VALUE vector4);
static inline VALUE rb_vector4_clamp_s(VALUE klass, VALUE vector, VALUE minimum, VALUE maximum);
static inline VALUE rb_vector4_lerp_s(VALUE klass, VALUE vec1, VALUE vec2, VALUE amount);
static inline VALUE rb_vector4_transform_s(VALUE klass, VALUE vector, VALUE matrix);
static inline VALUE rb_vector4_dot_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector4_min_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector4_max_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector4_abs_s(VALUE klass, VALUE vec);
static inline VALUE rb_vector4_sqrt_s(VALUE klass, VALUE vec);
static inline VALUE rb_vector4_add_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector4_subtract_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector4_multiply_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector4_divide_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector4_negate_s(VALUE klass, VALUE vec);

// Internal
static inline void rb_vector4_normalize_intern(Vector4 *v, Vector4 *result);

#endif /* NUMERIX_VECTOR4_H */