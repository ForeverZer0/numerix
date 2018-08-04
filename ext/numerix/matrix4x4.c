
#include "matrix4x4.h"


void Init_matrix4x4(VALUE outer) {
    
    rb_define_alloc_func(rb_cMatrix4x4, rb_matrix4x4_allocate);
    rb_define_method(rb_cMatrix4x4, "initialize", rb_matrix4x4_initialize, -1);

    // Instance
    rb_define_method(rb_cMatrix4x4, "identity?", rb_matrix4x4_identity_p, 0);
    rb_define_method(rb_cMatrix4x4, "translation", rb_matrix4x4_translation, 0);
    rb_define_method(rb_cMatrix4x4, "translation=", rb_matrix4x4_translation_set, 1);
    rb_define_method(rb_cMatrix4x4, "determinant", rb_matrix4x4_determinant, 0);
    rb_define_method(rb_cMatrix4x4, "row", rb_matrix4x4_row, 1);
    rb_define_method(rb_cMatrix4x4, "column", rb_matrix4x4_column, 1);
    rb_define_method(rb_cMatrix4x4, "each_row", rb_matrix4x4_each_row, 0);
    rb_define_method(rb_cMatrix4x4, "each_column", rb_matrix4x4_each_column, 0);
    rb_define_method(rb_cMatrix4x4, "invert", rb_matrix4x4_invert, 0);
    rb_define_method(rb_cMatrix4x4, "invert!", rb_matrix4x4_invert_bang, 0);
    rb_define_method(rb_cMatrix4x4, "transform", rb_matrix4x4_transform, 1);
    rb_define_method(rb_cMatrix4x4, "transpose", rb_matrix4x4_transpose, 0);
    rb_define_method(rb_cMatrix4x4, "lerp", rb_matrix4x4_lerp, 2);
    rb_define_method(rb_cMatrix4x4, "lerp!", rb_matrix4x4_lerp_bang, 2);

    // Conversion
    rb_define_method(rb_cMatrix4x4, "to_s", rb_matrix4x4_to_s, 0);
    rb_define_method(rb_cMatrix4x4, "to_a", rb_matrix4x4_to_a, 0);
    rb_define_method(rb_cMatrix4x4, "to_h", rb_matrix4x4_to_h, 0);
    // to_mat3
    
    // Operators
    rb_define_method(rb_cMatrix4x4, "+", rb_matrix4x4_add, 1);
    rb_define_method(rb_cMatrix4x4, "-", rb_matrix4x4_subtract, 1);
    rb_define_method(rb_cMatrix4x4, "*", rb_matrix4x4_multiply, 1);
    rb_define_method(rb_cMatrix4x4, "-@", rb_matrix4x4_negate, 0);
    rb_define_method(rb_cMatrix4x4, "==", rb_matrix4x4_equal, 1);
    rb_define_method(rb_cMatrix4x4, "[]", rb_matrix4x4_aref, -1);
    rb_define_method(rb_cMatrix4x4, "[]=", rb_matrix4x4_aset, -1);

    // // Class
    rb_define_singleton_method(rb_cMatrix4x4, "identity", rb_matrix4x4_identity, 0);
    rb_define_singleton_method(rb_cMatrix4x4, "create_billboard", rb_matrix4x4_create_billboard, 4);
    rb_define_singleton_method(rb_cMatrix4x4, "create_constrained_billboard", rb_matrix4x4_create_constrained_billboard, 5);
    rb_define_singleton_method(rb_cMatrix4x4, "create_translation", rb_matrix4x4_create_translation, -1);
    rb_define_singleton_method(rb_cMatrix4x4, "create_scale", rb_matrix4x4_create_scale, -1);
    rb_define_singleton_method(rb_cMatrix4x4, "create_rotation_x", rb_matrix4x4_create_rotation_x, -1);
    rb_define_singleton_method(rb_cMatrix4x4, "create_rotation_y", rb_matrix4x4_create_rotation_y, -1);
    rb_define_singleton_method(rb_cMatrix4x4, "create_rotation_z", rb_matrix4x4_create_rotation_z, -1);
    rb_define_singleton_method(rb_cMatrix4x4, "from_axis_angle", rb_matrix4x4_from_axis_angle, 2);
    rb_define_singleton_method(rb_cMatrix4x4, "create_perspective_fov", rb_matrix4x4_create_perspective_fov, 4);
    rb_define_singleton_method(rb_cMatrix4x4, "create_perspective", rb_matrix4x4_create_perspective_fov, 4);
    rb_define_singleton_method(rb_cMatrix4x4, "create_perspective_off_center", rb_matrix4x4_create_perspective_off_center, 6);
    rb_define_singleton_method(rb_cMatrix4x4, "create_orthographic", rb_matrix4x4_create_orthographic, 4);
    rb_define_singleton_method(rb_cMatrix4x4, "create_orthographic_off_center", rb_matrix4x4_create_orthographic_off_center, 6);
    rb_define_singleton_method(rb_cMatrix4x4, "create_look_at", rb_matrix4x4_create_look_at, 3);
    rb_define_singleton_method(rb_cMatrix4x4, "create_world", rb_matrix4x4_create_world, 3);
    rb_define_singleton_method(rb_cMatrix4x4, "from_quaternion", rb_matrix4x4_from_quaternion, 1);
    rb_define_singleton_method(rb_cMatrix4x4, "from_yaw_pitch_roll", rb_matrix4x4_from_yaw_pitch_roll, 3);
    rb_define_singleton_method(rb_cMatrix4x4, "create_shadow", rb_matrix4x4_create_shadow, 2);
    rb_define_singleton_method(rb_cMatrix4x4, "create_reflection", rb_matrix4x4_create_reflection, 1);
    rb_define_singleton_method(rb_cMatrix4x4, "lerp", rb_matrix4x4_lerp_s, 3);
}

static inline void numerix_cross_norm(Vector3 *v1, Vector3 *v2, Vector3 *result) {
    float x = v1->y * v2->z - v1->z * v2->y;
    float y = v1->z * v2->x - v1->x * v2->z;
    float z = v1->x * v2->y - v1->y * v2->x;
    float invLength = 1.0f / sqrtf(x * x + y * y + z * z);
    result->x = x * invLength;
    result->y = y * invLength;
    result->z = z * invLength;
}

static inline void numerix_vec3_normalize(Vector3 *v) {
    float invLength = 1.0f / sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x *= invLength;
    v->y *= invLength;
    v->z *= invLength;
}

static inline void numerix_vec3_cross(Vector3 *v1, Vector3 *v2, Vector3 *result) {
    result->x = v1->y * v2->z - v1->z * v2->y;
    result->y = v1->z * v2->x - v1->x * v2->z;
    result->z = v1->x * v2->y - v1->y * v2->x;
}

static inline float numerix_vec3_dot(Vector3 *v1, Vector3 *v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

static VALUE rb_matrix4x4_allocate(VALUE klass) {
    Matrix4x4 *m = ALLOC(Matrix4x4);
    memset(m, 0, sizeof(Matrix4x4));
    return NUMERIX_WRAP(klass, m);
}

VALUE rb_matrix4x4_initialize(int argc, VALUE *argv, VALUE self) {
    MATRIX4X4();
    if (argc == 16)
    {
        m->m11 = NUM2FLT(argv[0]);
        m->m12 = NUM2FLT(argv[1]);
        m->m13 = NUM2FLT(argv[2]);
        m->m14 = NUM2FLT(argv[3]);
        m->m21 = NUM2FLT(argv[4]);
        m->m22 = NUM2FLT(argv[5]);
        m->m23 = NUM2FLT(argv[6]);
        m->m24 = NUM2FLT(argv[7]);
        m->m31 = NUM2FLT(argv[8]);
        m->m32 = NUM2FLT(argv[9]);
        m->m33 = NUM2FLT(argv[10]);
        m->m34 = NUM2FLT(argv[11]);
        m->m41 = NUM2FLT(argv[12]);
        m->m42 = NUM2FLT(argv[13]);
        m->m43 = NUM2FLT(argv[14]);
        m->m44 = NUM2FLT(argv[15]);
    }
    else if (argc == 1)
    {
        if (NUMERIX_TYPE_P(argv[0], rb_cMatrix3x2))
        {
            Matrix3x2 *value;
            Data_Get_Struct(argv[0], Matrix3x2, value);
            m->m11 = value->m11;
            m->m12 = value->m12;
            m->m13 = 0.0f;
            m->m14 = 0.0f;
            m->m21 = value->m21;
            m->m22 = value->m22;
            m->m23 = 0.0f;
            m->m24 = 0.0f;
            m->m31 = 0.0f;
            m->m32 = 0.0f;
            m->m33 = 1.0f;
            m->m34 = 0.0f;
            m->m41 = value->m31;
            m->m42 = value->m32;
            m->m43 = 0.0f;
            m->m44 = 1.0f;
        }
        else
        {
            float value = NUM2FLT(argv[0]);
            float *p = (float*) m;
            for (int i = 0; i < 16; i++)
                p[i] = value;
        }
    }
    else if (argc != 0)
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 0, 16)", argc);

    return Qnil;
}

