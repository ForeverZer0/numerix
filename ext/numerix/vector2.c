
#include "vector2.h"


void Init_vector2(VALUE outer) {
    
    rb_define_alloc_func(rb_cVector2, rb_vector2_alloc);

    // Instance Methods
    rb_define_method(rb_cVector2, "initialize", rb_vector2_initialize, -1);
    rb_define_method(rb_cVector2, "length", rb_vector2_length, 0);
    rb_define_method(rb_cVector2, "length_squared", rb_vector2_length_squared, 0);
    rb_define_method(rb_cVector2, "one?", rb_vector2_one_p, 0);
    rb_define_method(rb_cVector2, "zero?", rb_vector2_zero_p, 0);
    rb_define_method(rb_cVector2, "min_value", rb_vector2_min_value, 0);
    rb_define_method(rb_cVector2, "max_value", rb_vector2_max_value, 0);
    rb_define_method(rb_cVector2, "distance", rb_vector2_distance, 1);
    rb_define_method(rb_cVector2, "distance_squared", rb_vector2_distance_squared, 1);
    rb_define_method(rb_cVector2, "normalize", rb_vector2_normalize, 0);
    rb_define_method(rb_cVector2, "normalize!", rb_vector2_normalize_bang, 0);
    rb_define_method(rb_cVector2, "lerp", rb_vector2_lerp, 2);
    rb_define_method(rb_cVector2, "lerp!", rb_vector2_lerp_bang, 2);
    rb_define_method(rb_cVector2, "transform", rb_vector2_transform, 1);
    rb_define_method(rb_cVector2, "transform!", rb_vector2_transform_bang, 1);
    rb_define_method(rb_cVector2, "abs", rb_vector2_abs, 0);
    rb_define_method(rb_cVector2, "sqrt", rb_vector2_sqrt, 0);
    rb_define_method(rb_cVector2, "dot", rb_vector2_dot, 1);
    rb_define_method(rb_cVector2, "clamp", rb_vector2_clamp, 2);
    rb_define_method(rb_cVector2, "clamp!", rb_vector2_clamp_bang, 2);
    rb_define_method(rb_cVector2, "reflect", rb_vector2_reflect, 2);
    rb_define_method(rb_cVector2, "reflect!", rb_vector2_reflect_bang, 2);

    // Conversion
    rb_define_method(rb_cVector2, "to_s", rb_vector2_to_s, 0);
    rb_define_method(rb_cVector2, "to_a", rb_vector2_to_a, 0);
    rb_define_method(rb_cVector2, "to_h", rb_vector2_to_h, 0);
    rb_define_method(rb_cVector2, "to_vec3", rb_vector2_to_vec3, 0);
    rb_define_method(rb_cVector2, "to_vec4", rb_vector2_to_vec4, 0);

    // Operators
    rb_define_method(rb_cVector2, "+", rb_vector2_add, 1);
    rb_define_method(rb_cVector2, "-", rb_vector2_subtract, 1);
    rb_define_method(rb_cVector2, "*", rb_vector2_multiply, 1);
    rb_define_method(rb_cVector2, "/", rb_vector2_divide, 1);
    rb_define_method(rb_cVector2, "==", rb_vector2_equal, 1);
    rb_define_method(rb_cVector2, "-@", rb_vector2_negate, 0);

    // Alias
    rb_define_alias(rb_cVector2, "magnitude", "length");
    rb_define_alias(rb_cVector2, "elements", "to_a");

    // Singleton Methods
    rb_define_singleton_method(rb_cVector2, "zero", rb_vector2_alloc, 0);
    rb_define_singleton_method(rb_cVector2, "one", rb_vector2_one, 0);
    rb_define_singleton_method(rb_cVector2, "unit_x", rb_vector2_unit_x, 0);
    rb_define_singleton_method(rb_cVector2, "unit_y", rb_vector2_unit_y, 0);
    rb_define_singleton_method(rb_cVector2, "create_norm", rb_vector2_create_norm, 2);
    rb_define_singleton_method(rb_cVector2, "clamp", rb_vector2_clamp_s, 3);
    rb_define_singleton_method(rb_cVector2, "lerp", rb_vector2_lerp_s, 3);
    rb_define_singleton_method(rb_cVector2, "transform", rb_vector2_transform_s, 2);
    rb_define_singleton_method(rb_cVector2, "transform_normal", rb_vector2_transform_normal_s, 2);
    rb_define_singleton_method(rb_cVector2, "min", rb_vector2_min_s, 2);
    rb_define_singleton_method(rb_cVector2, "max", rb_vector2_max_s, 2);
}

