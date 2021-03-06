
#include "vector4.h"

void Init_vector4(VALUE outer) {
    rb_define_alloc_func(rb_cVector4, rb_vector4_alloc);

    // Instance Methods
    rb_define_method(rb_cVector4, "initialize", rb_vector4_initialize, -1);
    rb_define_method(rb_cVector4, "length", rb_vector4_length, 0);
    rb_define_method(rb_cVector4, "length_squared", rb_vector4_length_squared, 0);
    rb_define_method(rb_cVector4, "one?", rb_vector4_one_p, 0);
    rb_define_method(rb_cVector4, "zero?", rb_vector4_zero_p, 0);
    rb_define_method(rb_cVector4, "min_value", rb_vector4_min_value, 0);
    rb_define_method(rb_cVector4, "max_value", rb_vector4_max_value, 0);
    rb_define_method(rb_cVector4, "distance", rb_vector4_distance, 1);
    rb_define_method(rb_cVector4, "distance_squared", rb_vector4_distance_squared, 1);
    rb_define_method(rb_cVector4, "normalize", rb_vector4_normalize, 0);
    rb_define_method(rb_cVector4, "normalize!", rb_vector4_normalize_bang, 0);
    rb_define_method(rb_cVector4, "lerp", rb_vector4_lerp, 2);
    rb_define_method(rb_cVector4, "lerp!", rb_vector4_lerp_bang, 2);
    rb_define_method(rb_cVector4, "transform", rb_vector4_transform, 1);
    rb_define_method(rb_cVector4, "transform!", rb_vector4_transform_bang, 1);
    rb_define_method(rb_cVector4, "abs", rb_vector4_abs, 0);
    rb_define_method(rb_cVector4, "sqrt", rb_vector4_sqrt, 0);
    rb_define_method(rb_cVector4, "dot", rb_vector4_dot, 1);
    rb_define_method(rb_cVector4, "clamp", rb_vector4_clamp, 2);
    rb_define_method(rb_cVector4, "clamp!", rb_vector4_clamp_bang, 2);
    rb_define_method(rb_cVector4, "map", rb_vector4_map, 0);
    rb_define_method(rb_cVector4, "map!", rb_vector4_map_bang, 0);

    // Conversion
    rb_define_method(rb_cVector4, "to_s", rb_vector4_to_s, 0);
    rb_define_method(rb_cVector4, "to_a", rb_vector4_to_a, 0);
    rb_define_method(rb_cVector4, "to_h", rb_vector4_to_h, 0);
    rb_define_method(rb_cVector4, "to_quaternion", rb_vector4_to_quaternion, 0);
    rb_define_method(rb_cVector4, "to_plane", rb_vector4_to_plane, 0);
    rb_define_method(rb_cVector4, "to_vec2", rb_vector4_to_vec2, 0);
    rb_define_method(rb_cVector4, "to_vec3", rb_vector4_to_vec3, 0);

    // Operators
    rb_define_method(rb_cVector4, "+", rb_vector4_add, 1);
    rb_define_method(rb_cVector4, "-", rb_vector4_subtract, 1);
    rb_define_method(rb_cVector4, "*", rb_vector4_multiply, 1);
    rb_define_method(rb_cVector4, "/", rb_vector4_divide, 1);
    rb_define_method(rb_cVector4, "==", rb_vector4_equal, 1);
    rb_define_method(rb_cVector4, "-@", rb_vector4_negate, 0);
    rb_define_method(rb_cVector4, "**", rb_vector4_pow, 1);

    // Alias
    rb_define_alias(rb_cVector4, "magnitude", "length");
    rb_define_alias(rb_cVector4, "elements", "to_a");
    rb_define_alias(rb_cVector4, "collect", "map");
    rb_define_alias(rb_cVector4, "collect!", "map!");

    // Singleton Methods
    rb_define_singleton_method(rb_cVector4, "zero", rb_vector4_alloc, 0);
    rb_define_singleton_method(rb_cVector4, "one", rb_vector4_one, 0);
    rb_define_singleton_method(rb_cVector4, "unit_x", rb_vector4_unit_x, 0);
    rb_define_singleton_method(rb_cVector4, "unit_y", rb_vector4_unit_y, 0);
    rb_define_singleton_method(rb_cVector4, "unit_z", rb_vector4_unit_z, 0);
    rb_define_singleton_method(rb_cVector4, "unit_w", rb_vector4_unit_w, 0);
    rb_define_singleton_method(rb_cVector4, "create_norm", rb_vector4_create_norm, 4);
    rb_define_singleton_method(rb_cVector4, "clamp", rb_vector4_clamp_s, 3);
    rb_define_singleton_method(rb_cVector4, "lerp", rb_vector4_lerp_s, 3);
    rb_define_singleton_method(rb_cVector4, "transform", rb_vector4_transform_s, 2);
    rb_define_singleton_method(rb_cVector4, "min", rb_vector4_min_s, 2);
    rb_define_singleton_method(rb_cVector4, "max", rb_vector4_max_s, 2);
}