VALUE rb_matrix4x4_lerp(VALUE self, VALUE other, VALUE amount) {
    Matrix4x4 *m1, *m2, *result;
    Data_Get_Struct(self, Matrix4x4, m1);
    Data_Get_Struct(other, Matrix4x4, m2);
    result = ALLOC(Matrix4x4);
    float weight = NUMERIX_CLAMP(NUM2FLT(amount), 0.0f, 1.0f);

    // First row
    result->m11 = m1->m11 + (m2->m11 - m1->m11) * weight;
    result->m12 = m1->m12 + (m2->m12 - m1->m12) * weight;
    result->m13 = m1->m13 + (m2->m13 - m1->m13) * weight;
    result->m14 = m1->m14 + (m2->m14 - m1->m14) * weight;

    // Second row
    result->m21 = m1->m21 + (m2->m21 - m1->m21) * weight;
    result->m22 = m1->m22 + (m2->m22 - m1->m22) * weight;
    result->m23 = m1->m23 + (m2->m23 - m1->m23) * weight;
    result->m24 = m1->m24 + (m2->m24 - m1->m24) * weight;

    // Third row
    result->m31 = m1->m31 + (m2->m31 - m1->m31) * weight;
    result->m32 = m1->m32 + (m2->m32 - m1->m32) * weight;
    result->m33 = m1->m33 + (m2->m33 - m1->m33) * weight;
    result->m34 = m1->m34 + (m2->m34 - m1->m34) * weight;

    // Fourth row
    result->m41 = m1->m41 + (m2->m41 - m1->m41) * weight;
    result->m42 = m1->m42 + (m2->m42 - m1->m42) * weight;
    result->m43 = m1->m43 + (m2->m43 - m1->m43) * weight;
    result->m44 = m1->m44 + (m2->m44 - m1->m44) * weight;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_matrix4x4_lerp_bang(VALUE self, VALUE other, VALUE amount) {
    Matrix4x4 *m1, *m2;
    Data_Get_Struct(self, Matrix4x4, m1);
    Data_Get_Struct(other, Matrix4x4, m2);
    float weight = NUMERIX_CLAMP(NUM2FLT(amount), 0.0f, 1.0f);

    // First row
    m1->m11 = m1->m11 + (m2->m11 - m1->m11) * weight;
    m1->m12 = m1->m12 + (m2->m12 - m1->m12) * weight;
    m1->m13 = m1->m13 + (m2->m13 - m1->m13) * weight;
    m1->m14 = m1->m14 + (m2->m14 - m1->m14) * weight;

    // Second row
    m1->m21 = m1->m21 + (m2->m21 - m1->m21) * weight;
    m1->m22 = m1->m22 + (m2->m22 - m1->m22) * weight;
    m1->m23 = m1->m23 + (m2->m23 - m1->m23) * weight;
    m1->m24 = m1->m24 + (m2->m24 - m1->m24) * weight;

    // Third row
    m1->m31 = m1->m31 + (m2->m31 - m1->m31) * weight;
    m1->m32 = m1->m32 + (m2->m32 - m1->m32) * weight;
    m1->m33 = m1->m33 + (m2->m33 - m1->m33) * weight;
    m1->m34 = m1->m34 + (m2->m34 - m1->m34) * weight;

    // Fourth row
    m1->m41 = m1->m41 + (m2->m41 - m1->m41) * weight;
    m1->m42 = m1->m42 + (m2->m42 - m1->m42) * weight;
    m1->m43 = m1->m43 + (m2->m43 - m1->m43) * weight;
    m1->m44 = m1->m44 + (m2->m44 - m1->m44) * weight;

    return self;
}

VALUE rb_matrix4x4_identity_p(VALUE self) {
    MATRIX4X4();
    // Check diagonal element first for early out.
    return m->m11 == 1.0f && m->m22 == 1.0f && m->m33 == 1.0f && m->m44 == 1.0f && 
           m->m12 == 0.0f && m->m13 == 0.0f && m->m14 == 0.0f && m->m21 == 0.0f && 
           m->m23 == 0.0f && m->m24 == 0.0f && m->m31 == 0.0f && m->m32 == 0.0f && 
           m->m34 == 0.0f && m->m41 == 0.0f && m->m42 == 0.0f && m->m43 == 0.0f ? Qtrue : Qfalse;
}

VALUE rb_matrix4x4_translation(VALUE self) {
    MATRIX4X4();
    Vector3 *v = ALLOC(Vector3);
    v->x = m->m41;
    v->y = m->m42;
    v->z = m->m43;
    return NUMERIX_WRAP(rb_cVector3, v);
}

VALUE rb_matrix4x4_translation_set(VALUE self, VALUE value) {
    MATRIX4X4();
    Vector3 *v;
    Data_Get_Struct(value, Vector3, v);
    m->m41 = v->x;
    m->m42 = v->y;
    m->m43 = v->z;
    return value;
}

VALUE rb_matrix4x4_determinant(VALUE self) {
    Matrix4x4 *matrix;
    Data_Get_Struct(self, Matrix4x4, matrix);
    // | a b c d |     | f g h |     | e g h |     | e f h |     | e f g |
    // | e f g h | = a | j k l | - b | i k l | + c | i j l | - d | i j k |
    // | i j k l |     | n o p |     | m o p |     | m n p |     | m n o |
    // | m n o p |
    //
    //   | f g h |
    // a | j k l | = a ( f ( kp - lo ) - g ( jp - ln ) + h ( jo - kn ) )
    //   | n o p |
    //
    //   | e g h |     
    // b | i k l | = b ( e ( kp - lo ) - g ( ip - lm ) + h ( io - km ) )
    //   | m o p |     
    //
    //   | e f h |
    // c | i j l | = c ( e ( jp - ln ) - f ( ip - lm ) + h ( in - jm ) )
    //   | m n p |
    //
    //   | e f g |
    // d | i j k | = d ( e ( jo - kn ) - f ( io - km ) + g ( in - jm ) )
    //   | m n o |
    //
    // Cost of operation
    // 17 adds and 28 muls.
    //
    // add: 6 + 8 + 3 = 17
    // mul: 12 + 16 = 28

    float a = matrix->m11, b = matrix->m12, c = matrix->m13, d = matrix->m14;
    float e = matrix->m21, f = matrix->m22, g = matrix->m23, h = matrix->m24;
    float i = matrix->m31, j = matrix->m32, k = matrix->m33, l = matrix->m34;
    float m = matrix->m41, n = matrix->m42, o = matrix->m43, p = matrix->m44;

    float kp_lo = k * p - l * o;
    float jp_ln = j * p - l * n;
    float jo_kn = j * o - k * n;
    float ip_lm = i * p - l * m;
    float io_km = i * o - k * m;
    float in_jm = i * n - j * m;

    return DBL2NUM(a * (f * kp_lo - g * jp_ln + h * jo_kn) -
                   b * (e * kp_lo - g * ip_lm + h * io_km) +
                   c * (e * jp_ln - f * ip_lm + h * in_jm) -
                   d * (e * jo_kn - f * io_km + g * in_jm));

}

VALUE rb_matrix4x4_to_s(VALUE self) {
    MATRIX4X4();
    return rb_sprintf("{{%f, %f, %f, %f}, {%f, %f, %f, %f}, {%f, %f, %f, %f}, {%f, %f, %f, %f}}",
        m->m11, m->m12, m->m13, m->m14, m->m21, m->m22, m->m23, m->m24,
        m->m31, m->m32, m->m33, m->m34, m->m41, m->m42, m->m43, m->m44);
}

VALUE rb_matrix4x4_equal(VALUE self, VALUE other) {
    if (CLASS_OF(other) != CLASS_OF(self))
        return Qfalse;
    Matrix4x4 *m1, *m2;
    Data_Get_Struct(self, Matrix4x4, m1);
    Data_Get_Struct(other, Matrix4x4, m2);
    return FLT_EQUAL(m1->m11, m2->m11) && FLT_EQUAL(m1->m12, m2->m12) && FLT_EQUAL(m1->m13, m2->m13) && FLT_EQUAL(m1->m14, m2->m14) &&
           FLT_EQUAL(m1->m21, m2->m21) && FLT_EQUAL(m1->m22, m2->m22) && FLT_EQUAL(m1->m23, m2->m23) && FLT_EQUAL(m1->m24, m2->m24) &&
           FLT_EQUAL(m1->m31, m2->m31) && FLT_EQUAL(m1->m32, m2->m32) && FLT_EQUAL(m1->m33, m2->m33) && FLT_EQUAL(m1->m34, m2->m34) &&
           FLT_EQUAL(m1->m41, m2->m41) && FLT_EQUAL(m1->m42, m2->m42) && FLT_EQUAL(m1->m43, m2->m43) && FLT_EQUAL(m1->m44, m2->m44) ? Qtrue : Qfalse;
}

VALUE rb_matrix4x4_to_a(VALUE self) {
    MATRIX4X4();
    VALUE array = rb_ary_new_capa(4);
    // Row 1
    VALUE r1 = rb_ary_new_capa(4);
    rb_ary_store(r1, 0, DBL2NUM(m->m11));
    rb_ary_store(r1, 1, DBL2NUM(m->m12));
    rb_ary_store(r1, 2, DBL2NUM(m->m13));
    rb_ary_store(r1, 3, DBL2NUM(m->m14));
    rb_ary_push(array, r1);
    // Row 2
    VALUE r2 = rb_ary_new_capa(4);
    rb_ary_store(r2, 0, DBL2NUM(m->m21));
    rb_ary_store(r2, 1, DBL2NUM(m->m22));
    rb_ary_store(r2, 2, DBL2NUM(m->m23));
    rb_ary_store(r2, 3, DBL2NUM(m->m24));
    rb_ary_push(array, r2);
    // Row 3
    VALUE r3 = rb_ary_new_capa(4);
    rb_ary_store(r3, 0, DBL2NUM(m->m31));
    rb_ary_store(r3, 1, DBL2NUM(m->m32));
    rb_ary_store(r3, 2, DBL2NUM(m->m33));
    rb_ary_store(r3, 3, DBL2NUM(m->m34));
    rb_ary_push(array, r3);
    // Row 4
    VALUE r4 = rb_ary_new_capa(4);
    rb_ary_store(r4, 0, DBL2NUM(m->m41));
    rb_ary_store(r4, 1, DBL2NUM(m->m42));
    rb_ary_store(r4, 2, DBL2NUM(m->m43));
    rb_ary_store(r4, 3, DBL2NUM(m->m44));
    rb_ary_push(array, r4);
    return array;
}

VALUE rb_matrix4x4_row(VALUE self, VALUE row) {
    MATRIX4X4();
    VALUE args = rb_ary_new_capa(4);
    int r = NUM2INT(row);
    switch (r)
    {
        case 0:
        {
            rb_ary_push(args, DBL2NUM(m->m11));
            rb_ary_push(args, DBL2NUM(m->m12));
            rb_ary_push(args, DBL2NUM(m->m13));
            rb_ary_push(args, DBL2NUM(m->m14));
            break;
        }
        case 1:
        {
            rb_ary_push(args, DBL2NUM(m->m21));
            rb_ary_push(args, DBL2NUM(m->m22));
            rb_ary_push(args, DBL2NUM(m->m23));
            rb_ary_push(args, DBL2NUM(m->m24));
            break;
        }
        case 2:
        {
            rb_ary_push(args, DBL2NUM(m->m31));
            rb_ary_push(args, DBL2NUM(m->m32));
            rb_ary_push(args, DBL2NUM(m->m33));
            rb_ary_push(args, DBL2NUM(m->m34));
            break;
        }
        case 3:
        {
            rb_ary_push(args, DBL2NUM(m->m41));
            rb_ary_push(args, DBL2NUM(m->m42));
            rb_ary_push(args, DBL2NUM(m->m43));
            rb_ary_push(args, DBL2NUM(m->m44));
            break;
        }
        default:
            break;
    }
    return args;
}

VALUE rb_matrix4x4_column(VALUE self, VALUE column) {
    MATRIX4X4();
    VALUE args = rb_ary_new_capa(4);
    int c = NUM2INT(column);
    switch (c)
    {
        case 0:
        {
            rb_ary_push(args, DBL2NUM(m->m11));
            rb_ary_push(args, DBL2NUM(m->m21));
            rb_ary_push(args, DBL2NUM(m->m31));
            rb_ary_push(args, DBL2NUM(m->m41));
            break;
        }
        case 1:
        {
            rb_ary_push(args, DBL2NUM(m->m12));
            rb_ary_push(args, DBL2NUM(m->m22));
            rb_ary_push(args, DBL2NUM(m->m32));
            rb_ary_push(args, DBL2NUM(m->m42));
            break;
        }
        case 2:
        {
            rb_ary_push(args, DBL2NUM(m->m13));
            rb_ary_push(args, DBL2NUM(m->m23));
            rb_ary_push(args, DBL2NUM(m->m33));
            rb_ary_push(args, DBL2NUM(m->m43));
            break;
        }
        case 3:
        {
            rb_ary_push(args, DBL2NUM(m->m14));
            rb_ary_push(args, DBL2NUM(m->m24));
            rb_ary_push(args, DBL2NUM(m->m34));
            rb_ary_push(args, DBL2NUM(m->m44));
            break;
        }
        default:
            break;
    }
    return args;
}

VALUE rb_matrix4x4_to_h(VALUE self) {
    MATRIX4X4();
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, ID2SYM(rb_intern("m11")), DBL2NUM(m->m11));
    rb_hash_aset(hash, ID2SYM(rb_intern("m12")), DBL2NUM(m->m12));
    rb_hash_aset(hash, ID2SYM(rb_intern("m13")), DBL2NUM(m->m13));
    rb_hash_aset(hash, ID2SYM(rb_intern("m14")), DBL2NUM(m->m14));

    rb_hash_aset(hash, ID2SYM(rb_intern("m21")), DBL2NUM(m->m21));
    rb_hash_aset(hash, ID2SYM(rb_intern("m22")), DBL2NUM(m->m22));
    rb_hash_aset(hash, ID2SYM(rb_intern("m23")), DBL2NUM(m->m23));
    rb_hash_aset(hash, ID2SYM(rb_intern("m24")), DBL2NUM(m->m24));

    rb_hash_aset(hash, ID2SYM(rb_intern("m31")), DBL2NUM(m->m31));
    rb_hash_aset(hash, ID2SYM(rb_intern("m32")), DBL2NUM(m->m32));
    rb_hash_aset(hash, ID2SYM(rb_intern("m33")), DBL2NUM(m->m33));
    rb_hash_aset(hash, ID2SYM(rb_intern("m34")), DBL2NUM(m->m34));

    rb_hash_aset(hash, ID2SYM(rb_intern("m41")), DBL2NUM(m->m41));
    rb_hash_aset(hash, ID2SYM(rb_intern("m42")), DBL2NUM(m->m42));
    rb_hash_aset(hash, ID2SYM(rb_intern("m43")), DBL2NUM(m->m43));
    rb_hash_aset(hash, ID2SYM(rb_intern("m44")), DBL2NUM(m->m44));
    return hash;
}