static VALUE rb_vector2_alloc(VALUE klass) {
    void *v = ALLOC(Vector2);
    memset(v, 0, sizeof(Vector2));
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector2_initialize(int argc, VALUE *argv, VALUE self) {
    VECTOR2();
    switch (argc)
    {
        case 0:
            break;
        case 1:
        {
            float value = NUM2FLT(argv[0]);
            v->x = value;
            v->y = value;
            break;
        }
        case 2:
        {
            v->x = NUM2FLT(argv[0]);
            v->y = NUM2FLT(argv[1]);
            break;
        }
        default:
            rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 0, 1, 2)", argc);
            break;

    }
    return Qnil;
}

VALUE rb_vector2_one(VALUE klass) {
    Vector2 *v = ALLOC(Vector2);
    v->x = 1.0f;
    v->y = 1.0f;
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector2_unit_x(VALUE klass) {
    Vector2 *v = ALLOC(Vector2);
    v->x = 1.0f;
    v->y = 0.0f;
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector2_unit_y(VALUE klass) {
    Vector2 *v = ALLOC(Vector2);
    v->x = 0.0f;
    v->y = 1.0f;
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_vector2_length(VALUE self) {
    VECTOR2();
    return DBL2NUM(sqrtf(v->x * v->x + v->y * v->y));
}

VALUE rb_vector2_length_squared(VALUE self) {
    VECTOR2();
    return DBL2NUM(v->x * v->x + v->y * v->y); 
}

VALUE rb_vector2_add(VALUE self, VALUE other) {
    Vector2 *v1, *v2, *result;
    Data_Get_Struct(self, Vector2, v1);
    Data_Get_Struct(other, Vector2, v2);
    result = ALLOC(Vector2);

    result->x = v1->x + v2->x;
    result->y = v1->y + v2->y;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector2_subtract(VALUE self, VALUE other) {
    Vector2 *v1, *v2, *result;
    Data_Get_Struct(self, Vector2, v1);
    Data_Get_Struct(other, Vector2, v2);
    result = ALLOC(Vector2);

    result->x = v1->x - v2->x;
    result->y = v1->y - v2->y;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector2_multiply(VALUE self, VALUE other) {
    Vector2 *v1, *result;
    Data_Get_Struct(self, Vector2, v1);
    result = ALLOC(Vector2);

    if (NUMERIX_TYPE_P(other, rb_cVector2))
    {
        Vector2 *v2;
        Data_Get_Struct(other, Vector2, v2);
        result->x = v1->x * v2->x;
        result->y = v1->y * v2->y;
    }
    else
    {
        float scalar = NUM2FLT(other);
        result->x = v1->x * scalar;
        result->y = v1->y * scalar;
    }
    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector2_divide(VALUE self, VALUE other) {
    Vector2 *v1, *result;
    Data_Get_Struct(self, Vector2, v1);
    result = ALLOC(Vector2);

    if (NUMERIX_TYPE_P(other, rb_cVector2))
    {
        Vector2 *v2;
        Data_Get_Struct(other, Vector2, v2);
        result->x = v1->x / v2->x;
        result->y = v1->y / v2->y;
    }
    else
    {
        float scalar = 1.0f / NUM2FLT(other);
        result->x = v1->x * scalar;
        result->y = v1->y * scalar;
    }
    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector2_equal(VALUE self, VALUE other) {
    if (CLASS_OF(other) != CLASS_OF(self))
        return Qfalse;
    Vector2 *v1, *v2;
    Data_Get_Struct(self, Vector2, v1);
    Data_Get_Struct(other, Vector2, v2);
    return FLT_EQUAL(v1->x, v2->x) && FLT_EQUAL(v1->y, v2->y) ? Qtrue : Qfalse;
}

VALUE rb_vector2_negate(VALUE self) {
    VECTOR2();
    Vector2 *result = ALLOC(Vector2);

    result->x = -v->x;
    result->y = -v->y;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector2_min_value(VALUE self) {
    VECTOR2();
    float m = NUMERIX_MIN(v->x, v->y);
    return DBL2NUM(m);
}

VALUE rb_vector2_max_value(VALUE self) {
    VECTOR2();
    float m = NUMERIX_MAX(v->x, v->y);
    return DBL2NUM(m);
}

VALUE rb_vector2_distance(VALUE self, VALUE other) {
    Vector2 *v1, *v2;
    Data_Get_Struct(self, Vector2, v1);
    Data_Get_Struct(other, Vector2, v2);

    float dx = v1->x - v2->x;
    float dy = v1->y - v2->y;

    return DBL2NUM(sqrtf(dx * dx + dy * dy));
}

VALUE rb_vector2_distance_squared(VALUE self, VALUE other) {
    Vector2 *v1, *v2;
    Data_Get_Struct(self, Vector2, v1);
    Data_Get_Struct(other, Vector2, v2);

    float dx = v1->x - v2->x;
    float dy = v1->y - v2->y;

    return DBL2NUM(dx * dx + dy * dy);
}

VALUE rb_vector2_normalize(VALUE self) {
    VECTOR2();
    Vector2 *result =  ALLOC(Vector2);

    float inv = 1.0f / sqrtf(v->x * v->x + v->y * v->y);
    result->x = v->x * inv;
    result->y = v->y * inv;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector2_lerp(VALUE self, VALUE other, VALUE amount) {
    return rb_vector2_lerp_s(CLASS_OF(self), self, other, amount);
}

VALUE rb_vector2_transform(VALUE self, VALUE other) {
    return rb_vector2_transform_s(CLASS_OF(self), self, other);
}

VALUE rb_vector2_abs(VALUE self) {
    VECTOR2();
    Vector2 *result = ALLOC(Vector2);

    result->x = fabsf(v->x);
    result->y = fabsf(v->y);

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector2_sqrt(VALUE self) {
    VECTOR2();
    Vector2 *result = ALLOC(Vector2);

    result->x = sqrtf(v->x);
    result->y = sqrtf(v->y);

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector2_dot(VALUE self, VALUE other) {
    Vector2 *v1, *v2;
    Data_Get_Struct(self, Vector2, v1);
    Data_Get_Struct(other, Vector2, v2);

    return DBL2NUM(v1->x * v2->x + v1->y * v2->y);
}

VALUE rb_vector2_clamp(VALUE self, VALUE min, VALUE max) {
    return rb_vector2_clamp_s(CLASS_OF(self), self, min, max);
}

VALUE rb_vector2_to_s(VALUE self) {
    VECTOR2();
    return rb_sprintf("<%f, %f>", v->x, v->y);
}

VALUE rb_vector2_to_a(VALUE self) {
    VECTOR2();
    VALUE ary = rb_ary_new_capa(2);
    rb_ary_store(ary, 0, DBL2NUM(v->x));
    rb_ary_store(ary, 1, DBL2NUM(v->y));
    return ary;
}

VALUE rb_vector2_to_h(VALUE self) {
    VECTOR2();
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, ID2SYM(rb_intern("x")), DBL2NUM(v->x));
    rb_hash_aset(hash, ID2SYM(rb_intern("y")), DBL2NUM(v->y));
    return hash;
}

VALUE rb_vector2_to_vec3(VALUE self) {
    VECTOR2();
    Vector3 *vec = ALLOC(Vector3);
    vec->x = v->x;
    vec->y = v->y;
    vec->z = 0.0f;
    return NUMERIX_WRAP(rb_cVector3, vec);
}

VALUE rb_vector2_to_vec4(VALUE self) {
    VECTOR2();
    Vector4 *vec = ALLOC(Vector4);
    vec->x = v->x;
    vec->y = v->y;
    vec->z = 0.0f;
    vec->w = 0.0f;
    return NUMERIX_WRAP(rb_cVector4, vec);
}

VALUE rb_vector2_normalize_bang(VALUE self) {
    VECTOR2();
    float inv = 1.0f / sqrtf(v->x * v->x + v->y * v->y);
    v->x = v->x * inv;
    v->y = v->y * inv;

    return self;
}

VALUE rb_vector2_lerp_bang(VALUE self, VALUE other, VALUE amount) {
    Vector2 *v1, *v2;
    Data_Get_Struct(self, Vector2, v1);
    Data_Get_Struct(other, Vector2, v2);
    float w = NUMERIX_CLAMP(NUM2FLT(amount), 0.0f, 1.0f);

    v1->x = v1->x + (v2->x - v1->x) * w;
    v1->y = v1->y + (v2->y - v1->y) * w;

    return self;
}

VALUE rb_vector2_transform_bang(VALUE self, VALUE other) {
    struct RData *rdata = RDATA(self);
    VALUE result = rb_vector2_transform_s(rdata->basic.klass, self, other);
    Vector2 *src;
    Data_Get_Struct(result, Vector2, src);
    memcpy(rdata->data, src, sizeof(Vector2));
    return self;
}

VALUE rb_vector2_clamp_bang(VALUE self, VALUE min, VALUE max) {
    struct RData *rdata = RDATA(self);
    VALUE result = rb_vector2_clamp_s(rdata->basic.klass, self, min, max);
    Vector2 *src;
    Data_Get_Struct(result, Vector2, src);
    memcpy(rdata->data, src, sizeof(Vector2));
    return self;
}

VALUE rb_vector2_one_p(VALUE self) {
    VECTOR2();
    return v->x == 1.0f && v->y == 1.0f ? Qtrue : Qfalse;
}

VALUE rb_vector2_zero_p(VALUE self) {
    VECTOR2();
    return v->x == 0.0f && v->y == 0.0f ? Qtrue : Qfalse;
}

VALUE rb_vector2_reflect(VALUE self, VALUE other) {
    Vector2 *v1, *v2, *result;
    Data_Get_Struct(self, Vector2, v1);
    Data_Get_Struct(other, Vector2, v2);
    result = ALLOC(Vector2);

    float dot = v1->x * v2->x + v1->y * v2->y;
    result->x = v1->x - 2.0f * dot * v2->x;
    result->y = v1->y - 2.0f * dot * v2->y;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_vector2_reflect_bang(VALUE self, VALUE other) {
    Vector2 *v1, *v2;
    Data_Get_Struct(self, Vector2, v1);
    Data_Get_Struct(other, Vector2, v2);

    float dot = v1->x * v2->x + v1->y * v2->y;
    v1->x = v1->x - 2.0f * dot * v2->x;
    v1->y = v1->y - 2.0f * dot * v2->y;

    return self;
}

static inline VALUE rb_vector2_clamp_s(VALUE klass, VALUE vector, VALUE minimum, VALUE maximum) {
    Vector2 *v, *result;
    Data_Get_Struct(vector, Vector2, v);
    result = ALLOC(Vector2);
    float x = v->x, y = v->y;

    // This compare order is very important!!!
    // We must follow HLSL behavior in the case user specified min value is bigger than max value.
    if (NUMERIX_TYPE_P(minimum, rb_cVector2) && NUMERIX_TYPE_P(maximum, rb_cVector2))
    {
        Vector2 *min, *max;
        Data_Get_Struct(minimum, Vector2, min);
        Data_Get_Struct(maximum, Vector2, max);

        x = NUMERIX_MIN(x, max->x);
        x = NUMERIX_MAX(x, min->x);

        y = NUMERIX_MIN(y, max->y);
        y = NUMERIX_MAX(y, min->y);
    }
    else
    {
        float minf = NUM2FLT(minimum);
        float maxf = NUM2FLT(maximum);

        x = NUMERIX_MIN(x, maxf);
        x = NUMERIX_MAX(x, minf);

        y = NUMERIX_MIN(y, maxf);
        y = NUMERIX_MAX(y, minf);

    }

    result->x = x;
    result->y = y;
    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector2_lerp_s(VALUE klass, VALUE vec1, VALUE vec2, VALUE amount) {
    Vector2 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector2, v1);
    Data_Get_Struct(vec2, Vector2, v2);
    result = ALLOC(Vector2);

    float w = NUMERIX_CLAMP(NUM2FLT(amount), 0.0f, 1.0f);

    result->x = v1->x + (v2->x - v1->x) * w;
    result->y = v1->y + (v2->y - v1->y) * w;

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector2_transform_s(VALUE klass, VALUE vector, VALUE matrix) {
    Vector2 *v, *result;
    Data_Get_Struct(vector, Vector2, v);
    result = ALLOC(Vector2);
    if (NUMERIX_TYPE_P(matrix, rb_cMatrix3x2))
    {
        Matrix3x2 *m3;
        Data_Get_Struct(matrix, Matrix3x2, m3);

        result->x = v->x * m3->m11 + v->y * m3->m21 + m3->m31;
        result->y = v->x * m3->m12 + v->y * m3->m22 + m3->m32;
    }
    else if (NUMERIX_TYPE_P(matrix, rb_cMatrix4x4))
    {
        Matrix4x4 *m4;
        Data_Get_Struct(matrix, Matrix4x4, m4);

        result->x = v->x * m4->m11 + v->y * m4->m21 + m4->m41;
        result->y = v->x * m4->m12 + v->y * m4->m22 + m4->m42;
    }
    else
    {
        Quaternion *q;
        Data_Get_Struct(matrix, Quaternion, q);

        float x2 = q->x + q->x;
        float y2 = q->y + q->y;
        float z2 = q->z + q->z;

        float wz2 = q->w * z2;
        float xx2 = q->x * x2;
        float xy2 = q->x * y2;
        float yy2 = q->y * y2;
        float zz2 = q->z * z2;
 
        result->x = v->x * (1.0f - yy2 - zz2) + v->y * (xy2 - wz2);
        result->y = v->x * (xy2 + wz2) + v->y * (1.0f - xx2 - zz2);
    }

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector2_transform_normal_s(VALUE klass, VALUE vector, VALUE matrix) {
    Vector2 *v, *result;
    Data_Get_Struct(vector, Vector2, v);
    result = ALLOC(Vector2);
    if (NUMERIX_TYPE_P(matrix, rb_cMatrix3x2))
    {
        Matrix3x2 *m3;
        Data_Get_Struct(matrix, Matrix3x2, m3);

        result->x = v->x * m3->m11 + v->y * m3->m21;
        result->y = v->x * m3->m12 + v->y * m3->m22;
    }
    else
    {
        Matrix4x4 *m4;
        Data_Get_Struct(matrix, Matrix4x4, m4);

        result->x = v->x * m4->m11 + v->y * m4->m21;
        result->y = v->x * m4->m12 + v->y * m4->m22;
    }

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector2_min_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector2 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector2, v1);
    Data_Get_Struct(vec2, Vector2, v2);
    result = ALLOC(Vector2);

    result->x = NUMERIX_MIN(v1->x, v2->x);
    result->y = NUMERIX_MIN(v1->y, v2->y);

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector2_max_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector2 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector2, v1);
    Data_Get_Struct(vec2, Vector2, v2);
    result = ALLOC(Vector2);

    result->x = NUMERIX_MAX(v1->x, v2->x);
    result->y = NUMERIX_MAX(v1->y, v2->y);

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_vector2_create_norm(VALUE klass, VALUE x, VALUE y) {
    Vector2 *v = ALLOC(Vector2);
    float vx = NUM2FLT(x);
    float vy = NUM2FLT(y);

    float inv = 1.0f / sqrtf(vx * vx + vy * vy);
    v->x = vx * inv;
    v->y = vy * inv;

    return NUMERIX_WRAP(klass, v);
}