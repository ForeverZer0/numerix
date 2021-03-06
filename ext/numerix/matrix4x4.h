#ifndef NUMERIX_MATRIX4X4_H
#define NUMERIX_MATRIX4X4_H 1

#include "common.h"
#include "matrix_base.h"
#include "plane.h"
#include "quaternion.h"

#define MATRIX4X4() \
    Matrix4x4 *m;   \
    Data_Get_Struct(self, Matrix4x4, m)

typedef struct CanonicalBasis {
    Vector3 row0;
    Vector3 row1;
    Vector3 row2;
} CanonicalBasis;

typedef struct VectorBasis {
    Vector3 *element0;
    Vector3 *element1;
    Vector3 *element2;
} VectorBasis;

void Init_matrix4x4(VALUE outer);
static VALUE rb_matrix4x4_allocate(VALUE klass);
VALUE rb_matrix4x4_initialize(int argc, VALUE *argv, VALUE self);

// Instance
VALUE rb_matrix4x4_identity_p(VALUE self);
VALUE rb_matrix4x4_translation(VALUE self);
VALUE rb_matrix4x4_translation_set(VALUE self, VALUE value);
VALUE rb_matrix4x4_determinant(VALUE self);
VALUE rb_matrix4x4_add(VALUE self, VALUE other);
VALUE rb_matrix4x4_subtract(VALUE self, VALUE other);
VALUE rb_matrix4x4_multiply(VALUE self, VALUE other);
VALUE rb_matrix4x4_negate(VALUE self);
VALUE rb_matrix4x4_equal(VALUE self, VALUE other);
VALUE rb_matrix4x4_pow(VALUE self, VALUE exponent);
VALUE rb_matrix4x4_row(VALUE self, VALUE row);
VALUE rb_matrix4x4_column(VALUE self, VALUE column);
VALUE rb_matrix4x4_each_row(VALUE self);
VALUE rb_matrix4x4_each_column(VALUE self);
VALUE rb_matrix4x4_aref(int argc, VALUE *argv, VALUE self);
VALUE rb_matrix4x4_aset(int argc, VALUE *argv, VALUE self);
VALUE rb_matrix4x4_invert(VALUE self);
VALUE rb_matrix4x4_transform(VALUE self, VALUE quaternion);
VALUE rb_matrix4x4_transform_bang(VALUE self, VALUE quaternion);
VALUE rb_matrix4x4_transpose(VALUE self);
VALUE rb_matrix4x4_lerp(VALUE self, VALUE other, VALUE amount);
VALUE rb_matrix4x4_lerp_bang(VALUE self, VALUE other, VALUE amount);
VALUE rb_matrix4x4_map(VALUE self);
VALUE rb_matrix4x4_map_bang(VALUE self);

// Conversion
VALUE rb_matrix4x4_to_s(VALUE self);
VALUE rb_matrix4x4_to_a(VALUE self);
VALUE rb_matrix4x4_to_h(VALUE self);
// TODO to_mat3x2

// // Class
VALUE rb_matrix4x4_identity(VALUE klass);
VALUE rb_matrix4x4_create_billboard(VALUE klass, VALUE position, VALUE camera, VALUE up, VALUE forward);
VALUE rb_matrix4x4_create_constrained_billboard(VALUE klass, VALUE position, VALUE rotate, VALUE camera, VALUE up, VALUE forward);
VALUE rb_matrix4x4_create_translation(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_create_scale(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_create_rotation_x(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_create_rotation_y(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_create_rotation_z(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_from_axis_angle(VALUE klass, VALUE axis, VALUE angle);
VALUE rb_matrix4x4_create_perspective_fov(VALUE klass, VALUE fieldOfView, VALUE aspectRatio, VALUE nearDist, VALUE farDist);
VALUE rb_matrix4x4_create_perspective(VALUE klass, VALUE width, VALUE height, VALUE nearDist, VALUE farDist);
VALUE rb_matrix4x4_create_perspective_off_center(VALUE klass, VALUE left, VALUE right, VALUE bottom, VALUE top, VALUE nearDist, VALUE farDist);
VALUE rb_matrix4x4_create_orthographic(VALUE klass, VALUE width, VALUE height, VALUE zNearPlane, VALUE zFarPlane);
VALUE rb_matrix4x4_create_orthographic_off_center(VALUE klass, VALUE left, VALUE right, VALUE bottom, VALUE top, VALUE zNearPlane, VALUE zFarPlane);
VALUE rb_matrix4x4_create_look_at(VALUE klass, VALUE camPos, VALUE camTarget, VALUE camUp);
VALUE rb_matrix4x4_create_world(VALUE klass, VALUE position, VALUE forward, VALUE up);
VALUE rb_matrix4x4_from_quaternion(VALUE klass, VALUE quaternion);
VALUE rb_matrix4x4_from_yaw_pitch_roll(VALUE klass, VALUE yaw, VALUE pitch, VALUE roll);
VALUE rb_matrix4x4_create_shadow(VALUE klass, VALUE light, VALUE plane);
VALUE rb_matrix4x4_create_reflection(VALUE klass, VALUE plane);
VALUE rb_matrix4x4_lerp_s(VALUE klass, VALUE matrix1, VALUE matrix2, VALUE amount);

// Internal
static inline void numerix_vec3_normalize(Vector3 *v);
static inline void numerix_vec3_cross(Vector3 *v1, Vector3 *v2, Vector3 *result);
static inline float numerix_vec3_dot(Vector3 *v1, Vector3 *v2);
static inline void numerix_cross_norm(Vector3 *v1, Vector3 *v2, Vector3 *result);

#endif /* NUMERIX_MATRIX4X4_H */