#ifndef NUMERIX_VECTOR_BASE_H
#define NUMERIX_VECTOR_BASE_H 1

#include "common.h"

#define VECTOR2() \
    Vector2 *v;   \
    Data_Get_Struct(self, Vector2, v)

#define VECTOR3() \
    Vector3 *v;   \
    Data_Get_Struct(self, Vector3, v)

#define VECTOR4() \
    Vector4 *v;   \
    Data_Get_Struct(self, Vector4, v)

void Init_vector_base(VALUE outer);

VALUE rb_vector_base_x(VALUE self);
VALUE rb_vector_base_y(VALUE self);
VALUE rb_vector_base_z(VALUE self);
VALUE rb_vector_base_w(VALUE self);

VALUE rb_vector_base_x_set(VALUE self, VALUE value);
VALUE rb_vector_base_y_set(VALUE self, VALUE value);
VALUE rb_vector_base_z_set(VALUE self, VALUE value);
VALUE rb_vector_base_w_set(VALUE self, VALUE value);

VALUE rb_vector_base_map(VALUE self);
VALUE rb_vector_base_map_bang(VALUE self);

#endif /* NUMERIX_VECTOR_BASE_H */