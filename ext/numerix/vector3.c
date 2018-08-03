
#include "vector3.h"


void Init_vector3(VALUE outer) {
    
    rb_define_alloc_func(rb_cVector3, rb_vector3_alloc);

    // Instance Methods
    rb_define_method(rb_cVector3, "initialize", rb_vector3_initialize, -1);
    rb_define_method(rb_cVector3, "length", rb_vector3_length, 0);
    rb_define_method(rb_cVector3, "length_squared", rb_vector3_length_squared, 0);
    rb_define_method(rb_cVector3, "one?", rb_vector3_one_p, 0);
    rb_define_method(rb_cVector3, "zero?", rb_vector3_zero_p, 0);
    rb_define_method(rb_cVector3, "min_value", rb_vector3_min_value, 0);
    rb_define_method(rb_cVector3, "max_value", rb_vector3_max_value, 0);
    rb_define_method(rb_cVector3, "distance", rb_vector3_distance, 1);
    rb_define_method(rb_cVector3, "distance_squared", rb_vector3_distance_squared, 1);
    rb_define_method(rb_cVector3, "normalize", rb_vector3_normalize, 0);
    rb_define_method(rb_cVector3, "normalize!", rb_vector3_normalize_bang, 0);
    rb_define_method(rb_cVector3, "lerp", rb_vector3_lerp, 2);
    rb_define_method(rb_cVector3, "lerp!", rb_vector3_lerp_bang, 2);
    rb_define_method(rb_cVector3, "transform", rb_vector3_transform, 1);
    rb_define_method(rb_cVector3, "transform!", rb_vector3_transform_bang, 1);
    rb_define_method(rb_cVector3, "abs", rb_vector3_abs, 0);
    rb_define_method(rb_cVector3, "sqrt", rb_vector3_sqrt, 0);
    rb_define_method(rb_cVector3, "dot", rb_vector3_dot, 1);
    rb_define_method(rb_cVector3, "clamp", rb_vector3_clamp, 2);
    rb_define_method(rb_cVector3, "clamp!", rb_vector3_clamp_bang, 2);
    rb_define_method(rb_cVector3, "cross", rb_vector3_cross, 1);
    rb_define_method(rb_cVector3, "cross!", rb_vector3_cross_bang, 1);
    rb_define_method(rb_cVector3, "reflect", rb_vector3_reflect, 1);
    rb_define_method(rb_cVector3, "reflect!", rb_vector3_reflect_bang, 1);

    // Conversion
    rb_define_method(rb_cVector3, "to_s", rb_vector3_to_s, 0);
    rb_define_method(rb_cVector3, "to_a", rb_vector3_to_a, 0);
    rb_define_method(rb_cVector3, "to_h", rb_vector3_to_h, 0);
    rb_define_method(rb_cVector3, "to_quaternion", rb_vector3_to_quaternion, 0);
    rb_define_method(rb_cVector3, "to_plane", rb_vector3_to_plane, 0);
    rb_define_method(rb_cVector3, "to_vec2", rb_vector3_to_vec2, 0);
    rb_define_method(rb_cVector3, "to_vec4", rb_vector3_to_vec4, 0);

    // Operators
    rb_define_method(rb_cVector3, "+", rb_vector3_add, 1);
    rb_define_method(rb_cVector3, "-", rb_vector3_subtract, 1);
    rb_define_method(rb_cVector3, "*", rb_vector3_multiply, 1);
    rb_define_method(rb_cVector3, "/", rb_vector3_divide, 1);
    rb_define_method(rb_cVector3, "==", rb_vector3_equal, 1);
    rb_define_method(rb_cVector3, "-@", rb_vector3_negate, 0);

    // Singleton Methods
    rb_define_singleton_method(rb_cVector3, "zero", rb_vector3_alloc, 0);
    rb_define_singleton_method(rb_cVector3, "one", rb_vector3_one, 0);
    rb_define_singleton_method(rb_cVector3, "unit_x", rb_vector3_unit_x, 0);
    rb_define_singleton_method(rb_cVector3, "unit_y", rb_vector3_unit_y, 0);
    rb_define_singleton_method(rb_cVector3, "unit_z", rb_vector3_unit_z, 0);
    rb_define_singleton_method(rb_cVector3, "distance", rb_vector3_distance_s, 2);
    rb_define_singleton_method(rb_cVector3, "distance_squared", rb_vector3_distance_squared_s, 2);
    rb_define_singleton_method(rb_cVector3, "normalize", rb_vector3_normalize_s, 1);
    rb_define_singleton_method(rb_cVector3, "cross", rb_vector3_cross_s, 2);
    rb_define_singleton_method(rb_cVector3, "reflect", rb_vector3_reflect_s, 2);
    rb_define_singleton_method(rb_cVector3, "clamp", rb_vector3_clamp_s, 3);
    rb_define_singleton_method(rb_cVector3, "lerp", rb_vector3_lerp_s, 3);
    rb_define_singleton_method(rb_cVector3, "transform", rb_vector3_transform_s, 2);
    rb_define_singleton_method(rb_cVector3, "transform_normal", rb_vector3_transform_normal_s, 2);
    rb_define_singleton_method(rb_cVector3, "min", rb_vector3_min_s, 2);
    rb_define_singleton_method(rb_cVector3, "max", rb_vector3_max_s, 2);
    rb_define_singleton_method(rb_cVector3, "abs", rb_vector3_abs_s, 1);
    rb_define_singleton_method(rb_cVector3, "sqrt", rb_vector3_sqrt_s, 1);
    rb_define_singleton_method(rb_cVector3, "dot", rb_vector3_dot_s, 2);
    rb_define_singleton_method(rb_cVector3, "add", rb_vector3_add_s, 2);
    rb_define_singleton_method(rb_cVector3, "subtract", rb_vector3_subtract_s, 2);
    rb_define_singleton_method(rb_cVector3, "multiply", rb_vector3_multiply_s, 2);
    rb_define_singleton_method(rb_cVector3, "divide", rb_vector3_divide_s, 2);
    rb_define_singleton_method(rb_cVector3, "negate", rb_vector3_negate_s, 1);
}

