#ifndef NUMERIX_VECTOR2_H
#define NUMERIX_VECTOR2_H 1

#include "common.h"
#include "vector_base.h"

void Init_vector2(VALUE outer);
static VALUE rb_vector2_alloc(VALUE klass);
VALUE rb_vector2_initialize(int argc, VALUE *argv, VALUE self);

// Instance
VALUE rb_vector2_length(VALUE self);
VALUE rb_vector2_length_squared(VALUE self);
VALUE rb_vector2_add(VALUE self, VALUE other);
VALUE rb_vector2_subtract(VALUE self, VALUE other);
VALUE rb_vector2_multiply(VALUE self, VALUE other);
VALUE rb_vector2_divide(VALUE self, VALUE other);
VALUE rb_vector2_equal(VALUE self, VALUE other);
VALUE rb_vector2_negate(VALUE self);
VALUE rb_vector2_one_p(VALUE self);
VALUE rb_vector2_zero_p(VALUE self);
VALUE rb_vector2_min_value(VALUE self);
VALUE rb_vector2_max_value(VALUE self);
VALUE rb_vector2_distance(VALUE self, VALUE other);
VALUE rb_vector2_distance_squared(VALUE self, VALUE other);
VALUE rb_vector2_normalize(VALUE self);
VALUE rb_vector2_normalize_bang(VALUE self);
VALUE rb_vector2_lerp(VALUE self, VALUE other, VALUE amount);
VALUE rb_vector2_lerp_bang(VALUE self, VALUE other, VALUE amount);
VALUE rb_vector2_transform(VALUE self, VALUE other);
VALUE rb_vector2_transform_bang(VALUE self, VALUE other);
VALUE rb_vector2_abs(VALUE self);
VALUE rb_vector2_sqrt(VALUE self);
VALUE rb_vector2_dot(VALUE self, VALUE other);
VALUE rb_vector2_clamp(VALUE self, VALUE min, VALUE max);
VALUE rb_vector2_clamp_bang(VALUE self, VALUE min, VALUE max);
VALUE rb_vector2_reflect(VALUE self, VALUE other);
VALUE rb_vector2_reflect_bang(VALUE self, VALUE other);

// Conversion
VALUE rb_vector2_to_s(VALUE self);
VALUE rb_vector2_to_a(VALUE self);
VALUE rb_vector2_to_h(VALUE self);
VALUE rb_vector2_to_vec3(VALUE self);
VALUE rb_vector2_to_vec4(VALUE self);

// Class
VALUE rb_vector2_one(VALUE klass);
VALUE rb_vector2_unit_x(VALUE klass);
VALUE rb_vector2_unit_y(VALUE klass);
VALUE rb_vector2_create_norm(VALUE klass, VALUE x, VALUE y);
// static inline VALUE rb_vector2_distance_s(VALUE klass, VALUE vec1, VALUE vec2);
// static inline VALUE rb_vector2_distance_squared_s(VALUE klass, VALUE vec1, VALUE vec2);
// static inline VALUE rb_vector2_normalize_s(VALUE klass, VALUE vector2);
// static inline VALUE rb_vector2_reflect_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector2_clamp_s(VALUE klass, VALUE vector, VALUE min, VALUE max);
static inline VALUE rb_vector2_lerp_s(VALUE klass, VALUE vec1, VALUE vec2, VALUE amount);
static inline VALUE rb_vector2_transform_s(VALUE klass, VALUE vector, VALUE matrix);
static inline VALUE rb_vector2_transform_normal_s(VALUE klass, VALUE vector, VALUE matrix);
static inline VALUE rb_vector2_min_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector2_max_s(VALUE klass, VALUE vec1, VALUE vec2);
// static inline VALUE rb_vector2_abs_s(VALUE klass, VALUE vec);
// static inline VALUE rb_vector2_sqrt_s(VALUE klass, VALUE vec);
// static inline VALUE rb_vector2_add_s(VALUE klass, VALUE vec1, VALUE vec2);
// static inline VALUE rb_vector2_subtract_s(VALUE klass, VALUE vec1, VALUE vec2);
// static inline VALUE rb_vector2_multiply_s(VALUE klass, VALUE vec, VALUE other);
// static inline VALUE rb_vector2_divide_s(VALUE klass, VALUE vec, VALUE other);
// static inline VALUE rb_vector2_negate_s(VALUE klass, VALUE vec);
// static inline VALUE rb_vector2_dot_s(VALUE klass, VALUE vec1, VALUE vec2);

#endif /* NUMERIX_VECTOR2_H */