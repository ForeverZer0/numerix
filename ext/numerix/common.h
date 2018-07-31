#ifndef NUMERIX_COMMON_H
#define NUMERIX_COMMON_H 1

#include "ruby.h"

#define NUMERIX_MIN(a, b) (a < b ? a : b)
#define NUMERIX_MAX(a, b) (a > b ? a : b)
#define NUMERIX_CLAMP(value, min, max) (value < min ? min : value > max ? max : value)

#define NUMERIX_TYPE_P(obj, klass) (rb_obj_is_kind_of(obj, klass) == Qtrue)
#define NUMERIX_INHERIT_P(klass, super) (rb_class_inherited_p(klass, super) == Qtrue)

#define NUMERIX_PI 3.141593f
#define NUMERIX_HALF_PI 1.570796f

#define NUM2FLT(value) ((float) rb_num2dbl(value))
#define NUMERIX_WRAP(klass, ptr) Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, ptr)

#define CLASS_NAME(obj) rb_class2name(CLASS_OF(obj))

typedef struct Vector2 {
    float x; /* The X component of the vector. */
    float y; /* The Y component of the vector. */
} Vector2;

typedef struct Vector3 {
    float x; /* The X component of the vector. */
    float y; /* The Y component of the vector. */
    float z; /* The Z component of the vector. */
} Vector3;

typedef struct Vector4 {
    float x; /* The X component of the vector. */
    float y; /* The Y component of the vector. */
    float z; /* The Z component of the vector. */
    float w; /* The W component of the vector. */
} Vector4;

typedef struct Quaternion {
    float x; /* Specifies the X-value of the vector component of the Quaternion. */
    float y; /* Specifies the Y-value of the vector component of the Quaternion. */
    float z; /* Specifies the Z-value of the vector component of the Quaternion. */
    float w; /* Specifies the rotation component of the Quaternion. */
} Quaternion;

typedef struct Plane {
    Vector3 normal; /* The normal vector of the Plane. */
    float distance; /* The distance of the Plane along its normal from the origin. */
} Plane;

typedef struct Matrix3x2 {
    float m11; /* Value at row 1, column 1 of the matrix. */
    float m12; /* Value at row 1, column 2 of the matrix. */

    float m21; /* Value at row 2, column 1 of the matrix. */
    float m22; /* Value at row 2, column 2 of the matrix. */

    float m31; /* Value at row 3, column 1 of the matrix. */
    float m32; /* Value at row 3, column 2 of the matrix. */
} Matrix3x2;

typedef struct Matrix4x4 {
    float m11; /* Value at row 1, column 1 of the matrix. */
    float m12; /* Value at row 1, column 2 of the matrix. */
    float m13; /* Value at row 1, column 3 of the matrix. */
    float m14; /* Value at row 1, column 4 of the matrix. */

    float m21; /* Value at row 2, column 1 of the matrix. */
    float m22; /* Value at row 2, column 2 of the matrix. */
    float m23; /* Value at row 2, column 3 of the matrix. */
    float m24; /* Value at row 2, column 4 of the matrix. */

    float m31; /* Value at row 3, column 1 of the matrix. */
    float m32; /* Value at row 3, column 2 of the matrix. */
    float m33; /* Value at row 3, column 3 of the matrix. */
    float m34; /* Value at row 3, column 4 of the matrix. */

    float m41; /* Value at row 4, column 1 of the matrix. */
    float m42; /* Value at row 4, column 2 of the matrix. */
    float m43; /* Value at row 4, column 3 of the matrix. */
    float m44; /* Value at row 4, column 4 of the matrix. */
} Matrix4x4;

extern VALUE rb_mNumerix;
extern VALUE rb_cNumerixStruct;
extern VALUE rb_cVectorBase;
extern VALUE rb_cMatrixBase;
extern VALUE rb_cVector2;
extern VALUE rb_cVector3;
extern VALUE rb_cVector4;
extern VALUE rb_cMatrix3x2;
extern VALUE rb_cMatrix4x4;
extern VALUE rb_cQuaternion;
extern VALUE rb_cPlane;

#endif /* NUMERIX_COMMON_H */