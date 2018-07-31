
#include "vector2.h"


void Init_vector2(VALUE outer) {
    
    rb_define_alloc_func(rb_cVector2, rb_vector2_alloc);

    // Instance Methods
    rb_define_method(rb_cVector2, "initialize", rb_vector2_initialize, -1);
    rb_define_method(rb_cVector2, "length", rb_vector2_length, 0);
    rb_define_method(rb_cVector2, "length_squared", rb_vector2_length_squared, 0);

    // Conversion
    rb_define_method(rb_cVector2, "to_s", rb_vector2_to_s, 0);

    // Operators
    rb_define_method(rb_cVector2, "+", rb_vector2_add, 1);
    rb_define_method(rb_cVector2, "-", rb_vector2_subtract, 1);
    rb_define_method(rb_cVector2, "*", rb_vector2_multiply, 1);
    rb_define_method(rb_cVector2, "/", rb_vector2_divide, 1);
    rb_define_method(rb_cVector2, "==", rb_vector2_equal, 1);
    rb_define_method(rb_cVector2, "-@", rb_vector2_negate, 0);

    // Singleton Methods
    rb_define_singleton_method(rb_cVector2, "zero", rb_vector2_alloc, 0);
    rb_define_singleton_method(rb_cVector2, "one", rb_vector2_one, 0);
    rb_define_singleton_method(rb_cVector2, "unit_x", rb_vector2_unit_x, 0);
    rb_define_singleton_method(rb_cVector2, "unit_y", rb_vector2_unit_y, 0);
    rb_define_singleton_method(rb_cVector2, "distance", rb_vector2_distance_s, 2);
    rb_define_singleton_method(rb_cVector2, "distance_squared", rb_vector2_distance_squared_s, 2);
    rb_define_singleton_method(rb_cVector2, "normalize", rb_vector2_normalize_s, 1);
    rb_define_singleton_method(rb_cVector2, "reflect", rb_vector2_reflect_s, 2);
    rb_define_singleton_method(rb_cVector2, "clamp", rb_vector2_clamp_s, 3);
    rb_define_singleton_method(rb_cVector2, "lerp", rb_vector2_lerp_s, 3);
    rb_define_singleton_method(rb_cVector2, "transform", rb_vector2_transform_s, 2);
    rb_define_singleton_method(rb_cVector2, "transform_normal", rb_vector2_transform_normal_s, 2);
    rb_define_singleton_method(rb_cVector2, "min", rb_vector2_min_s, 2);
    rb_define_singleton_method(rb_cVector2, "max", rb_vector2_max_s, 2);
    rb_define_singleton_method(rb_cVector2, "abs", rb_vector2_abs_s, 1);
    rb_define_singleton_method(rb_cVector2, "sqrt", rb_vector2_sqrt_s, 1);
    rb_define_singleton_method(rb_cVector2, "dot", rb_vector2_dot_s, 2);
    rb_define_singleton_method(rb_cVector2, "add", rb_vector2_add_s, 2);
    rb_define_singleton_method(rb_cVector2, "subtract", rb_vector2_subtract_s, 2);
    rb_define_singleton_method(rb_cVector2, "multiply", rb_vector2_multiply_s, 2);
    rb_define_singleton_method(rb_cVector2, "divide", rb_vector2_divide_s, 2);
    rb_define_singleton_method(rb_cVector2, "equal?", rb_vector2_equal_s, 2);
    rb_define_singleton_method(rb_cVector2, "negate", rb_vector2_negate_s, 1);
    
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
            rb_raise(rb_eArgError, "wrong number of arguments (%d for 0, 1, 2)", argc);
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
    return rb_vector2_add_s(CLASS_OF(self), self, other);
}

VALUE rb_vector2_subtract(VALUE self, VALUE other) {
    return rb_vector2_subtract_s(CLASS_OF(self), self, other);
}

VALUE rb_vector2_multiply(VALUE self, VALUE other) {
    return rb_vector2_multiply_s(CLASS_OF(self), self, other);
}

VALUE rb_vector2_divide(VALUE self, VALUE other) {
    return rb_vector2_divide_s(CLASS_OF(self), self, other);
}

VALUE rb_vector2_equal(VALUE self, VALUE other) {
    return rb_vector2_equal_s(CLASS_OF(self), self, other);
}

VALUE rb_vector2_negate(VALUE self) {
    return rb_vector2_negate_s(CLASS_OF(self), self);
}

VALUE rb_vector2_to_s(VALUE self) {
    VECTOR2();
    return rb_sprintf("<%f, %f>", v->x, v->y);
}

static inline VALUE rb_vector2_distance_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector2 *v1, *v2;
    Data_Get_Struct(vec1, Vector2, v1);
    Data_Get_Struct(vec2, Vector2, v2);

    float dx = v1->x - v2->x;
    float dy = v1->y - v2->y;

    return DBL2NUM(sqrtf(dx * dx + dy * dy));
}

