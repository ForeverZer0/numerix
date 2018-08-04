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
VALUE rb_plane_equal(VALUE self, VALUE other);
VALUE rb_plane_transform(VALUE self, VALUE matrix);
VALUE rb_plane_transform_bang(VALUE self, VALUE matrix);
VALUE rb_plane_dot(VALUE self, VALUE vec4);
VALUE rb_plane_dot_coord(VALUE self, VALUE vec3);
VALUE rb_plane_dot_normal(VALUE self, VALUE vec3);
VALUE rb_plane_normalize(VALUE self);
VALUE rb_plane_normalize_bang(VALUE self);

// Class
VALUE rb_plane_from_vertices_s(VALUE klass, VALUE vert1, VALUE vert2, VALUE vert3);

#endif /* NUMERIX_PLANE_H */