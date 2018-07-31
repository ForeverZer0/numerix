#ifndef NUMERIX_PLANE_H
#define NUMERIX_PLANE_H 1

#include "common.h"
#include "matrix4x4.h"

#define PLANE() \
    Plane *p;   \
    Data_Get_Struct(self, Plane, p)

void Init_plane(VALUE outer);
static VALUE rb_plane_alloc(VALUE klass);
VALUE rb_plane_initialize(int argc, VALUE *argv, VALUE self);

// Instance
VALUE rb_plane_normal(VALUE self);
VALUE rb_plane_distance(VALUE self);
VALUE rb_plane_normal_set(VALUE self, VALUE value);
VALUE rb_plane_distance_set(VALUE self, VALUE value);
VALUE rb_plane_equal(VALUE self, VALUE other);
VALUE rb_plane_to_s(VALUE self);

// Class
VALUE rb_plane_from_vertices_s(VALUE klass, VALUE vert1, VALUE vert2, VALUE vert3);
static inline VALUE rb_plane_normalize_s(VALUE klass, VALUE plane);
static inline VALUE rb_plane_transform_s(VALUE klass, VALUE plane, VALUE matrix);
static inline VALUE rb_plane_dot_s(VALUE klass, VALUE plane, VALUE vec4);
static inline VALUE rb_plane_dot_coord_s(VALUE klass, VALUE plane, VALUE vec3);
static inline VALUE rb_plane_dot_normal_s(VALUE klass, VALUE plane, VALUE vec3);
static inline VALUE rb_plane_equal_s(VALUE klass, VALUE plane, VALUE other);

#endif /* NUMERIX_PLANE_H */