VALUE rb_matrix4x4_each_row(VALUE self) {
    MATRIX4X4();
    for (int i = 0; i < 4; i++)
    {
        VALUE index = INT2NUM(i);
        rb_yield(rb_matrix4x4_row(self, index));
    }
    return self;
}

VALUE rb_matrix4x4_each_column(VALUE self) {
    MATRIX4X4();
    for (int i = 0; i < 4; i++)
    {
        VALUE index = INT2NUM(i);
        rb_yield(rb_matrix4x4_column(self, index));
    }
    return self;
}

VALUE rb_matrix4x4_aref(int argc, VALUE *argv, VALUE self) {
    if (argc == 1)
    {
        return rb_call_super(1, argv);
    }
    else if (argc == 2)
    {
        int r = NUM2INT(argv[0]);
        int c = NUM2INT(argv[1]);
        if (r < 0 || r > 3 || c < 0 || c > 3)
            return Qnil;
        argv[0] = INT2NUM(r + (c * 4));
        return rb_call_super(1, argv);
    }
    rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 2)", argc);
    return Qnil;
}

VALUE rb_matrix4x4_aset(int argc, VALUE *argv, VALUE self) {
    if (argc == 2)
    {
        return rb_call_super(2, argv); 
    }
    else if (argc == 3)
    {
        int r = NUM2INT(argv[0]);
        int c = NUM2INT(argv[1]);
        if (r < 0 || r > 3 || c < 0 || c > 3)
            return Qnil;
        argv[1] = INT2NUM(r + (c * 4));
        return rb_call_super(2, &argv[1]);
    }
    rb_raise(rb_eArgError, "wrong number of arguments (%d for 2, 3)", argc);
    return Qnil; 
}

VALUE rb_matrix4x4_identity(VALUE klass) {
    Matrix4x4 *m = ALLOC(Matrix4x4);
    m->m11 = 1.0f;
    m->m12 = 0.0f;
    m->m13 = 0.0f;
    m->m14 = 0.0f;
    m->m21 = 0.0f;
    m->m22 = 1.0f;
    m->m23 = 0.0f;
    m->m24 = 0.0f;
    m->m31 = 0.0f;
    m->m32 = 0.0f;
    m->m33 = 1.0f;
    m->m34 = 0.0f;
    m->m41 = 0.0f;
    m->m42 = 0.0f;
    m->m43 = 0.0f;
    m->m44 = 1.0f;
    return NUMERIX_WRAP(klass, m);
}