static inline void rb_vector3_cross_intern(Vector3 *vec1, Vector3 *vec2, Vector3 *result) {
    result->x = vec1->y * vec2->z - vec1->z * vec2->y;
    result->y = vec1->z * vec2->x - vec1->x * vec2->z;
    result->z = vec1->x * vec2->y - vec1->y * vec2->x;
}

static inline void rb_vector3_normalize_intern(Vector3 *v, Vector3 *result) {
    float inv = 1.0f / sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
    result->x = v->x * inv;
    result->y = v->y * inv;
    result->z = v->z * inv;
}

static VALUE rb_vector3_alloc(VALUE klass) {
    void *v = ALLOC(Vector3);
    memset(v, 0, sizeof(Vector3));
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector3_initialize(int argc, VALUE *argv, VALUE self) {
    VECTOR3();
    switch (argc)
    {
        case 0:
            break;
        case 1:
        {
            float value = NUM2FLT(argv[0]);
            v->x = value;
            v->y = value;
            v->z = value;
            break;
        }
        case 2:
        {
            Vector2 *v2;
            Data_Get_Struct(argv[0], Vector2, v2);
            v->x = v2->x;
            v->y = v2->y;
            v->z = NUM2FLT(argv[1]);
            break;
        }
        case 3:
        {
            v->x = NUM2FLT(argv[0]);
            v->y = NUM2FLT(argv[1]);
            v->z = NUM2FLT(argv[2]);
            break;
        }
        default:
            rb_raise(rb_eArgError, "wrong number of arguments (%d for 0, 1, 2, 3)", argc);
            break;

    }
    return Qnil;
}

VALUE rb_vector3_one(VALUE klass) {
    Vector3 *v = ALLOC(Vector3);
    v->x = 1.0f;
    v->y = 1.0f;
    v->z = 1.0f;
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector3_unit_x(VALUE klass) {
    Vector3 *v = ALLOC(Vector3);
    v->x = 1.0f;
    v->y = 0.0f;
    v->z = 0.0f;
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector3_unit_y(VALUE klass) {
    Vector3 *v = ALLOC(Vector3);
    v->x = 0.0f;
    v->y = 1.0f;
    v->z = 0.0f;
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector3_unit_z(VALUE klass) {
    Vector3 *v = ALLOC(Vector3);
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 1.0f;
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector3_length(VALUE self) {
    VECTOR3();
    return DBL2NUM(sqrtf(v->x * v->x + v->y * v->y + v->z * v->z));
}

VALUE rb_vector3_length_squared(VALUE self) {
    VECTOR3();
    return DBL2NUM(v->x * v->x + v->y * v->y + v->z * v->z); 
}

VALUE rb_vector3_add(VALUE self, VALUE other) {
    return rb_vector3_add_s(CLASS_OF(self), self, other);
}

VALUE rb_vector3_subtract(VALUE self, VALUE other) {
    return rb_vector3_subtract_s(CLASS_OF(self), self, other);
}

VALUE rb_vector3_multiply(VALUE self, VALUE other) {
    return rb_vector3_multiply_s(CLASS_OF(self), self, other);
}

VALUE rb_vector3_divide(VALUE self, VALUE other) {
    return rb_vector3_divide_s(CLASS_OF(self), self, other);
}

VALUE rb_vector3_equal(VALUE self, VALUE other) {
    if (CLASS_OF(other) != CLASS_OF(self))
        return Qfalse;
    Vector3 *v1, *v2;
    Data_Get_Struct(self, Vector3, v1);
    Data_Get_Struct(other, Vector3, v2);
    return FLT_EQUAL(v1->x, v2->x) && FLT_EQUAL(v1->y, v2->y) && FLT_EQUAL(v1->z, v2->z) ? Qtrue : Qfalse;
}

VALUE rb_vector3_negate(VALUE self) {
    return rb_vector3_negate_s(CLASS_OF(self), self);
}

VALUE rb_vector3_to_s(VALUE self) {
    VECTOR3();
    return rb_sprintf("<%f, %f, %f>", v->x, v->y, v->z);
}

VALUE rb_vector3_to_a(VALUE self) {
    VECTOR3();
    VALUE ary = rb_ary_new_capa(3);
    rb_ary_store(ary, 0, DBL2NUM(v->x));
    rb_ary_store(ary, 1, DBL2NUM(v->y));
    rb_ary_store(ary, 2, DBL2NUM(v->z));
    return ary;
}

VALUE rb_vector3_to_h(VALUE self) {
    VECTOR3();
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, ID2SYM(rb_intern("x")), DBL2NUM(v->x));
    rb_hash_aset(hash, ID2SYM(rb_intern("y")), DBL2NUM(v->y));
    rb_hash_aset(hash, ID2SYM(rb_intern("z")), DBL2NUM(v->z));
    return hash;
}

VALUE rb_vector3_to_vec2(VALUE self) {
    VECTOR3();
    Vector2 *vec = ALLOC(Vector2);
    vec->x = v->x;
    vec->y = v->y;
    return NUMERIX_WRAP(rb_cVector2, vec);
}

VALUE rb_vector3_to_vec4(VALUE self) {
    VECTOR3();
    Vector4 *vec = ALLOC(Vector4);
    vec->x = v->x;
    vec->y = v->y;
    vec->z = v->z;
    vec->w = 0.0f;
    return NUMERIX_WRAP(rb_cVector4, vec);
}

VALUE rb_vector3_to_quaternion(VALUE self) {
    VECTOR3();
    Quaternion *q = ALLOC(Quaternion);
    memcpy(q, v, sizeof(Vector3));
    q->w = 0.0f;
    return NUMERIX_WRAP(rb_cQuaternion, q);
}

VALUE rb_vector3_to_plane(VALUE self) {
    VECTOR3();
    Plane *p = ALLOC(Plane);
    memcpy(p, v, sizeof(Vector3));
    p->distance = 0.0f;
    return NUMERIX_WRAP(rb_cPlane, p);   
}

VALUE rb_vector3_min_value(VALUE self) {
    VECTOR3();
    float m = NUMERIX_MIN(v->x, NUMERIX_MIN(v->y, v->z));
    return DBL2NUM(m);
}

VALUE rb_vector3_max_value(VALUE self) {
    VECTOR3();
    float m = NUMERIX_MAX(v->x, NUMERIX_MAX(v->y, v->z));
    return DBL2NUM(m);
}

VALUE rb_vector3_distance(VALUE self, VALUE other) {
    return rb_vector3_distance_s(CLASS_OF(self), self, other);
}

VALUE rb_vector3_distance_squared(VALUE self, VALUE other) {
    return rb_vector3_distance_squared_s(CLASS_OF(self), self, other);
}

VALUE rb_vector3_normalize(VALUE self) {
    return rb_vector3_normalize_s(CLASS_OF(self), self);
}

VALUE rb_vector3_lerp(VALUE self, VALUE other, VALUE amount) {
    return rb_vector3_lerp_s(CLASS_OF(self), self, other, amount);
}

VALUE rb_vector3_transform(VALUE self, VALUE other) {
    return rb_vector3_transform_s(CLASS_OF(self), self, other);
}

VALUE rb_vector3_abs(VALUE self) {
    return rb_vector3_abs_s(CLASS_OF(self), self);
}

VALUE rb_vector3_sqrt(VALUE self) {
    return rb_vector3_sqrt_s(CLASS_OF(self), self);
}

VALUE rb_vector3_dot(VALUE self, VALUE other) {
    return rb_vector3_dot_s(CLASS_OF(self), self, other);
}

VALUE rb_vector3_clamp(VALUE self, VALUE min, VALUE max) {
    return rb_vector3_clamp_s(CLASS_OF(self), self, min, max);
}

VALUE rb_vector3_normalize_bang(VALUE self) {
    VECTOR3();
    float inv = 1.0f / sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x = v->x * inv;
    v->y = v->y * inv;
    v->z = v->z * inv;

    return self;
}

VALUE rb_vector3_lerp_bang(VALUE self, VALUE other, VALUE amount) {
    Vector3 *v1, *v2;
    Data_Get_Struct(self, Vector3, v1);
    Data_Get_Struct(other, Vector3, v2);
    float w = NUMERIX_CLAMP(NUM2FLT(amount), 0.0f, 1.0f);

    v1->x = v1->x + (v2->x - v1->x) * w;
    v1->y = v1->y + (v2->y - v1->y) * w;
    v1->z = v1->z + (v2->z - v1->z) * w;

    return self;
}

VALUE rb_vector3_transform_bang(VALUE self, VALUE other) {
    struct RData *rdata = RDATA(self);
    VALUE result = rb_vector3_transform_s(rdata->basic.klass, self, other);
    Vector3 *src;
    Data_Get_Struct(result, Vector3, src);
    memcpy(rdata->data, src, sizeof(Vector3));
    return self;
}

VALUE rb_vector3_clamp_bang(VALUE self, VALUE min, VALUE max) {
    struct RData *rdata = RDATA(self);
    VALUE result = rb_vector3_clamp_s(rdata->basic.klass, self, min, max);
    Vector3 *src;
    Data_Get_Struct(result, Vector3, src);
    memcpy(rdata->data, src, sizeof(Vector3));
    return self;
}

VALUE rb_vector3_one_p(VALUE self) {
    VECTOR3();
    return v->x == 1.0f && v->y == 1.0f && v->z == 1.0f ? Qtrue : Qfalse;
}

VALUE rb_vector3_zero_p(VALUE self) {
    VECTOR3();
    return v->x == 0.0f && v->y == 0.0f && v->z == 0.0f ? Qtrue : Qfalse;
}

VALUE rb_vector3_cross(VALUE self, VALUE other) {
    return rb_vector3_cross_s(CLASS_OF(self), self, other);
}

VALUE rb_vector3_cross_bang(VALUE self, VALUE other) {
    Vector3 *v1, *v2;
    Data_Get_Struct(self, Vector3, v1);
    Data_Get_Struct(other, Vector3, v2);

    v1->x = v1->y * v2->z - v1->z * v2->y;
    v1->y = v1->z * v2->x - v1->x * v2->z;
    v1->z = v1->x * v2->y - v1->y * v2->x;

    return self;
}

VALUE rb_vector3_reflect(VALUE self, VALUE other) {
    return rb_vector3_reflect_s(CLASS_OF(self), self, other);
}

VALUE rb_vector3_reflect_bang(VALUE self, VALUE other) {
    Vector3 *v1, *v2;
    Data_Get_Struct(self, Vector3, v1);
    Data_Get_Struct(other, Vector3, v2);

    float dot = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
    v1->x = v1->x = (v2->x * dot * 2.0f);
    v1->y = v1->y = (v2->y * dot * 2.0f);
    v1->z = v1->z = (v2->z * dot * 2.0f);

    return self;
}

static inline VALUE rb_vector3_distance_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector3 *v1, *v2;
    Data_Get_Struct(vec1, Vector3, v1);
    Data_Get_Struct(vec2, Vector3, v2);

    float dx = v1->x - v2->x;
    float dy = v1->y - v2->y;
    float dz = v1->z - v2->z;

    return DBL2NUM(sqrtf(dx * dx + dy * dy + dz * dz));
}

static inline VALUE rb_vector3_distance_squared_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector3 *v1, *v2;
    Data_Get_Struct(vec1, Vector3, v1);
    Data_Get_Struct(vec2, Vector3, v2);

    float dx = v1->x - v2->x;
    float dy = v1->y - v2->y;
    float dz = v1->z - v2->z;

    return DBL2NUM(dx * dx + dy * dy + dz * dz);
}

static inline VALUE rb_vector3_normalize_s(VALUE klass, VALUE vector3) {
    Vector3 *v, *result;
    Data_Get_Struct(vector3, Vector3, v);
    result = ALLOC(Vector3);

    float inv = 1.0f / sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
    result->x = v->x * inv;
    result->y = v->y * inv;
    result->z = v->z * inv;

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector3_cross_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector3 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector3, v1);
    Data_Get_Struct(vec2, Vector3, v2);
    result = ALLOC(Vector3);

    result->x = v1->y * v2->z - v1->z * v2->y;
    result->y = v1->z * v2->x - v1->x * v2->z;
    result->z = v1->x * v2->y - v1->y * v2->x;

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector3_reflect_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector3 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector3, v1);
    Data_Get_Struct(vec2, Vector3, v2);
    result = ALLOC(Vector3);

    float dot = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
    result->x = v1->x = (v2->x * dot * 2.0f);
    result->y = v1->y = (v2->y * dot * 2.0f);
    result->z = v1->z = (v2->z * dot * 2.0f);

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector3_clamp_s(VALUE klass, VALUE vector, VALUE minimum, VALUE maximum) {
    Vector3 *v, *result;
    Data_Get_Struct(vector, Vector3, v);
    result = ALLOC(Vector3);
    float x = v->x, y = v->y, z = v->z;

    // This compare order is very important!!!
    // We must follow HLSL behavior in the case user specified min value is bigger than max value.
    if (NUMERIX_TYPE_P(minimum, rb_cVector3) && NUMERIX_TYPE_P(maximum, rb_cVector3))
    {
        Vector3 *min, *max;
        Data_Get_Struct(minimum, Vector3, min);
        Data_Get_Struct(maximum, Vector3, max);

        x = NUMERIX_MIN(x, max->x);
        x = NUMERIX_MAX(x, min->x);

        y = NUMERIX_MIN(y, max->y);
        y = NUMERIX_MAX(y, min->y);

        z = NUMERIX_MIN(z, max->z);
        z = NUMERIX_MAX(z, min->z);
    }
    else
    {
        float minf = NUM2FLT(minimum);
        float maxf = NUM2FLT(maximum);

        x = NUMERIX_MIN(x, maxf);
        x = NUMERIX_MAX(x, minf);

        y = NUMERIX_MIN(y, maxf);
        y = NUMERIX_MAX(y, minf);

        z = NUMERIX_MIN(z, maxf);
        z = NUMERIX_MAX(z, minf);
    }

    result->x = x;
    result->y = y;
    result->z = z;
    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector3_lerp_s(VALUE klass, VALUE vec1, VALUE vec2, VALUE amount) {
    Vector3 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector3, v1);
    Data_Get_Struct(vec2, Vector3, v2);
    result = ALLOC(Vector3);

    float w = NUMERIX_CLAMP(NUM2FLT(amount), 0.0f, 1.0f);

    result->x = v1->x + (v2->x - v1->x) * w;
    result->y = v1->y + (v2->y - v1->y) * w;
    result->z = v1->z + (v2->z - v1->z) * w;

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector3_transform_s(VALUE klass, VALUE vector, VALUE matrix) {
    Vector3 *v, *result;
    Data_Get_Struct(vector, Vector3, v);
    result = ALLOC(Vector3);
    if (NUMERIX_TYPE_P(matrix, rb_cMatrix4x4))
    {
        Matrix4x4 *m;
        Data_Get_Struct(matrix, Matrix4x4, m);

        result->x = v->x * m->m11 + v->y * m->m21 + v->z * m->m31 + m->m41;
        result->y = v->x * m->m12 + v->y * m->m22 + v->z * m->m32 + m->m42;
        result->z = v->x * m->m13 + v->y * m->m23 + v->z * m->m33 + m->m43;
    }
    else
    {
        Quaternion *q;
        Data_Get_Struct(matrix, Quaternion, q);

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

        result->x = v->x * (1.0f - yy2 - zz2) + v->y * (xy2 - wz2) + v->z * (xz2 + wy2);
        result->y = v->x * (xy2 + wz2) + v->y * (1.0f - xx2 - zz2) + v->z * (yz2 - wx2);
        result->z = v->x * (xz2 - wy2) + v->y * (yz2 + wx2) + v->z * (1.0f - xx2 - yy2);
    }

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector3_transform_normal_s(VALUE klass, VALUE vector, VALUE matrix) {
    Vector3 *v, *result;
    Data_Get_Struct(vector, Vector3, v);
    result = ALLOC(Vector3);
    Matrix4x4 *m4;
    Data_Get_Struct(matrix, Matrix4x4, m4);

    result->x = v->x * m4->m11 + v->y * m4->m21 + v->z * m4->m31;
    result->y = v->x * m4->m12 + v->y * m4->m22 + v->z * m4->m32;
    result->z = v->x * m4->m13 + v->y * m4->m23 + v->z * m4->m33;

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector3_dot_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector3 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector3, v1);
    Data_Get_Struct(vec2, Vector3, v2);

    return DBL2NUM(v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

static inline VALUE rb_vector3_min_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector3 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector3, v1);
    Data_Get_Struct(vec2, Vector3, v2);
    result = ALLOC(Vector3);

    result->x = NUMERIX_MIN(v1->x, v2->x);
    result->y = NUMERIX_MIN(v1->y, v2->y);
    result->z = NUMERIX_MIN(v1->z, v2->z);

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector3_max_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector3 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector3, v1);
    Data_Get_Struct(vec2, Vector3, v2);
    result = ALLOC(Vector3);

    result->x = NUMERIX_MAX(v1->x, v2->x);
    result->y = NUMERIX_MAX(v1->y, v2->y);
    result->z = NUMERIX_MAX(v1->z, v2->z);

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector3_abs_s(VALUE klass, VALUE vec) {
    Vector3 *v, *result;
    Data_Get_Struct(vec, Vector3, v);
    result = ALLOC(Vector3);

    result->x = fabsf(v->x);
    result->y = fabsf(v->y);
    result->z = fabsf(v->z);

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector3_sqrt_s(VALUE klass, VALUE vec) {
    Vector3 *v, *result;
    Data_Get_Struct(vec, Vector3, v);
    result = ALLOC(Vector3);

    result->x = sqrtf(v->x);
    result->y = sqrtf(v->y);
    result->z = sqrtf(v->z);

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector3_add_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector3 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector3, v1);
    Data_Get_Struct(vec2, Vector3, v2);
    result = ALLOC(Vector3);

    result->x = v1->x + v2->x;
    result->y = v1->y + v2->y;
    result->z = v1->z + v2->z;

    return NUMERIX_WRAP(klass, result); 
}

static inline VALUE rb_vector3_subtract_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector3 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector3, v1);
    Data_Get_Struct(vec2, Vector3, v2);
    result = ALLOC(Vector3);

    result->x = v1->x - v2->x;
    result->y = v1->y - v2->y;
    result->z = v1->z - v2->z;

    return NUMERIX_WRAP(klass, result); 
}

