
#include "plane.h"

VALUE rb_cPlane;

void Init_plane(VALUE outer) {
    rb_cPlane = rb_define_class_under(outer, "Plane", rb_cNumerixStruct);
    rb_define_alloc_func(rb_cPlane, rb_plane_alloc);
    rb_define_method(rb_cPlane, "initialize", rb_plane_initialize, -1);

    // Instance
    rb_define_method(rb_cPlane, "normal", rb_plane_normal, 0);
    rb_define_method(rb_cPlane, "distance", rb_plane_distance, 0);
    rb_define_method(rb_cPlane, "normal=", rb_plane_normal_set, 1);
    rb_define_method(rb_cPlane, "distance=", rb_plane_distance_set, 1);
    rb_define_method(rb_cPlane, "==", rb_plane_equal, 1);

    // Conversion
    rb_define_method(rb_cPlane, "to_s", rb_plane_to_s, 0);

    // Class
    rb_define_singleton_method(rb_cPlane, "from_vertices", rb_plane_from_vertices_s, 3);
    rb_define_singleton_method(rb_cPlane, "normalize", rb_plane_normalize_s, 1);
    rb_define_singleton_method(rb_cPlane, "transfrom", rb_plane_transform_s, 2);
    rb_define_singleton_method(rb_cPlane, "dot", rb_plane_dot_s, 2);
    rb_define_singleton_method(rb_cPlane, "dot_coord", rb_plane_dot_coord_s, 2);
    rb_define_singleton_method(rb_cPlane, "dot_normal", rb_plane_dot_normal_s, 2);
    rb_define_singleton_method(rb_cPlane, "equals?", rb_plane_equal_s, 2);
  
}

static VALUE rb_plane_alloc(VALUE klass) {
    Plane *p = ALLOC(Plane);
    memset(p, 0, sizeof(Plane));
    return NUMERIX_WRAP(klass, p);
}

VALUE rb_plane_initialize(int argc, VALUE *argv, VALUE self) {
    PLANE();
    switch (argc)
    {
        case 0:
            break;
        case 1:
        {
            Vector4 *vec4;
            Data_Get_Struct(argv[0], Vector4, vec4);
            memcpy(p, vec4, sizeof(Vector4));
            break;
        }
        case 2:
        {
            Vector3 *vec3;
            Data_Get_Struct(argv[0], Vector3, vec3);
            memcpy(p, vec3, sizeof(Vector3));
            p->distance = NUM2FLT(argv[1]);
            break;
        }
        case 4:
        {
            p->normal.x = NUM2FLT(argv[0]);
            p->normal.y = NUM2FLT(argv[1]);
            p->normal.z = NUM2FLT(argv[2]);
            p->distance = NUM2FLT(argv[3]);
            break;
        }
        default:
            rb_raise(rb_eArgError, "wrong number of arguments (%d for 0, 1, 2, 4)", argc);
            break;

    }
    return Qnil;
}

VALUE rb_plane_normal(VALUE self) {
    PLANE();
    return NUMERIX_WRAP(rb_cVector3, &(p->normal));
}

VALUE rb_plane_distance(VALUE self) {
    PLANE();
    return DBL2NUM(p->distance);
}

VALUE rb_plane_normal_set(VALUE self, VALUE value) {
    PLANE();
    Vector3 *v3;
    Data_Get_Struct(value, Vector3, v3);
    memcpy(p, v3, sizeof(Vector3));
    return value;
}

VALUE rb_plane_distance_set(VALUE self, VALUE value) {
    PLANE();
    p->distance = NUM2FLT(value);
    return value;
}

VALUE rb_plane_equal(VALUE self, VALUE other) {
    return rb_plane_equal_s(CLASS_OF(self), self, other);
}

VALUE rb_plane_to_s(VALUE self) {
    PLANE();
    return rb_sprintf("{<%f, %f, %f>, %f}", p->normal.x, p->normal.y, p->normal.z, p->distance);
}


VALUE rb_plane_from_vertices_s(VALUE klass, VALUE vert1, VALUE vert2, VALUE vert3) {
    Vector3 *v1, *v2, *v3;
    Data_Get_Struct(vert1, Vector3, v1);
    Data_Get_Struct(vert2, Vector3, v2);
    Data_Get_Struct(vert3, Vector3, v3);

    float ax = v2->x - v1->x;
    float ay = v2->y - v1->y;
    float az = v2->z - v1->z;

    float bx = v3->x - v1->x;
    float by = v3->y - v1->y;
    float bz = v3->z - v1->z;

    // N=Cross(a,b)
    float nx = ay * bz - az * by;
    float ny = az * bx - ax * bz;
    float nz = ax * by - ay * bx;

    // Normalize(N)
    float invNorm = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);

    Plane *p = ALLOC(Plane);
    p->normal.x = nx * invNorm;
    p->normal.y = ny * invNorm;
    p->normal.z = nz * invNorm;
    p->distance = -(p->normal.x * v1->x + p->normal.y * v1->y + p->normal.z * v1->z);
    
    return NUMERIX_WRAP(klass, p);
}