VALUE rb_matrix4x4_create_billboard(VALUE klass, VALUE position, VALUE camera, VALUE up, VALUE forward) {
    const float epsilon = 1e-4f;
    Vector3 *pos, *cam, *u, *f;
    Data_Get_Struct(position, Vector3, pos);
    Data_Get_Struct(camera, Vector3, cam);
    Data_Get_Struct(up, Vector3, u);
    Data_Get_Struct(forward, Vector3, f);

   Vector3 *axis = xmalloc(sizeof(Vector3) * 3);

    axis[2].x = pos->x - cam->x;
    axis[2].y = pos->y - cam->y;
    axis[2].z = pos->z - cam->z;

    float norm = axis[2].x * axis[2].x + axis[2].y * axis[2].y + axis[2].z * axis[2].z;

    if (norm < epsilon)
    {
        axis[2].x = -f->x;
        axis[2].y = -f->y;
        axis[2].z = -f->z;
    }
    else
    {
        float inverseNorm = 1.0f / sqrtf(norm);
        axis[2].x *= inverseNorm;
        axis[2].y *= inverseNorm;
        axis[2].z *= inverseNorm;
    }

    numerix_cross_norm(u, &axis[2], &axis[0]);
    numerix_vec3_cross(&axis[2], &axis[0], &axis[1]);

    Matrix4x4 *result = ALLOC(Matrix4x4);

    result->m11 = axis[0].x;
    result->m12 = axis[0].y;
    result->m13 = axis[0].z;
    result->m14 = 0.0f;
    result->m21 = axis[1].x;
    result->m22 = axis[1].y;
    result->m23 = axis[1].z;
    result->m24 = 0.0f;
    result->m31 = axis[2].x;
    result->m32 = axis[2].y;
    result->m33 = axis[2].z;
    result->m34 = 0.0f;

    result->m41 = pos->x;
    result->m42 = pos->y;
    result->m43 = pos->z;
    result->m44 = 1.0f;

    xfree(axis);

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix4x4_create_constrained_billboard(VALUE klass, VALUE position, VALUE rotate, VALUE camera, VALUE up, VALUE forward) {
    const float epsilon = 1e-4f;
    const float minAngle = 1.0f - (0.1f * (NUMERIX_PI / 180.0f)); // 0.1 degrees

    Vector3 *pos, *cam, *r, *u, *f;
    Data_Get_Struct(position, Vector3, pos);
    Data_Get_Struct(camera, Vector3, cam);
    Data_Get_Struct(rotate, Vector3, r);
    Data_Get_Struct(up, Vector3, u);
    Data_Get_Struct(forward, Vector3, f);

    Vector3 *axis = xmalloc(sizeof(Vector3) * 3);
    Vector3 *faceDir = xmalloc(sizeof(Vector3));

    faceDir->x = pos->x - cam->x;
    faceDir->y = pos->y - cam->y;
    faceDir->z = pos->z - cam->z;

    float norm = faceDir->x * faceDir->x + faceDir->y * faceDir->y + faceDir->z * faceDir->z;
    if (norm < epsilon)
    {
        faceDir->x = -f->x;
        faceDir->y = -f->y;
        faceDir->z = -f->z;
    }
    else
    {
        float invNorm = 1.0f / sqrtf(norm);
        faceDir->x *= invNorm;
        faceDir->y *= invNorm;
        faceDir->z *= invNorm;
    }

    // Treat the case when angle between faceDir and rotateAxis is too close to 0.
    float dot = numerix_vec3_dot(r, faceDir);

    if (fabsf(dot) > minAngle)
    {
        memcpy(&axis[2], f, sizeof(Vector2));
        // Make sure passed values are useful for compute.
        dot = numerix_vec3_dot(r, &axis[2]);

        if (fabsf(dot) > minAngle)
        {
            axis[2].y = 0.0f;
            if (fabsf(r->z) > minAngle)
            {
                axis[2].x = 1.0f;
                axis[2].z = 0.0f;
            }
            else
            {
                axis[2].x = 0.0f;
                axis[2].z = -1.0f;
            }
        }
        numerix_cross_norm(r, &axis[2], &axis[0]);
        numerix_cross_norm(&axis[0], r, &axis[2]);
    }
    else
    {
        numerix_cross_norm(r, faceDir, &axis[0]);
        numerix_cross_norm(&axis[0], &axis[1], &axis[2]);
    }

    Matrix4x4 *result = ALLOC(Matrix4x4);

    result->m11 = axis[0].x;
    result->m12 = axis[0].y;
    result->m13 = axis[0].z;
    result->m14 = 0.0f;
    result->m21 = axis[1].x;
    result->m22 = axis[1].y;
    result->m23 = axis[1].z;
    result->m24 = 0.0f;
    result->m31 = axis[2].x;
    result->m32 = axis[2].y;
    result->m33 = axis[2].z;
    result->m34 = 0.0f;

    result->m41 = pos->x;
    result->m42 = pos->y;
    result->m43 = pos->z;
    result->m44 = 1.0f;

    xfree(axis);
    xfree(faceDir);

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix4x4_create_translation(int argc, VALUE *argv, VALUE klass) {
    float x, y, z;
    if (argc == 1)
    {
        Vector3 *v; 
        Data_Get_Struct(argv[0], Vector3, v);
        x = v->x;
        y = v->y;
        z = v->z;
    }
    else if (argc == 3)
    {
        x = NUM2FLT(argv[0]);
        y = NUM2FLT(argv[1]);
        z = NUM2FLT(argv[2]);
    }
    else
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 3)", argc);

    Matrix4x4 *result = ALLOC(Matrix4x4);
    result->m11 = 1.0f;
    result->m12 = 0.0f;
    result->m13 = 0.0f;
    result->m14 = 0.0f;
    result->m21 = 0.0f;
    result->m22 = 1.0f;
    result->m23 = 0.0f;
    result->m24 = 0.0f;
    result->m31 = 0.0f;
    result->m32 = 0.0f;
    result->m33 = 1.0f;
    result->m34 = 0.0f;

    result->m41 = x;
    result->m42 = y;
    result->m43 = z;
    result->m44 = 1.0f;

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix4x4_create_scale(int argc, VALUE *argv, VALUE klass) {
    float xscale, yscale, zscale, tx = 0.0f, ty = 0.0f, tz = 0.0f;

    switch (argc)
    {
        case 1:
        {
            if (NUMERIX_TYPE_P(argv[0], rb_cVector3)) // (vec3)
            {
                Vector3 *vec3;
                Data_Get_Struct(argv[0], Vector3, vec3);
                xscale = vec3->x;
                yscale = vec3->y;
                zscale = vec3->z;
            }
            else   // (float)
            {
                xscale = yscale = zscale = NUM2FLT(argv[0]);
            }
            break;
        }
        case 2:
        {
            Vector3 *cp;
            Data_Get_Struct(argv[1], Vector3, cp);
            if (NUMERIX_TYPE_P(argv[0], rb_cVector3)) // (vec3, vec3)
            {
                Vector3 *v3;
                Data_Get_Struct(argv[1], Vector3, v3);
                xscale = v3->x;
                yscale = v3->y;
                zscale = v3->z;
            }
            else // (float, vec3)
            {
                xscale = yscale = zscale = NUM2FLT(argv[0]);
            }
            tx = cp->x * (1.0f - xscale);
            ty = cp->y * (1.0f - yscale);
            tz = cp->z * (1.0f - zscale);
            break;
        }
        case 3: // (float, float, float)
        {
            xscale = NUM2FLT(argv[0]);
            yscale = NUM2FLT(argv[1]);
            zscale = NUM2FLT(argv[2]);
            break;
        }
        case 4: // (float, float, float, vec3)
        {
            xscale = NUM2FLT(argv[0]);
            yscale = NUM2FLT(argv[1]);
            zscale = NUM2FLT(argv[2]);
            Vector3 *center;
            Data_Get_Struct(argv[3], Vector3, center);
            tx = center->x * (1.0f - xscale);
            ty = center->y * (1.0f - yscale);
            tz = center->z * (1.0f - zscale);
            break;
        }
        default:
        {
            rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 2, 3, 4)", argc);
            break;
        }
    }
    Matrix4x4 *result = ALLOC(Matrix4x4);
    result->m11 = xscale;
    result->m12 = 0.0f;
    result->m13 = 0.0f;
    result->m14 = 0.0f;
    result->m21 = 0.0f;
    result->m22 = yscale;
    result->m23 = 0.0f;
    result->m24 = 0.0f;
    result->m31 = 0.0f;
    result->m32 = 0.0f;
    result->m33 = zscale;
    result->m34 = 0.0f;
    result->m41 = tx;
    result->m42 = ty;
    result->m43 = tz;
    result->m44 = 1.0f;

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix4x4_create_rotation_x(int argc, VALUE *argv, VALUE klass) {
    if (argc != 1 && argc != 2)
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 2)", argc);

    float radians = NUM2FLT(argv[0]);
    float c = cosf(radians);
    float s = sinf(radians);
    float y = 0.0f, z = 0.0f;
    if (argc == 2)
    {
        Vector3 *center;
        Data_Get_Struct(argv[1], Vector3, center);
        y = center->y * (1.0f - c) + center->z * s;
        z = center->z * (1.0f - c) - center->y * s;
    }

    Matrix4x4 *result = ALLOC(Matrix4x4);
    // [  1  0  0  0 ]
    // [  0  c  s  0 ]
    // [  0 -s  c  0 ]
    // [  0  y  z  1 ]
    result->m11 = 1.0f;
    result->m12 = 0.0f;
    result->m13 = 0.0f;
    result->m14 = 0.0f;
    result->m21 = 0.0f;
    result->m22 = c;
    result->m23 = s;
    result->m24 = 0.0f;
    result->m31 = 0.0f;
    result->m32 = -s;
    result->m33 = c;
    result->m34 = 0.0f;
    result->m41 = 0.0f;
    result->m42 = y;
    result->m43 = z;
    result->m44 = 1.0f;

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix4x4_create_rotation_y(int argc, VALUE *argv, VALUE klass) {
    if (argc != 1 && argc != 2)
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 2)", argc);

    float radians = NUM2FLT(argv[0]);
    float c = cosf(radians);
    float s = sinf(radians);
    float x = 0.0f, z = 0.0f;
    if (argc == 2)
    {
        Vector3 *center;
        Data_Get_Struct(argv[1], Vector3, center);
        x = center->x * (1.0f - c) - center->z * s;
        z = center->z * (1.0f - c) + center->x * s;
    }

    Matrix4x4 *result = ALLOC(Matrix4x4);
    // [  c  0 -s  0 ]
    // [  0  1  0  0 ]
    // [  s  0  c  0 ]
    // [  x  0  z  1 ]
    result->m11 = c;
    result->m12 = 0.0f;
    result->m13 = -s;
    result->m14 = 0.0f;
    result->m21 = 0.0f;
    result->m22 = 1.0f;
    result->m23 = 0.0f;
    result->m24 = 0.0f;
    result->m31 = s;
    result->m32 = 0.0f;
    result->m33 = c;
    result->m34 = 0.0f;
    result->m41 = x;
    result->m42 = 0.0f;
    result->m43 = z;
    result->m44 = 1.0f;

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix4x4_create_rotation_z(int argc, VALUE *argv, VALUE klass) {
    if (argc != 1 && argc != 2)
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 2)", argc);

    float radians = NUM2FLT(argv[0]);
    float c = cosf(radians);
    float s = sinf(radians);
    float x = 0.0f, y = 0.0f;
    if (argc == 2)
    {
        Vector3 *center;
        Data_Get_Struct(argv[1], Vector3, center);
        x = center->x * (1.0f - c) + center->y * s;
        y = center->y * (1.0f - c) - center->x * s;
    }

    Matrix4x4 *result = ALLOC(Matrix4x4);
    // [  c  s  0  0 ]
    // [ -s  c  0  0 ]
    // [  0  0  1  0 ]
    // [  x  y  0  1 ]
    result->m11 = c;
    result->m12 = s;
    result->m13 = 0.0f;
    result->m14 = 0.0f;
    result->m21 = -s;
    result->m22 = c;
    result->m23 = 0.0f;
    result->m24 = 0.0f;
    result->m31 = 0.0f;
    result->m32 = 0.0f;
    result->m33 = 1.0f;
    result->m34 = 0.0f;
    result->m41 = x;
    result->m42 = y;
    result->m43 = 0.0f;
    result->m44 = 1.0f;

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix4x4_from_axis_angle(VALUE klass, VALUE axis, VALUE angle) {
    // a: angle
    // x, y, z: unit vector for axis.
    //
    // Rotation matrix M can compute by using below equation.
    //
    //        T               T
    //  M = uu + (cos a)( I-uu ) + (sin a)S
    //
    // Where:
    //
    //  u = ( x, y, z )
    //
    //      [  0 -z  y ]
    //  S = [  z  0 -x ]
    //      [ -y  x  0 ]
    //
    //      [ 1 0 0 ]
    //  I = [ 0 1 0 ]
    //      [ 0 0 1 ]
    //
    //
    //     [  xx+cosa*(1-xx)   yx-cosa*yx-sina*z zx-cosa*xz+sina*y ]
    // M = [ xy-cosa*yx+sina*z    yy+cosa(1-yy)  yz-cosa*yz-sina*x ]
    //     [ zx-cosa*zx-sina*y zy-cosa*zy+sina*x   zz+cosa*(1-zz)  ]
    //

    float ang = NUM2FLT(angle);
    Vector3 *v;
    Data_Get_Struct(axis, Vector3, v);

    float x = v->x, y = v->y, z = v->z;
    float sa = sinf(ang), ca = cosf(ang);
    float xx = x * x, yy = y * y, zz = z * z;
    float xy = x * y, xz = x * z, yz = y * z;

    Matrix4x4 *result = ALLOC(Matrix4x4);

    result->m11 = xx + ca * (1.0f - xx);
    result->m12 = xy - ca * xy + sa * z;
    result->m13 = xz - ca * xz - sa * y;
    result->m14 = 0.0f;
    result->m21 = xy - ca * xy - sa * z;
    result->m22 = yy + ca * (1.0f - yy);
    result->m23 = yz - ca * yz + sa * x;
    result->m24 = 0.0f;
    result->m31 = xz - ca * xz + sa * y;
    result->m32 = yz - ca * yz - sa * x;
    result->m33 = zz + ca * (1.0f - zz);
    result->m34 = 0.0f;
    result->m41 = 0.0f;
    result->m42 = 0.0f;
    result->m43 = 0.0f;
    result->m44 = 1.0f;

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix4x4_create_perspective_fov(VALUE klass, VALUE fieldOfView, VALUE aspectRatio, VALUE nearDist, VALUE farDist) {
    float n = NUM2FLT(nearDist);
    float f = NUM2FLT(farDist);
    if (n <= 0.0f)
        rb_raise(rb_eRangeError, "near plane distance must be value greater than 0.0 (given %f)", n);
    if (f <= 0.0f)
        rb_raise(rb_eRangeError, "far plane distance must be value greater than 0.0 (given %f)", n);
    if (n <= 0.0f)
        rb_raise(rb_eRangeError, "near plane distance must be less than far plane distance");

    float ratio = NUM2FLT(aspectRatio);
    float fov = NUM2FLT(fieldOfView);
    if (fov <= 0.0f || fov >= NUMERIX_PI)
        rb_raise(rb_eRangeError, "field of view must be value greater than 0.0 and less than PI (given %f)", fov);

    Matrix4x4 *result = ALLOC(Matrix4x4);

    float yscale = 1.0f / tanf(fov * 0.5f);
    float xscale = yscale / ratio;

    result->m11 = xscale;
    result->m12 = result->m13 = result->m14 = 0.0f;

    result->m22 = yscale;
    result->m21 = result->m23 = result->m24 = 0.0f;

    result->m31 = result->m32 = 0.0f;
    result->m33 = f / (n - f);
    result->m34 = -1.0f;

    result->m41 = result->m42 = result->m44 = 0.0f;
    result->m43 = n * f / (n - f);
 
    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix4x4_create_perspective(VALUE klass, VALUE width, VALUE height, VALUE nearDist, VALUE farDist) {
    float n = NUM2FLT(nearDist);
    float f = NUM2FLT(farDist);
    if (n <= 0.0f)
        rb_raise(rb_eRangeError, "near plane distance must be value greater than 0.0 (given %f)", n);
    if (f <= 0.0f)
        rb_raise(rb_eRangeError, "far plane distance must be value greater than 0.0 (given %f)", n);
    if (n <= 0.0f)
        rb_raise(rb_eRangeError, "near plane distance must be less than far plane distance");

    float w = NUM2FLT(width);
    float h = NUM2FLT(height);

    Matrix4x4 *result = ALLOC(Matrix4x4);

    result->m11 = 2.0f * n / w;
    result->m12 = result->m13 = result->m14 = 0.0f;

    result->m22 = 2.0f * n / h;
    result->m21 = result->m23 = result->m24 = 0.0f;

    result->m33 = f / (n - f);
    result->m31 = result->m32 = 0.0f;
    result->m34 = -1.0f;

    result->m41 = result->m42 = result->m44 = 0.0f;
    result->m43 = n * f / (n - f);
 

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix4x4_create_perspective_off_center(VALUE klass, VALUE left, VALUE right, VALUE bottom, VALUE top, VALUE nearDist, VALUE farDist) {
    float n = NUM2FLT(nearDist);
    float f = NUM2FLT(farDist);
    if (n <= 0.0f)
        rb_raise(rb_eRangeError, "near plane distance must be value greater than 0.0 (given %f)", n);
    if (f <= 0.0f)
        rb_raise(rb_eRangeError, "far plane distance must be value greater than 0.0 (given %f)", n);
    if (n <= 0.0f)
        rb_raise(rb_eRangeError, "near plane distance must be less than far plane distance");

    float l = NUM2FLT(left);
    float r = NUM2FLT(right);
    float t = NUM2FLT(top);
    float b = NUM2FLT(bottom);
    Matrix4x4 *result = ALLOC(Matrix4x4);

    result->m11 = 2.0f * n / (r - l);
    result->m12 = result->m13 = result->m14 = 0.0f;

    result->m22 = 2.0f * n / (t - b);
    result->m21 = result->m23 = result->m24 = 0.0f;

    result->m31 = (l + r) / (r - l);
    result->m32 = (t + b) / (t - b);
    result->m33 = f / (n - f);
    result->m34 = -1.0f;

    result->m43 = n * f / (n - f);
    result->m41 = result->m42 = result->m44 = 0.0f;

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix4x4_create_orthographic(VALUE klass, VALUE width, VALUE height, VALUE zNearPlane, VALUE zFarPlane) {

    float n = NUM2FLT(zNearPlane);
    float f = NUM2FLT(zFarPlane);

    Matrix4x4 *result = ALLOC(Matrix4x4);

    result->m11 = 2.0f / NUM2FLT(width);
    result->m12 = result->m13 = result->m14 = 0.0f;

    result->m22 = 2.0f / NUM2FLT(height);
    result->m21 = result->m23 = result->m24 = 0.0f;

    result->m33 = 1.0f / (n - f);
    result->m31 = result->m32 = result->m34 = 0.0f;

    result->m41 = result->m42 = 0.0f;
    result->m43 = n / (n - f);
    result->m44 = 1.0f;

    return NUMERIX_WRAP(klass, result);  
}

VALUE rb_matrix4x4_create_orthographic_off_center(VALUE klass, VALUE left, VALUE right, VALUE bottom, VALUE top, VALUE zNearPlane, VALUE zFarPlane) {
    float n = NUM2FLT(zNearPlane);
    float f = NUM2FLT(zFarPlane);
    float l = NUM2FLT(left);
    float r = NUM2FLT(right);
    float t = NUM2FLT(top);
    float b = NUM2FLT(bottom);
    Matrix4x4 *result = ALLOC(Matrix4x4);

    result->m11 = 2.0f / (r - l);
    result->m12 = result->m13 = result->m14 = 0.0f;

    result->m22 = 2.0f / (t - b);
    result->m21 = result->m23 = result->m24 = 0.0f;

    result->m33 = 1.0f / (n - f);
    result->m31 = result->m32 = result->m34 = 0.0f;

    result->m41 = (l + r) / (l - r);
    result->m42 = (t + b) / (b - t);
    result->m43 = n / (n - f);
    result->m44 = 1.0f;

    return NUMERIX_WRAP(klass, result);  
}

VALUE rb_matrix4x4_create_look_at(VALUE klass, VALUE camPos, VALUE camTarget, VALUE camUp) {

    Vector3 *cam, *target, *up;
    Data_Get_Struct(camPos, Vector3, cam);
    Data_Get_Struct(camTarget, Vector3, target);
    Data_Get_Struct(camUp, Vector3, up);

    Vector3 *axis = xmalloc(sizeof(Vector3) * 3);
    axis[2].x = cam->x - target->x;
    axis[2].y = cam->y - target->y;
    axis[2].z = cam->z - target->z;
    numerix_vec3_normalize(&axis[2]);

    numerix_cross_norm(up, &axis[2], &axis[0]);
    numerix_cross_norm(&axis[2], &axis[0], &axis[1]);

    Matrix4x4 *result = ALLOC(Matrix4x4);

    result->m11 = axis[0].x;
    result->m12 = axis[1].x;
    result->m13 = axis[2].x;
    result->m14 = 0.0f;
    result->m21 = axis[0].y;
    result->m22 = axis[1].y;
    result->m23 = axis[2].y;
    result->m24 = 0.0f;
    result->m31 = axis[0].z;
    result->m32 = axis[1].z;
    result->m33 = axis[2].z;
    result->m34 = 0.0f;
    result->m41 = -(numerix_vec3_dot(&axis[0], cam));
    result->m42 = -(numerix_vec3_dot(&axis[1], cam));
    result->m43 = -(numerix_vec3_dot(&axis[2], cam));
    result->m44 = 1.0f;

    xfree(axis);

    return NUMERIX_WRAP(klass, result);  
}

VALUE rb_matrix4x4_create_world(VALUE klass, VALUE position, VALUE forward, VALUE up) {
    Vector3 *pos, *f, *u;
    Data_Get_Struct(position, Vector3, pos);
    Data_Get_Struct(forward, Vector3, f);
    Data_Get_Struct(up, Vector3, u);

    Vector3 *axis = xmalloc(sizeof(Vector3) * 3);

    axis[2].x = -f->x;
    axis[2].y = -f->y;
    axis[2].z = -f->z;
    numerix_vec3_normalize(&axis[2]);
    numerix_cross_norm(u, &axis[2], &axis[0]);
    numerix_vec3_cross(&axis[2], &axis[0], &axis[1]);

    Matrix4x4 *result = ALLOC(Matrix4x4);

    result->m11 = axis[0].x;
    result->m12 = axis[0].y;
    result->m13 = axis[0].z;
    result->m14 = 0.0f;
    result->m21 = axis[1].x;
    result->m22 = axis[1].y;
    result->m23 = axis[1].z;
    result->m24 = 0.0f;
    result->m31 = axis[2].x;
    result->m32 = axis[2].y;
    result->m33 = axis[2].z;
    result->m34 = 0.0f;
    result->m41 = pos->x;
    result->m42 = pos->y;
    result->m43 = pos->z;
    result->m44 = 1.0f;

    xfree(axis);

    return NUMERIX_WRAP(klass, result); 
}

VALUE rb_matrix4x4_from_quaternion(VALUE klass, VALUE quaternion) {
    Quaternion *q;
    Data_Get_Struct(quaternion, Quaternion, q);

    float xx = q->x * q->x;
    float yy = q->y * q->y;
    float zz = q->z * q->z;

    float xy = q->x * q->y;
    float wz = q->z * q->w;
    float xz = q->z * q->x;
    float wy = q->y * q->w;
    float yz = q->y * q->z;
    float wx = q->x * q->w;

    Matrix4x4 *result = ALLOC(Matrix4x4);

    result->m11 = 1.0f - 2.0f * (yy + zz);
    result->m12 = 2.0f * (xy + wz);
    result->m13 = 2.0f * (xz - wy);
    result->m14 = 0.0f;
    result->m21 = 2.0f * (xy - wz);
    result->m22 = 1.0f - 2.0f * (zz + xx);
    result->m23 = 2.0f * (yz + wx);
    result->m24 = 0.0f;
    result->m31 = 2.0f * (xz + wy);
    result->m32 = 2.0f * (yz - wx);
    result->m33 = 1.0f - 2.0f * (yy + xx);
    result->m34 = 0.0f;
    result->m41 = 0.0f;
    result->m42 = 0.0f;
    result->m43 = 0.0f;
    result->m44 = 1.0f;

    return NUMERIX_WRAP(klass, result); 
}

VALUE rb_matrix4x4_from_yaw_pitch_roll(VALUE klass, VALUE yaw, VALUE pitch, VALUE roll) {
    VALUE q = rb_quaternion_from_yaw_pitch_roll(rb_cQuaternion, yaw, pitch, roll);
    return rb_matrix4x4_from_quaternion(klass, q);
}

VALUE rb_matrix4x4_create_shadow(VALUE klass, VALUE lightDir, VALUE plane) {
    Vector3 *light;
    Data_Get_Struct(lightDir, Vector3, light);

    VALUE normPlane = rb_plane_normalize(plane);
    Plane *p;
    Data_Get_Struct(normPlane, Plane, p);
    
    float dot = p->normal.x * light->x + p->normal.y * light->y + p->normal.z * light->z;
    float a = -p->normal.x;
    float b = -p->normal.y;
    float c = -p->normal.z;
    float d = -p->distance;

    Matrix4x4 *result = ALLOC(Matrix4x4);

    result->m11 = a * light->x + dot;
    result->m21 = b * light->x;
    result->m31 = c * light->x;
    result->m41 = d * light->x;

    result->m12 = a * light->y;
    result->m22 = b * light->y + dot;
    result->m32 = c * light->y;
    result->m42 = d * light->y;

    result->m13 = a * light->z;
    result->m23 = b * light->z;
    result->m33 = c * light->z + dot;
    result->m43 = d * light->z;

    result->m14 = 0.0f;
    result->m24 = 0.0f;
    result->m34 = 0.0f;
    result->m44 = dot;

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix4x4_create_reflection(VALUE klass, VALUE plane) {
    VALUE normPlane = rb_plane_normalize(plane);
    Plane *p;
    Data_Get_Struct(normPlane, Plane, p);

    float a = p->normal.x;
    float b = p->normal.y;
    float c = p->normal.z;

    float fa = -2.0f * a;
    float fb = -2.0f * b;
    float fc = -2.0f * c;

    Matrix4x4 *result = ALLOC(Matrix4x4);

    result->m11 = fa * a + 1.0f;
    result->m12 = fb * a;
    result->m13 = fc * a;
    result->m14 = 0.0f;

    result->m21 = fa * b;
    result->m22 = fb * b + 1.0f;
    result->m23 = fc * b;
    result->m24 = 0.0f;

    result->m31 = fa * c;
    result->m32 = fb * c;
    result->m33 = fc * c + 1.0f;
    result->m34 = 0.0f;

    result->m41 = fa * p->distance;
    result->m42 = fb * p->distance;
    result->m43 = fc * p->distance;
    result->m44 = 1.0f;

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix4x4_transform(VALUE self, VALUE quaternion) {
    Matrix4x4 *m, *result;
    Quaternion *rotation;
    Data_Get_Struct(self, Matrix4x4, m);
    Data_Get_Struct(quaternion, Quaternion, rotation);

    // Compute rotation matrix.
    float x2 = rotation->x + rotation->x;
    float y2 = rotation->y + rotation->y;
    float z2 = rotation->z + rotation->z;

    float wx2 = rotation->w * x2;
    float wy2 = rotation->w * y2;
    float wz2 = rotation->w * z2;
    float xx2 = rotation->x * x2;
    float xy2 = rotation->x * y2;
    float xz2 = rotation->x * z2;
    float yy2 = rotation->y * y2;
    float yz2 = rotation->y * z2;
    float zz2 = rotation->z * z2;

    float q11 = 1.0f - yy2 - zz2;
    float q21 = xy2 - wz2;
    float q31 = xz2 + wy2;

    float q12 = xy2 + wz2;
    float q22 = 1.0f - xx2 - zz2;
    float q32 = yz2 - wx2;

    float q13 = xz2 - wy2;
    float q23 = yz2 + wx2;
    float q33 = 1.0f - xx2 - yy2;

    result = ALLOC(Matrix4x4);

    // First row
    result->m11 = m->m11 * q11 + m->m12 * q21 + m->m13 * q31;
    result->m12 = m->m11 * q12 + m->m12 * q22 + m->m13 * q32;
    result->m13 = m->m11 * q13 + m->m12 * q23 + m->m13 * q33;
    result->m14 = m->m14;

    // Second row
    result->m21 = m->m21 * q11 + m->m22 * q21 + m->m23 * q31;
    result->m22 = m->m21 * q12 + m->m22 * q22 + m->m23 * q32;
    result->m23 = m->m21 * q13 + m->m22 * q23 + m->m23 * q33;
    result->m24 = m->m24;

    // Third row
    result->m31 = m->m31 * q11 + m->m32 * q21 + m->m33 * q31;
    result->m32 = m->m31 * q12 + m->m32 * q22 + m->m33 * q32;
    result->m33 = m->m31 * q13 + m->m32 * q23 + m->m33 * q33;
    result->m34 = m->m34;

    // Fourth row
    result->m41 = m->m41 * q11 + m->m42 * q21 + m->m43 * q31;
    result->m42 = m->m41 * q12 + m->m42 * q22 + m->m43 * q32;
    result->m43 = m->m41 * q13 + m->m42 * q23 + m->m43 * q33;
    result->m44 = m->m44;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_matrix4x4_transpose(VALUE self) {
    MATRIX4X4();
    Matrix4x4 *result = ALLOC(Matrix4x4);

    result->m11 = m->m11;
    result->m12 = m->m21;
    result->m13 = m->m31;
    result->m14 = m->m41;
    result->m21 = m->m12;
    result->m22 = m->m22;
    result->m23 = m->m32;
    result->m24 = m->m42;
    result->m31 = m->m13;
    result->m32 = m->m23;
    result->m33 = m->m33;
    result->m34 = m->m43;
    result->m41 = m->m14;
    result->m42 = m->m24;
    result->m43 = m->m34;
    result->m44 = m->m44;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_matrix4x4_lerp_s(VALUE klass, VALUE matrix1, VALUE matrix2, VALUE amount) {
    Matrix4x4 *m1, *m2, *result;
    Data_Get_Struct(matrix1, Matrix4x4, m1);
    Data_Get_Struct(matrix2, Matrix4x4, m2);
    result = ALLOC(Matrix4x4);
    float weight = NUMERIX_CLAMP(NUM2FLT(amount), 0.0f, 1.0f);

    // First row
    result->m11 = m1->m11 + (m2->m11 - m1->m11) * weight;
    result->m12 = m1->m12 + (m2->m12 - m1->m12) * weight;
    result->m13 = m1->m13 + (m2->m13 - m1->m13) * weight;
    result->m14 = m1->m14 + (m2->m14 - m1->m14) * weight;

    // Second row
    result->m21 = m1->m21 + (m2->m21 - m1->m21) * weight;
    result->m22 = m1->m22 + (m2->m22 - m1->m22) * weight;
    result->m23 = m1->m23 + (m2->m23 - m1->m23) * weight;
    result->m24 = m1->m24 + (m2->m24 - m1->m24) * weight;

    // Third row
    result->m31 = m1->m31 + (m2->m31 - m1->m31) * weight;
    result->m32 = m1->m32 + (m2->m32 - m1->m32) * weight;
    result->m33 = m1->m33 + (m2->m33 - m1->m33) * weight;
    result->m34 = m1->m34 + (m2->m34 - m1->m34) * weight;

    // Fourth row
    result->m41 = m1->m41 + (m2->m41 - m1->m41) * weight;
    result->m42 = m1->m42 + (m2->m42 - m1->m42) * weight;
    result->m43 = m1->m43 + (m2->m43 - m1->m43) * weight;
    result->m44 = m1->m44 + (m2->m44 - m1->m44) * weight;

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix4x4_negate(VALUE self) {
    MATRIX4X4();
    Matrix4x4 *result = ALLOC(Matrix4x4);

    result->m11 = -m->m11;
    result->m12 = -m->m12;
    result->m13 = -m->m13;
    result->m14 = -m->m14;
    result->m21 = -m->m21;
    result->m22 = -m->m22;
    result->m23 = -m->m23;
    result->m24 = -m->m24;
    result->m31 = -m->m31;
    result->m32 = -m->m32;
    result->m33 = -m->m33;
    result->m34 = -m->m34;
    result->m41 = -m->m41;
    result->m42 = -m->m42;
    result->m43 = -m->m43;
    result->m44 = -m->m44;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_matrix4x4_add(VALUE self, VALUE other) {
    Matrix4x4 *m1, *m2, *result;
    Data_Get_Struct(self, Matrix4x4, m1);
    Data_Get_Struct(other, Matrix4x4, m2);
    result = ALLOC(Matrix4x4);

    result->m11 = m1->m11 + m2->m11;
    result->m12 = m1->m12 + m2->m12;
    result->m13 = m1->m13 + m2->m13;
    result->m14 = m1->m14 + m2->m14;
    result->m21 = m1->m21 + m2->m21;
    result->m22 = m1->m22 + m2->m22;
    result->m23 = m1->m23 + m2->m23;
    result->m24 = m1->m24 + m2->m24;
    result->m31 = m1->m31 + m2->m31;
    result->m32 = m1->m32 + m2->m32;
    result->m33 = m1->m33 + m2->m33;
    result->m34 = m1->m34 + m2->m34;
    result->m41 = m1->m41 + m2->m41;
    result->m42 = m1->m42 + m2->m42;
    result->m43 = m1->m43 + m2->m43;
    result->m44 = m1->m44 + m2->m44;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_matrix4x4_subtract(VALUE self, VALUE other) {
    Matrix4x4 *m1, *m2, *result;
    Data_Get_Struct(self, Matrix4x4, m1);
    Data_Get_Struct(other, Matrix4x4, m2);
    result = ALLOC(Matrix4x4);

    result->m11 = m1->m11 - m2->m11;
    result->m12 = m1->m12 - m2->m12;
    result->m13 = m1->m13 - m2->m13;
    result->m14 = m1->m14 - m2->m14;
    result->m21 = m1->m21 - m2->m21;
    result->m22 = m1->m22 - m2->m22;
    result->m23 = m1->m23 - m2->m23;
    result->m24 = m1->m24 - m2->m24;
    result->m31 = m1->m31 - m2->m31;
    result->m32 = m1->m32 - m2->m32;
    result->m33 = m1->m33 - m2->m33;
    result->m34 = m1->m34 - m2->m34;
    result->m41 = m1->m41 - m2->m41;
    result->m42 = m1->m42 - m2->m42;
    result->m43 = m1->m43 - m2->m43;
    result->m44 = m1->m44 - m2->m44;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_matrix4x4_multiply(VALUE self, VALUE other) {
    Matrix4x4 *m1, *result;
    Data_Get_Struct(self, Matrix4x4, m1);
    result = ALLOC(Matrix4x4);

    if (NUMERIX_TYPE_P(other, rb_cMatrix4x4))
    {
        Matrix4x4 *m2;
        Data_Get_Struct(other, Matrix4x4, m2);

        // First row
        result->m11 = m1->m11 * m2->m11 + m1->m12 * m2->m21 + m1->m13 * m2->m31 + m1->m14 * m2->m41;
        result->m12 = m1->m11 * m2->m12 + m1->m12 * m2->m22 + m1->m13 * m2->m32 + m1->m14 * m2->m42;
        result->m13 = m1->m11 * m2->m13 + m1->m12 * m2->m23 + m1->m13 * m2->m33 + m1->m14 * m2->m43;
        result->m14 = m1->m11 * m2->m14 + m1->m12 * m2->m24 + m1->m13 * m2->m34 + m1->m14 * m2->m44;

        // Second row
        result->m21 = m1->m21 * m2->m11 + m1->m22 * m2->m21 + m1->m23 * m2->m31 + m1->m24 * m2->m41;
        result->m22 = m1->m21 * m2->m12 + m1->m22 * m2->m22 + m1->m23 * m2->m32 + m1->m24 * m2->m42;
        result->m23 = m1->m21 * m2->m13 + m1->m22 * m2->m23 + m1->m23 * m2->m33 + m1->m24 * m2->m43;
        result->m24 = m1->m21 * m2->m14 + m1->m22 * m2->m24 + m1->m23 * m2->m34 + m1->m24 * m2->m44;

        // Third row
        result->m31 = m1->m31 * m2->m11 + m1->m32 * m2->m21 + m1->m33 * m2->m31 + m1->m34 * m2->m41;
        result->m32 = m1->m31 * m2->m12 + m1->m32 * m2->m22 + m1->m33 * m2->m32 + m1->m34 * m2->m42;
        result->m33 = m1->m31 * m2->m13 + m1->m32 * m2->m23 + m1->m33 * m2->m33 + m1->m34 * m2->m43;
        result->m34 = m1->m31 * m2->m14 + m1->m32 * m2->m24 + m1->m33 * m2->m34 + m1->m34 * m2->m44;

        // Fourth row
        result->m41 = m1->m41 * m2->m11 + m1->m42 * m2->m21 + m1->m43 * m2->m31 + m1->m44 * m2->m41;
        result->m42 = m1->m41 * m2->m12 + m1->m42 * m2->m22 + m1->m43 * m2->m32 + m1->m44 * m2->m42;
        result->m43 = m1->m41 * m2->m13 + m1->m42 * m2->m23 + m1->m43 * m2->m33 + m1->m44 * m2->m43;
        result->m44 = m1->m41 * m2->m14 + m1->m42 * m2->m24 + m1->m43 * m2->m34 + m1->m44 * m2->m44;
    }
    else
    {
        float scalar = NUM2FLT(other);
        result->m11 = m1->m11 * scalar;
        result->m12 = m1->m12 * scalar;
        result->m13 = m1->m13 * scalar;
        result->m14 = m1->m14 * scalar;
        result->m21 = m1->m21 * scalar;
        result->m22 = m1->m22 * scalar;
        result->m23 = m1->m23 * scalar;
        result->m24 = m1->m24 * scalar;
        result->m31 = m1->m31 * scalar;
        result->m32 = m1->m32 * scalar;
        result->m33 = m1->m33 * scalar;
        result->m34 = m1->m34 * scalar;
        result->m41 = m1->m41 * scalar;
        result->m42 = m1->m42 * scalar;
        result->m43 = m1->m43 * scalar;
        result->m44 = m1->m44 * scalar;
    }

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_matrix4x4_invert(VALUE self) {
    Matrix4x4 *mat, *result;
    Data_Get_Struct(self, Matrix4x4, mat);
    result = ALLOC(Matrix4x4);
    //                                       -1
    // If you have matrix M, inverse Matrix M   can compute
    //
    //     -1       1      
    //    M   = --------- A
    //            det(M)
    //
    // A is adjugate (adjoint) of M, where,
    //
    //      T
    // A = C
    //
    // C is Cofactor matrix of M, where,
    //           i + j
    // C   = (-1)      * det(M  )
    //  ij                    ij
    //
    //     [ a b c d ]
    // M = [ e f g h ]
    //     [ i j k l ]
    //     [ m n o p ]
    //
    // First Row
    //           2 | f g h |
    // C   = (-1)  | j k l | = + ( f ( kp - lo ) - g ( jp - ln ) + h ( jo - kn ) )
    //  11         | n o p |
    //
    //           3 | e g h |
    // C   = (-1)  | i k l | = - ( e ( kp - lo ) - g ( ip - lm ) + h ( io - km ) )
    //  12         | m o p |
    //
    //           4 | e f h |
    // C   = (-1)  | i j l | = + ( e ( jp - ln ) - f ( ip - lm ) + h ( in - jm ) )
    //  13         | m n p |
    //
    //           5 | e f g |
    // C   = (-1)  | i j k | = - ( e ( jo - kn ) - f ( io - km ) + g ( in - jm ) )
    //  14         | m n o |
    //
    // Second Row
    //           3 | b c d |
    // C   = (-1)  | j k l | = - ( b ( kp - lo ) - c ( jp - ln ) + d ( jo - kn ) )
    //  21         | n o p |
    //
    //           4 | a c d |
    // C   = (-1)  | i k l | = + ( a ( kp - lo ) - c ( ip - lm ) + d ( io - km ) )
    //  22         | m o p |
    //
    //           5 | a b d |
    // C   = (-1)  | i j l | = - ( a ( jp - ln ) - b ( ip - lm ) + d ( in - jm ) )
    //  23         | m n p |
    //
    //           6 | a b c |
    // C   = (-1)  | i j k | = + ( a ( jo - kn ) - b ( io - km ) + c ( in - jm ) )
    //  24         | m n o |
    //
    // Third Row
    //           4 | b c d |
    // C   = (-1)  | f g h | = + ( b ( gp - ho ) - c ( fp - hn ) + d ( fo - gn ) )
    //  31         | n o p |
    //
    //           5 | a c d |
    // C   = (-1)  | e g h | = - ( a ( gp - ho ) - c ( ep - hm ) + d ( eo - gm ) )
    //  32         | m o p |
    //
    //           6 | a b d |
    // C   = (-1)  | e f h | = + ( a ( fp - hn ) - b ( ep - hm ) + d ( en - fm ) )
    //  33         | m n p |
    //
    //           7 | a b c |
    // C   = (-1)  | e f g | = - ( a ( fo - gn ) - b ( eo - gm ) + c ( en - fm ) )
    //  34         | m n o |
    //
    // Fourth Row
    //           5 | b c d |
    // C   = (-1)  | f g h | = - ( b ( gl - hk ) - c ( fl - hj ) + d ( fk - gj ) )
    //  41         | j k l |
    //
    //           6 | a c d |
    // C   = (-1)  | e g h | = + ( a ( gl - hk ) - c ( el - hi ) + d ( ek - gi ) )
    //  42         | i k l |
    //
    //           7 | a b d |
    // C   = (-1)  | e f h | = - ( a ( fl - hj ) - b ( el - hi ) + d ( ej - fi ) )
    //  43         | i j l |
    //
    //           8 | a b c |
    // C   = (-1)  | e f g | = + ( a ( fk - gj ) - b ( ek - gi ) + c ( ej - fi ) )
    //  44         | i j k |
    //
    // Cost of operation
    // 53 adds, 104 muls, and 1 div.
    float a = mat->m11, b = mat->m12, c = mat->m13, d = mat->m14;
    float e = mat->m21, f = mat->m22, g = mat->m23, h = mat->m24;
    float i = mat->m31, j = mat->m32, k = mat->m33, l = mat->m34;
    float m = mat->m41, n = mat->m42, o = mat->m43, p = mat->m44;

    float kp_lo = k * p - l * o;
    float jp_ln = j * p - l * n;
    float jo_kn = j * o - k * n;
    float ip_lm = i * p - l * m;
    float io_km = i * o - k * m;
    float in_jm = i * n - j * m;

    float a11 = +(f * kp_lo - g * jp_ln + h * jo_kn);
    float a12 = -(e * kp_lo - g * ip_lm + h * io_km);
    float a13 = +(e * jp_ln - f * ip_lm + h * in_jm);
    float a14 = -(e * jo_kn - f * io_km + g * in_jm);

    float det = a * a11 + b * a12 + c * a13 + d * a14;

    if (fabsf(det) < FLT_EPSILON)
    {
        // invalid
        float *matp = (float*) mat;
        for (int i = 0; i < 16; i++)
            matp[i] = NAN;
    }
    else
    {
        float invDet = 1.0f / det;

        result->m11 = a11 * invDet;
        result->m21 = a12 * invDet;
        result->m31 = a13 * invDet;
        result->m41 = a14 * invDet;

        result->m12 = -(b * kp_lo - c * jp_ln + d * jo_kn) * invDet;
        result->m22 = +(a * kp_lo - c * ip_lm + d * io_km) * invDet;
        result->m32 = -(a * jp_ln - b * ip_lm + d * in_jm) * invDet;
        result->m42 = +(a * jo_kn - b * io_km + c * in_jm) * invDet;

        float gp_ho = g * p - h * o;
        float fp_hn = f * p - h * n;
        float fo_gn = f * o - g * n;
        float ep_hm = e * p - h * m;
        float eo_gm = e * o - g * m;
        float en_fm = e * n - f * m;

        result->m13 = +(b * gp_ho - c * fp_hn + d * fo_gn) * invDet;
        result->m23 = -(a * gp_ho - c * ep_hm + d * eo_gm) * invDet;
        result->m33 = +(a * fp_hn - b * ep_hm + d * en_fm) * invDet;
        result->m43 = -(a * fo_gn - b * eo_gm + c * en_fm) * invDet;

        float gl_hk = g * l - h * k;
        float fl_hj = f * l - h * j;
        float fk_gj = f * k - g * j;
        float el_hi = e * l - h * i;
        float ek_gi = e * k - g * i;
        float ej_fi = e * j - f * i;

        result->m14 = -(b * gl_hk - c * fl_hj + d * fk_gj) * invDet;
        result->m24 = +(a * gl_hk - c * el_hi + d * ek_gi) * invDet;
        result->m34 = -(a * fl_hj - b * el_hi + d * ej_fi) * invDet;
        result->m44 = +(a * fk_gj - b * ek_gi + c * ej_fi) * invDet;
    }

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_matrix4x4_invert_bang(VALUE self) {
    Matrix4x4 *mat;
    Data_Get_Struct(self, Matrix4x4, mat);

    float a = mat->m11, b = mat->m12, c = mat->m13, d = mat->m14;
    float e = mat->m21, f = mat->m22, g = mat->m23, h = mat->m24;
    float i = mat->m31, j = mat->m32, k = mat->m33, l = mat->m34;
    float m = mat->m41, n = mat->m42, o = mat->m43, p = mat->m44;

    float kp_lo = k * p - l * o;
    float jp_ln = j * p - l * n;
    float jo_kn = j * o - k * n;
    float ip_lm = i * p - l * m;
    float io_km = i * o - k * m;
    float in_jm = i * n - j * m;

    float a11 = +(f * kp_lo - g * jp_ln + h * jo_kn);
    float a12 = -(e * kp_lo - g * ip_lm + h * io_km);
    float a13 = +(e * jp_ln - f * ip_lm + h * in_jm);
    float a14 = -(e * jo_kn - f * io_km + g * in_jm);

    float det = a * a11 + b * a12 + c * a13 + d * a14;

    if (fabsf(det) < FLT_EPSILON)
    {
        // invalid
        float *matp = (float*) mat;
        for (int i = 0; i < 16; i++)
            matp[i] = NAN;
    }
    else
    {
        float invDet = 1.0f / det;

        mat->m11 = a11 * invDet;
        mat->m21 = a12 * invDet;
        mat->m31 = a13 * invDet;
        mat->m41 = a14 * invDet;

        mat->m12 = -(b * kp_lo - c * jp_ln + d * jo_kn) * invDet;
        mat->m22 = +(a * kp_lo - c * ip_lm + d * io_km) * invDet;
        mat->m32 = -(a * jp_ln - b * ip_lm + d * in_jm) * invDet;
        mat->m42 = +(a * jo_kn - b * io_km + c * in_jm) * invDet;

        float gp_ho = g * p - h * o;
        float fp_hn = f * p - h * n;
        float fo_gn = f * o - g * n;
        float ep_hm = e * p - h * m;
        float eo_gm = e * o - g * m;
        float en_fm = e * n - f * m;

        mat->m13 = +(b * gp_ho - c * fp_hn + d * fo_gn) * invDet;
        mat->m23 = -(a * gp_ho - c * ep_hm + d * eo_gm) * invDet;
        mat->m33 = +(a * fp_hn - b * ep_hm + d * en_fm) * invDet;
        mat->m43 = -(a * fo_gn - b * eo_gm + c * en_fm) * invDet;

        float gl_hk = g * l - h * k;
        float fl_hj = f * l - h * j;
        float fk_gj = f * k - g * j;
        float el_hi = e * l - h * i;
        float ek_gi = e * k - g * i;
        float ej_fi = e * j - f * i;

        mat->m14 = -(b * gl_hk - c * fl_hj + d * fk_gj) * invDet;
        mat->m24 = +(a * gl_hk - c * el_hi + d * ek_gi) * invDet;
        mat->m34 = -(a * fl_hj - b * el_hi + d * ej_fi) * invDet;
        mat->m44 = +(a * fk_gj - b * ek_gi + c * ej_fi) * invDet;
    }

    return self;
}