static VALUE rb_vector4_alloc(VALUE klass) {
    void *v = ALLOC(Vector4);
    memset(v, 0, sizeof(Vector4));
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector4_initialize(int argc, VALUE *argv, VALUE self) {
    VECTOR4();
    switch (argc) {
        case 0:
            break;
        case 1: {
            float value = NUM2FLT(argv[0]);
            v->x = value;
            v->y = value;
            v->z = value;
            v->w = value;
            break;
        }
        case 2: {
            if (NUMERIX_TYPE_P(argv[0], rb_cVector3)) {
                Vector3 *vec3;
                Data_Get_Struct(argv[0], Vector3, vec3);
                v->x = vec3->x;
                v->y = vec3->y;
                v->z = vec3->z;
                v->w = NUM2FLT(argv[1]);
            } else {
                Vector2 *v1, *v2;
                Data_Get_Struct(argv[0], Vector2, v1);
                Data_Get_Struct(argv[1], Vector2, v2);
                v->x = v1->x;
                v->y = v1->y;
                v->z = v2->x;
                v->w = v2->y;
            }
            break;
        }
        case 3: {
            Vector2 *vec2;
            Data_Get_Struct(argv[0], Vector2, vec2);
            v->x = vec2->x;
            v->y = vec2->y;
            v->z = NUM2FLT(argv[1]);
            v->w = NUM2FLT(argv[2]);
            break;
        }
        case 4: {
            v->x = NUM2FLT(argv[0]);
            v->y = NUM2FLT(argv[1]);
            v->z = NUM2FLT(argv[2]);
            v->w = NUM2FLT(argv[3]);
            break;
        }
        default:
            rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 0, 1, 2, 3, 4)", argc);
            break;
    }
    return Qnil;
}

