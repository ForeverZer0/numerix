#ifndef NUMERIX_VECTOR3_H
#define NUMERIX_VECTOR3_H 1

#include "common.h"
#include "vector_base.h"

void Init_vector3(VALUE outer);
static VALUE rb_vector3_alloc(VALUE klass);
VALUE rb_vector3_initialize(int argc, VALUE *argv, VALUE self);

// Instance
VALUE rb_vector3_length(VALUE self);
VALUE rb_vector3_length_squared(VALUE self);
VALUE rb_vector3_add(VALUE self, VALUE other);
VALUE rb_vector3_subtract(VALUE self, VALUE other);
VALUE rb_vector3_multiply(VALUE self, VALUE other);
VALUE rb_vector3_divide(VALUE self, VALUE other);
VALUE rb_vector3_equal(VALUE self, VALUE other);
VALUE rb_vector3_negate(VALUE self);
VALUE rb_vector3_one_p(VALUE self);
VALUE rb_vector3_zero_p(VALUE self);
VALUE rb_vector3_min_value(VALUE self);
VALUE rb_vector3_max_value(VALUE self);
VALUE rb_vector3_distance(VALUE self, VALUE other);
VALUE rb_vector3_distance_squared(VALUE self, VALUE other);
VALUE rb_vector3_normalize(VALUE self);
VALUE rb_vector3_lerp(VALUE self, VALUE other, VALUE amount);
VALUE rb_vector3_lerp_bang(VALUE self, VALUE other, VALUE amount);
VALUE rb_vector3_normalize_bang(VALUE self);
VALUE rb_vector3_transform(VALUE self, VALUE other);
VALUE rb_vector3_transform_bang(VALUE self, VALUE other);
VALUE rb_vector3_abs(VALUE self);
VALUE rb_vector3_sqrt(VALUE self);
VALUE rb_vector3_dot(VALUE self, VALUE other);
VALUE rb_vector3_clamp(VALUE self, VALUE min, VALUE max);
VALUE rb_vector3_clamp_bang(VALUE self, VALUE min, VALUE max);
VALUE rb_vector3_cross(VALUE self, VALUE other);
VALUE rb_vector3_cross_bang(VALUE self, VALUE other);
VALUE rb_vector3_reflect(VALUE self, VALUE other);
VALUE rb_vector3_reflect_bang(VALUE self, VALUE other);

// Conversion
VALUE rb_vector3_to_s(VALUE self);
VALUE rb_vector3_to_a(VALUE self);
VALUE rb_vector3_to_h(VALUE self);
VALUE rb_vector3_to_vec2(VALUE self);
VALUE rb_vector3_to_vec4(VALUE self);
VALUE rb_vector3_to_quaternion(VALUE self);
VALUE rb_vector3_to_plane(VALUE self);

// Class
VALUE rb_vector3_one(VALUE klass);
VALUE rb_vector3_unit_x(VALUE klass);
VALUE rb_vector3_unit_y(VALUE klass);
VALUE rb_vector3_unit_z(VALUE klass);
static inline VALUE rb_vector3_distance_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector3_distance_squared_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector3_normalize_s(VALUE klass, VALUE vector3);
static inline VALUE rb_vector3_cross_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector3_reflect_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector3_clamp_s(VALUE klass, VALUE vector, VALUE minimum, VALUE maximum);
static inline VALUE rb_vector3_lerp_s(VALUE klass, VALUE vec1, VALUE vec2, VALUE amount);
static inline VALUE rb_vector3_transform_s(VALUE klass, VALUE vector, VALUE matrix);
static inline VALUE rb_vector3_transform_normal_s(VALUE klass, VALUE vector, VALUE matrix);
static inline VALUE rb_vector3_dot_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector3_min_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector3_max_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector3_abs_s(VALUE klass, VALUE vec);
static inline VALUE rb_vector3_sqrt_s(VALUE klass, VALUE vec);
static inline VALUE rb_vector3_add_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector3_subtract_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector3_multiply_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector3_divide_s(VALUE klass, VALUE vec1, VALUE vec2);
static inline VALUE rb_vector3_negate_s(VALUE klass, VALUE vec);

// Internal
static inline void rb_vector3_cross_intern(Vector3 *vec1, Vector3 *vec2, Vector3 *result);
static inline void rb_vector3_normalize_intern(Vector3 *v, Vector3 *result);

#endif /* NUMERIX_VECTOR3_H */