VALUE rb_plane_normalize_s(VALUE klass, VALUE plane) {
    Plane *p, *result;
    Data_Get_Struct(plane, Plane, p);
    result = ALLOC(Plane);

    float f = p->normal.x * p->normal.x + p->normal.y * p->normal.y + p->normal.z * p->normal.z;

    if (fabsf(f - 1.0f) < FLT_EPSILON)
    {
        // It already normalized, so we don't need to further process.
        memcpy(result, p, sizeof(Plane)); 
    }
    else
    {
        float fInv = 1.0f / sqrtf(f);
        result->normal.x = p->normal.x * fInv;
        result->normal.y = p->normal.y * fInv;
        result->normal.z = p->normal.z * fInv;
        result->distance = p->distance * fInv;
    }

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_plane_transform_s(VALUE klass, VALUE plane, VALUE matrix) {
    Plane *p, *result;
    Data_Get_Struct(plane, Plane, p);
    result = ALLOC(Plane);

    if (NUMERIX_TYPE_P(matrix, rb_cMatrix4x4))
    {
        VALUE inverted = rb_matrix4x4_invert_s(CLASS_OF(matrix), matrix);
        Matrix4x4 *m;
        Data_Get_Struct(inverted, Matrix4x4, m);

        float x = p->normal.x, y = p->normal.y, z = p->normal.z, w = p->distance;

        result->normal.x = x * m->m11 + y * m->m12 + z * m->m13 + w * m->m14;
        result->normal.y = x * m->m21 + y * m->m22 + z * m->m23 + w * m->m24;
        result->normal.z = x * m->m31 + y * m->m32 + z * m->m33 + w * m->m34;
        result->distance = x * m->m41 + y * m->m42 + z * m->m43 + w * m->m44;
    }
    else 
    {
        Quaternion *q;
        Data_Get_Struct(matrix, Quaternion, q);

        // Compute rotation matrix.
        float x2 = q->x + q->x;
        float y2 = q->y + q->y;
        float z2 = q->z + q->z;

        float wx2 = q->w * x2;
        float wy2 = q->w * y2;
        float wz2 = q->w * z2;
        float xx2 = q->x * x2;
        float xy2 = q->x * y2;
        float xz2 = q->x * z2;
        float yy2 = q->y * y2;
        float yz2 = q->y * z2;
        float zz2 = q->z * z2;

        float m11 = 1.0f - yy2 - zz2;
        float m21 = xy2 - wz2;
        float m31 = xz2 + wy2;

        float m12 = xy2 + wz2;
        float m22 = 1.0f - xx2 - zz2;
        float m32 = yz2 - wx2;

        float m13 = xz2 - wy2;
        float m23 = yz2 + wx2;
        float m33 = 1.0f - xx2 - yy2;

        float x = p->normal.x, y = p->normal.y, z = p->normal.z;

        result->normal.x = x * m11 + y * m21 + z * m31;
        result->normal.y = x * m12 + y * m22 + z * m32;
        result->normal.y = x * m13 + y * m23 + z * m33;
        result->distance = p->distance;
    }

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_plane_dot_s(VALUE klass, VALUE plane, VALUE vec4) {
    Plane *p;
    Vector4 *v;
    Data_Get_Struct(plane, Plane, p);
    Data_Get_Struct(vec4, Vector4, v);

    return DBL2NUM(p->normal.x * v->x + p->normal.y * v->y + p->normal.z * v->z + p->distance * v->w);
}

static inline VALUE rb_plane_dot_coord_s(VALUE klass, VALUE plane, VALUE vec3) {
    Plane *p;
    Vector3 *v;
    Data_Get_Struct(plane, Plane, p);
    Data_Get_Struct(vec3, Vector3, v);
    return DBL2NUM(p->normal.x * v->x + p->normal.y * v->y + p->normal.z * v->z + p->distance);

}

static inline VALUE rb_plane_dot_normal_s(VALUE klass, VALUE plane, VALUE vec3) {
    Plane *p;
    Vector3 *v;
    Data_Get_Struct(plane, Plane, p);
    Data_Get_Struct(vec3, Vector3, v);

    return DBL2NUM(p->normal.x * v->x + p->normal.y * v->y + p->normal.z * v->z);
}

static inline VALUE rb_plane_equal_s(VALUE klass, VALUE plane, VALUE other) {
    if (CLASS_OF(plane) != klass || CLASS_OF(other) != klass)
        return Qfalse;
    Plane *p1, *p2;
    Data_Get_Struct(plane, Plane, p1);
    Data_Get_Struct(other, Plane, p2);

    return p1->normal.x == p1->normal.x && p1->normal.y == p1->normal.y &&
        p1->normal.z == p1->normal.z && p1->distance == p1->distance ? Qtrue : Qfalse;
}