VALUE rb_vector4_one(VALUE klass) {
    Vector4 *v = ALLOC(Vector4);
    v->x = 1.0f;
    v->y = 1.0f;
    v->z = 1.0f;
    v->w = 1.0f;
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector4_unit_x(VALUE klass) {
    Vector4 *v = ALLOC(Vector4);
    v->x = 1.0f;
    v->y = 0.0f;
    v->z = 0.0f;
    v->w = 0.0f;
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector4_unit_y(VALUE klass) {
    Vector4 *v = ALLOC(Vector4);
    v->x = 0.0f;
    v->y = 1.0f;
    v->z = 0.0f;
    v->w = 0.0f;
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector4_unit_z(VALUE klass) {
    Vector4 *v = ALLOC(Vector4);
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 1.0f;
    v->w = 0.0f;
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector4_unit_w(VALUE klass) {
    Vector4 *v = ALLOC(Vector4);
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 0.0f;
    v->w = 1.0f;
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector4_length(VALUE self) {
    VECTOR4();
    return DBL2NUM(sqrtf(v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w));
}

VALUE rb_vector4_length_squared(VALUE self) {
    VECTOR4();
    return DBL2NUM(v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w);
}

VALUE rb_vector4_one_p(VALUE self) {
    VECTOR4();
    return v->x == 1.0f && v->y == 1.0f && v->z == 1.0f && v->w == 1.0f ? Qtrue : Qfalse;
}

VALUE rb_vector4_zero_p(VALUE self) {
    VECTOR4();
    return v->x == 0.0f && v->y == 0.0f && v->z == 0.0f && v->w == 0.0f ? Qtrue : Qfalse;
}

VALUE rb_vector4_add(VALUE self, VALUE other) {
    VECTOR4();
    Vector4 *result = ALLOC(Vector4);
    Vector4 *v2;
    Data_Get_Struct(other, Vector4, v2);

    result->x = v->x + v2->x;
    result->y = v->y + v2->y;
    result->z = v->z + v2->z;
    result->w = v->w + v2->w;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector4_subtract(VALUE self, VALUE other) {
    VECTOR4();
    Vector4 *result = ALLOC(Vector4);
    Vector4 *v2;
    Data_Get_Struct(other, Vector4, v2);

    result->x = v->x - v2->x;
    result->y = v->y - v2->y;
    result->z = v->z - v2->z;
    result->w = v->w - v2->w;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector4_multiply(VALUE self, VALUE other) {
    VECTOR4();
    Vector4 *result = ALLOC(Vector4);

    if (NUMERIX_TYPE_P(other, rb_cVector4)) {
        Vector4 *v2;
        Data_Get_Struct(other, Vector4, v2);
        result->x = v->x * v2->x;
        result->y = v->x * v2->y;
        result->z = v->z * v2->z;
        result->w = v->w * v2->w;
    } else {
        float scalar = NUM2FLT(other);
        result->x = v->x * scalar;
        result->y = v->y * scalar;
        result->z = v->z * scalar;
        result->w = v->w * scalar;
    }

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector4_divide(VALUE self, VALUE other) {
    VECTOR4();
    Vector4 *result = ALLOC(Vector4);

    if (NUMERIX_TYPE_P(other, rb_cVector4)) {
        Vector4 *v2;
        Data_Get_Struct(other, Vector4, v2);
        result->x = v->x / v2->x;
        result->y = v->y / v2->y;
        result->z = v->z / v2->z;
        result->w = v->w / v2->w;
    } else {
        float scalar = 1.0f / NUM2FLT(other);
        result->x = v->x * scalar;
        result->y = v->y * scalar;
        result->z = v->z * scalar;
        result->w = v->w * scalar;
    }

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector4_equal(VALUE self, VALUE other) {
    if (CLASS_OF(other) != CLASS_OF(self))
        return Qfalse;
    Vector4 *v1, *v2;
    Data_Get_Struct(self, Vector4, v1);
    Data_Get_Struct(other, Vector4, v2);
    return FLT_EQUAL(v1->x, v2->x) && FLT_EQUAL(v1->y, v2->y) && FLT_EQUAL(v1->z, v2->z) && FLT_EQUAL(v1->w, v2->w) ? Qtrue : Qfalse;
}

VALUE rb_vector4_negate(VALUE self) {
    VECTOR4();
    Vector4 *result = ALLOC(Vector4);

    result->x = -v->x;
    result->y = -v->y;
    result->z = -v->z;
    result->w = -v->w;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector4_map(VALUE self) {
    VECTOR4();
    Vector4 *result = ALLOC(Vector4);

    result->x = NUM2FLT(rb_yield(DBL2NUM(v->x)));
    result->y = NUM2FLT(rb_yield(DBL2NUM(v->y)));
    result->z = NUM2FLT(rb_yield(DBL2NUM(v->z)));
    result->w = NUM2FLT(rb_yield(DBL2NUM(v->w)));

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector4_map_bang(VALUE self) {
    VECTOR4();

    v->x = NUM2FLT(rb_yield(DBL2NUM(v->x)));
    v->y = NUM2FLT(rb_yield(DBL2NUM(v->y)));
    v->z = NUM2FLT(rb_yield(DBL2NUM(v->z)));
    v->w = NUM2FLT(rb_yield(DBL2NUM(v->w)));

    return self;
}

VALUE rb_vector4_to_s(VALUE self) {
    VECTOR4();
    return rb_sprintf("<%f, %f, %f, %f>", v->x, v->y, v->z, v->w);
}

VALUE rb_vector4_to_a(VALUE self) {
    VECTOR4();
    VALUE ary = rb_ary_new_capa(4);
    rb_ary_store(ary, 0, DBL2NUM(v->x));
    rb_ary_store(ary, 1, DBL2NUM(v->y));
    rb_ary_store(ary, 2, DBL2NUM(v->z));
    rb_ary_store(ary, 3, DBL2NUM(v->w));
    return ary;
}

VALUE rb_vector4_to_h(VALUE self) {
    VECTOR4();
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, ID2SYM(rb_intern("x")), DBL2NUM(v->x));
    rb_hash_aset(hash, ID2SYM(rb_intern("y")), DBL2NUM(v->y));
    rb_hash_aset(hash, ID2SYM(rb_intern("z")), DBL2NUM(v->z));
    rb_hash_aset(hash, ID2SYM(rb_intern("w")), DBL2NUM(v->w));
    return hash;
}

VALUE rb_vector4_to_vec2(VALUE self) {
    VECTOR4();
    Vector2 *vec = ALLOC(Vector2);
    vec->x = v->x;
    vec->y = v->y;
    return NUMERIX_WRAP(rb_cVector2, vec);
}

VALUE rb_vector4_to_vec3(VALUE self) {
    VECTOR4();
    Vector3 *vec = ALLOC(Vector3);
    vec->x = v->x;
    vec->y = v->y;
    vec->z = v->z;
    return NUMERIX_WRAP(rb_cVector3, vec);
}

VALUE rb_vector4_to_quaternion(VALUE self) {
    VECTOR4();
    Quaternion *q = ALLOC(Quaternion);
    memcpy(q, v, sizeof(Vector4));
    return NUMERIX_WRAP(rb_cQuaternion, q);
}

VALUE rb_vector4_to_plane(VALUE self) {
    VECTOR4();
    Plane *p = ALLOC(Plane);
    memcpy(p, v, sizeof(Vector4));
    return NUMERIX_WRAP(rb_cPlane, p);
}

VALUE rb_vector4_min_value(VALUE self) {
    VECTOR4();
    float m = NUMERIX_MIN(v->x, NUMERIX_MIN(v->y, NUMERIX_MIN(v->z, v->w)));
    return DBL2NUM(m);
}

VALUE rb_vector4_max_value(VALUE self) {
    VECTOR4();
    float m = NUMERIX_MAX(v->x, NUMERIX_MAX(v->y, NUMERIX_MAX(v->z, v->w)));
    return DBL2NUM(m);
}

VALUE rb_vector4_distance(VALUE self, VALUE other) {
    Vector4 *v1, *v2;
    Data_Get_Struct(self, Vector4, v1);
    Data_Get_Struct(other, Vector4, v2);

    float dx = v1->x - v2->x;
    float dy = v1->y - v2->y;
    float dz = v1->z - v2->z;
    float dw = v1->w - v2->w;

    return DBL2NUM(sqrtf(dx * dx + dy * dy + dz * dz + dw * dw));
}

VALUE rb_vector4_distance_squared(VALUE self, VALUE other) {
    Vector4 *v1, *v2;
    Data_Get_Struct(self, Vector4, v1);
    Data_Get_Struct(other, Vector4, v2);

    float dx = v1->x - v2->x;
    float dy = v1->y - v2->y;
    float dz = v1->z - v2->z;
    float dw = v1->w - v2->w;

    return DBL2NUM(dx * dx + dy * dy + dz * dz + dw * dw);
}

VALUE rb_vector4_normalize(VALUE self) {
    VECTOR4();
    Vector4 *result = ALLOC(Vector4);

    float inv = 1.0f / sqrtf(v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w);
    result->x = v->x * inv;
    result->y = v->y * inv;
    result->z = v->z * inv;
    result->w = v->w * inv;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector4_lerp(VALUE self, VALUE other, VALUE amount) {
    return rb_vector4_lerp_s(CLASS_OF(self), self, other, amount);
}

VALUE rb_vector4_transform(VALUE self, VALUE other) {
    return rb_vector4_transform_s(CLASS_OF(self), self, other);
}

VALUE rb_vector4_abs(VALUE self) {
    VECTOR4();
    Vector4 *result = ALLOC(Vector4);

    result->x = fabsf(v->x);
    result->y = fabsf(v->y);
    result->z = fabsf(v->z);
    result->w = fabsf(v->w);

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector4_sqrt(VALUE self) {
    VECTOR4();
    Vector4 *result = ALLOC(Vector4);

    result->x = sqrtf(v->x);
    result->y = sqrtf(v->y);
    result->z = sqrtf(v->z);
    result->w = sqrtf(v->w);

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector4_pow(VALUE self, VALUE exponent) {
    VECTOR4();
    Vector4 *result = ALLOC(Vector4);
    float e = fabsf(NUM2FLT(exponent));

    result->x = powf(fabsf(v->x), e);
    result->y = powf(fabsf(v->y), e);
    result->z = powf(fabsf(v->z), e);
    result->w = powf(fabsf(v->w), e);

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector4_dot(VALUE self, VALUE other) {
    Vector4 *v1, *v2;
    Data_Get_Struct(self, Vector4, v1);
    Data_Get_Struct(other, Vector4, v2);

    return DBL2NUM(v1->x * v2->x + v1->y * v2->y + v1->z * v2->z + v1->w * v2->w);
}

VALUE rb_vector4_clamp(VALUE self, VALUE min, VALUE max) {
    return rb_vector4_clamp_s(CLASS_OF(self), self, min, max);
}

VALUE rb_vector4_normalize_bang(VALUE self) {
    VECTOR4();
    float inv = 1.0f / sqrtf(v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w);
    v->x = v->x * inv;
    v->y = v->y * inv;
    v->z = v->z * inv;
    v->w = v->w * inv;

    return self;
}

VALUE rb_vector4_lerp_bang(VALUE self, VALUE other, VALUE amount) {
    Vector4 *v1, *v2;
    Data_Get_Struct(self, Vector4, v1);
    Data_Get_Struct(other, Vector4, v2);
    float w = NUMERIX_CLAMP(NUM2FLT(amount), 0.0f, 1.0f);

    v1->x = v1->x + (v2->x - v1->x) * w;
    v1->y = v1->y + (v2->y - v1->y) * w;
    v1->z = v1->z + (v2->z - v1->z) * w;
    v1->w = v1->w + (v2->w - v1->w) * w;

    return self;
}

VALUE rb_vector4_transform_bang(VALUE self, VALUE other) {
    struct RData *rdata = RDATA(self);
    VALUE result = rb_vector4_transform_s(rdata->basic.klass, self, other);
    Vector4 *src;
    Data_Get_Struct(result, Vector4, src);
    memcpy(rdata->data, src, sizeof(Vector4));
    return self;
}

VALUE rb_vector4_clamp_bang(VALUE self, VALUE min, VALUE max) {
    struct RData *rdata = RDATA(self);
    VALUE result = rb_vector4_clamp_s(rdata->basic.klass, self, min, max);
    Vector4 *src;
    Data_Get_Struct(result, Vector4, src);
    memcpy(rdata->data, src, sizeof(Vector4));
    return self;
}

static inline VALUE rb_vector4_clamp_s(VALUE klass, VALUE vector, VALUE minimum, VALUE maximum) {
    Vector4 *v, *result;
    Data_Get_Struct(vector, Vector4, v);
    result = ALLOC(Vector4);
    float x = v->x, y = v->y, z = v->z, w = v->w;

    // This compare order is very important!!!
    // We must follow HLSL behavior in the case user specified min value is bigger than max value.
    if (NUMERIX_TYPE_P(minimum, rb_cVector4) && NUMERIX_TYPE_P(maximum, rb_cVector4)) {
        Vector4 *min, *max;
        Data_Get_Struct(minimum, Vector4, min);
        Data_Get_Struct(maximum, Vector4, max);

        x = NUMERIX_MIN(x, max->x);
        x = NUMERIX_MAX(x, min->x);

        y = NUMERIX_MIN(y, max->y);
        y = NUMERIX_MAX(y, min->y);

        z = NUMERIX_MIN(z, max->z);
        z = NUMERIX_MAX(z, min->z);

        w = NUMERIX_MIN(w, max->w);
        w = NUMERIX_MAX(w, min->w);
    } else {
        float minf = NUM2FLT(minimum);
        float maxf = NUM2FLT(maximum);

        x = NUMERIX_MIN(x, maxf);
        x = NUMERIX_MAX(x, minf);

        y = NUMERIX_MIN(y, maxf);
        y = NUMERIX_MAX(y, minf);

        z = NUMERIX_MIN(z, maxf);
        z = NUMERIX_MAX(z, minf);

        w = NUMERIX_MIN(w, maxf);
        w = NUMERIX_MAX(w, minf);
    }

    result->x = x;
    result->y = y;
    result->z = z;
    result->w = w;
    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector4_lerp_s(VALUE klass, VALUE vec1, VALUE vec2, VALUE amount) {
    Vector4 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector4, v1);
    Data_Get_Struct(vec2, Vector4, v2);
    result = ALLOC(Vector4);

    float w = NUMERIX_CLAMP(NUM2FLT(amount), 0.0f, 1.0f);

    result->x = v1->x + (v2->x - v1->x) * w;
    result->y = v1->y + (v2->y - v1->y) * w;
    result->z = v1->z + (v2->z - v1->z) * w;
    result->w = v1->w + (v2->w - v1->w) * w;

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector4_transform_s(VALUE klass, VALUE vector, VALUE matrix) {
    Vector4 *v, *result;
    result = ALLOC(Vector4);

    if (NUMERIX_TYPE_P(matrix, rb_cMatrix4x4)) {
        Matrix4x4 *m;
        Data_Get_Struct(matrix, Matrix4x4, m);
        if (NUMERIX_TYPE_P(vector, rb_cVector2)) {
            result->x = v->x * m->m11 + v->y * m->m21 + m->m41;
            result->y = v->x * m->m12 + v->y * m->m22 + m->m42;
            result->z = v->x * m->m13 + v->y * m->m23 + m->m43;
            result->w = v->x * m->m14 + v->y * m->m24 + m->m44;
        } else if (NUMERIX_TYPE_P(vector, rb_cVector3)) {
            result->x = v->x * m->m11 + v->y * m->m21 + v->z * m->m31 + m->m41;
            result->y = v->x * m->m12 + v->y * m->m22 + v->z * m->m32 + m->m42;
            result->z = v->x * m->m13 + v->y * m->m23 + v->z * m->m33 + m->m43;
            result->w = v->x * m->m14 + v->y * m->m24 + v->z * m->m34 + m->m44;
        } else if (NUMERIX_TYPE_P(vector, rb_cVector4)) {
            result->x = v->x * m->m11 + v->y * m->m21 + v->z * m->m31 + v->w * m->m41;
            result->y = v->x * m->m12 + v->y * m->m22 + v->z * m->m32 + v->w * m->m42;
            result->z = v->x * m->m13 + v->y * m->m23 + v->z * m->m33 + v->w * m->m43;
            result->w = v->x * m->m14 + v->y * m->m24 + v->z * m->m34 + v->w * m->m44;
        } else
            rb_raise(rb_eTypeError, "%s is not a valid Vector type", CLASS_NAME(vector));
    } else if (NUMERIX_TYPE_P(matrix, rb_cQuaternion)) {
        Quaternion *q;
        Data_Get_Struct(matrix, Quaternion, q);
        float x2, y2, z2, wx2, wy2, wz2, xx2, xy2, xz2, yy2, yz2, zz2;
        if (NUMERIX_TYPE_P(vector, rb_cVector2)) {
            Vector2 *v2;
            Data_Get_Struct(vector, Vector2, v2);
            x2 = q->x + q->x;
            y2 = q->y + q->y;
            z2 = q->z + q->z;

            wx2 = q->w * x2;
            wy2 = q->w * y2;
            wz2 = q->w * z2;
            xx2 = q->x * x2;
            xy2 = q->x * y2;
            xz2 = q->x * z2;
            yy2 = q->y * y2;
            yz2 = q->y * z2;
            zz2 = q->z * z2;

            result->x = v2->x * (1.0f - yy2 - zz2) + v2->y * (xy2 - wz2);
            result->y = v2->x * (xy2 + wz2) + v2->y * (1.0f - xx2 - zz2);
            result->z = v2->x * (xz2 - wy2) + v2->y * (yz2 + wx2);
            result->w = 1.0f;
        } else if (NUMERIX_TYPE_P(vector, rb_cVector3)) {
            Vector3 *v3;
            Data_Get_Struct(vector, Vector3, v3);
            x2 = q->x + q->x;
            y2 = q->y + q->y;
            z2 = q->z + q->z;

            wx2 = q->w * x2;
            wy2 = q->w * y2;
            wz2 = q->w * z2;
            xx2 = q->x * x2;
            xy2 = q->x * y2;
            xz2 = q->x * z2;
            yy2 = q->y * y2;
            yz2 = q->y * z2;
            zz2 = q->z * z2;

            result->x = v3->x * (1.0f - yy2 - zz2) + v3->y * (xy2 - wz2) + v3->z * (xz2 + wy2);
            result->y = v3->x * (xy2 + wz2) + v3->y * (1.0f - xx2 - zz2) + v3->z * (yz2 - wx2);
            result->z = v3->x * (xz2 - wy2) + v3->y * (yz2 + wx2) + v3->z * (1.0f - xx2 - yy2);
            result->w = 1.0f;
        } else if (NUMERIX_TYPE_P(vector, rb_cVector4)) {
            Vector4 *v4;
            Data_Get_Struct(vector, Vector4, v4);
            x2 = q->x + q->x;
            y2 = q->y + q->y;
            z2 = q->z + q->z;

            wx2 = q->w * x2;
            wy2 = q->w * y2;
            wz2 = q->w * z2;
            xx2 = q->x * x2;
            xy2 = q->x * y2;
            xz2 = q->x * z2;
            yy2 = q->y * y2;
            yz2 = q->y * z2;
            zz2 = q->z * z2;

            result->x = v4->x * (1.0f - yy2 - zz2) + v4->y * (xy2 - wz2) + v4->z * (xz2 + wy2);
            result->y = v4->x * (xy2 + wz2) + v4->y * (1.0f - xx2 - zz2) + v4->z * (yz2 - wx2);
            result->z = v4->x * (xz2 - wy2) + v4->y * (yz2 + wx2) + v4->z * (1.0f - xx2 - yy2);
            result->w = v4->w;
        } else
            rb_raise(rb_eTypeError, "%s is not a valid Vector type", CLASS_NAME(vector));

    } else {
        rb_raise(rb_eTypeError, "%s is not a valid Matrix4x4 or Quaternion", CLASS_NAME(matrix));
        return Qnil;
    }

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector4_min_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector4 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector4, v1);
    Data_Get_Struct(vec2, Vector4, v2);
    result = ALLOC(Vector4);

    result->x = NUMERIX_MIN(v1->x, v2->x);
    result->y = NUMERIX_MIN(v1->y, v2->y);
    result->z = NUMERIX_MIN(v1->z, v2->z);
    result->w = NUMERIX_MIN(v1->w, v2->w);

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector4_max_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector4 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector4, v1);
    Data_Get_Struct(vec2, Vector4, v2);
    result = ALLOC(Vector4);

    result->x = NUMERIX_MAX(v1->x, v2->x);
    result->y = NUMERIX_MAX(v1->y, v2->y);
    result->z = NUMERIX_MAX(v1->z, v2->z);
    result->w = NUMERIX_MAX(v1->w, v2->w);

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_vector4_create_norm(VALUE klass, VALUE x, VALUE y, VALUE z, VALUE w) {
    Vector4 *v = ALLOC(Vector4);
    float vx = NUM2FLT(x);
    float vy = NUM2FLT(y);
    float vz = NUM2FLT(z);
    float vw = NUM2FLT(w);

    float inv = 1.0f / sqrtf(vx * vx + vy * vy + vz * vz + vw * vw);
    v->x = vx * inv;
    v->y = vy * inv;
    v->z = vz * inv;
    v->w = vw * inv;

    return NUMERIX_WRAP(klass, v);
}