static inline VALUE rb_vector2_distance_squared_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector2 *v1, *v2;
    Data_Get_Struct(vec1, Vector2, v1);
    Data_Get_Struct(vec2, Vector2, v2);

    float dx = v1->x - v2->x;
    float dy = v1->y - v2->y;

    return DBL2NUM(dx * dx + dy * dy);
}

static inline VALUE rb_vector2_normalize_s(VALUE klass, VALUE vector2) {
    Vector2 *v, *result;
    Data_Get_Struct(vector2, Vector2, v);
    result = ALLOC(Vector2);

    float inv = 1.0f / sqrtf(v->x * v->x + v->y * v->y);
    result->x = v->x * inv;
    result->y = v->y * inv;

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector2_reflect_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector2 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector2, v1);
    Data_Get_Struct(vec2, Vector2, v2);
    result = ALLOC(Vector2);

    float dot = v1->x * v2->x + v1->y * v2->y;
    result->x = v1->x - 2.0f * dot * v2->x;
    result->y = v1->y - 2.0f * dot * v2->y;

    return NUMERIX_WRAP(klass, result);
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

static inline VALUE rb_vector2_abs_s(VALUE klass, VALUE vec) {
    Vector2 *v, *result;
    Data_Get_Struct(vec, Vector2, v);
    result = ALLOC(Vector2);

    result->x = fabsf(v->x);
    result->y = fabsf(v->y);

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector2_sqrt_s(VALUE klass, VALUE vec) {
    Vector2 *v, *result;
    Data_Get_Struct(vec, Vector2, v);
    result = ALLOC(Vector2);

    result->x = sqrtf(v->x);
    result->y = sqrtf(v->y);

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector2_dot_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector2 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector2, v1);
    Data_Get_Struct(vec2, Vector2, v2);

    return DBL2NUM(v1->x * v2->x + v1->y * v2->y);
}

static inline VALUE rb_vector2_add_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector2 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector2, v1);
    Data_Get_Struct(vec2, Vector2, v2);
    result = ALLOC(Vector2);

    result->x = v1->x + v2->x;
    result->y = v1->y + v2->y;

    return NUMERIX_WRAP(klass, result); 
}

static inline VALUE rb_vector2_subtract_s(VALUE klass, VALUE vec1, VALUE vec2) {
    Vector2 *v1, *v2, *result;
    Data_Get_Struct(vec1, Vector2, v1);
    Data_Get_Struct(vec2, Vector2, v2);
    result = ALLOC(Vector2);

    result->x = v1->x - v2->x;
    result->y = v1->y - v2->y;

    return NUMERIX_WRAP(klass, result); 
}

static inline VALUE rb_vector2_multiply_s(VALUE klass, VALUE vec, VALUE other) {
    Vector2 *v1, *result;
    Data_Get_Struct(vec, Vector2, v1);
    result = ALLOC(Vector2);

    if (NUMERIX_TYPE_P(other, rb_cVector2))
    {
        Vector2 *v2;
        Data_Get_Struct(other, Vector2, v2);
        result->x = v1->x * v2->x;
        result->y = v1->x * v2->y;
    }
    else
    {
        float scalar = NUM2FLT(other);
        result->x = v1->x * scalar;
        result->y = v1->x * scalar;
    }
    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector2_divide_s(VALUE klass, VALUE vec, VALUE other) {
    Vector2 *v1, *result;
    Data_Get_Struct(vec, Vector2, v1);
    result = ALLOC(Vector2);

    if (NUMERIX_TYPE_P(other, rb_cVector2))
    {
        Vector2 *v2;
        Data_Get_Struct(other, Vector2, v2);
        result->x = v1->x / v2->x;
        result->y = v1->x / v2->y;
    }
    else
    {
        float scalar = 1.0f / NUM2FLT(other);
        result->x = v1->x * scalar;
        result->y = v1->x * scalar;
    }
    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector2_negate_s(VALUE klass, VALUE vec) {
    Vector2 *v, *result;
    Data_Get_Struct(vec, Vector2, v);
    result = ALLOC(Vector2);

    result->x = -v->x;
    result->y = -v->y;

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_vector2_equal_s(VALUE klass, VALUE vec, VALUE other) {
    if (!NUMERIX_INHERIT_P(CLASS_OF(vec), klass) || !NUMERIX_INHERIT_P(CLASS_OF(other), klass))
        return Qfalse;

    Vector2 *v1, *v2;
    Data_Get_Struct(vec, Vector2, v1);
    Data_Get_Struct(vec, Vector2, v2);
    
    return v1->x == v2->x && v1->y == v2->y ? Qtrue : Qfalse;
}