static inline VALUE rb_vector3_multiply_s(VALUE klass, VALUE vec, VALUE other) {
    Vector3 *v1, *result;
    Data_Get_Struct(vec, Vector3, v1);
    result = ALLOC(Vector3);

    if (NUMERIX_TYPE_P(other, rb_cVector3))
    {
        Vector3 *v2;
        Data_Get_Struct(other, Vector3, v2);
        result->x = v1->x * v2->x;
        result->y = v1->x * v2->y;
        result->z = v1->z * v2->z;
    }
    else
    {
        float scalar = NUM2FLT(other);
        result->x = v1->x * scalar;
        result->y = v1->y * scalar;
        result->z = v1->z * scalar;
    }
    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector3_divide_s(VALUE klass, VALUE vec, VALUE other) {
    Vector3 *v1, *result;
    Data_Get_Struct(vec, Vector3, v1);
    result = ALLOC(Vector3);

    if (NUMERIX_TYPE_P(other, rb_cVector3))
    {
        Vector3 *v2;
        Data_Get_Struct(other, Vector3, v2);
        result->x = v1->x / v2->x;
        result->y = v1->y / v2->y;
        result->z = v1->z / v2->z;
    }
    else
    {
        float scalar = 1.0f / NUM2FLT(other);
        result->x = v1->x * scalar;
        result->y = v1->y * scalar;
        result->z = v1->z * scalar;
    }
    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector3_negate_s(VALUE klass, VALUE vec) {
    Vector3 *v, *result;
    Data_Get_Struct(vec, Vector3, v);
    result = ALLOC(Vector3);

    result->x = -v->x;
    result->y = -v->y;
    result->z = -v->z;

    return NUMERIX_WRAP(klass, result);
}
