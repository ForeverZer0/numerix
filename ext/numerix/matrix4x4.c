
#include "matrix4x4.h"


void Init_matrix4x4(VALUE outer) {
    
    rb_define_alloc_func(rb_cMatrix4x4, rb_matrix4x4_allocate);
    rb_define_method(rb_cMatrix4x4, "initialize", rb_matrix4x4_initialize, -1);
    // Instance
    rb_define_method(rb_cMatrix4x4, "identity?", rb_matrix4x4_identity_p, 0);
    rb_define_method(rb_cMatrix4x4, "translation", rb_matrix4x4_translation, 0);
    rb_define_method(rb_cMatrix4x4, "translation=", rb_matrix4x4_translation_set, 1);

    // Class
    rb_define_singleton_method(rb_cMatrix4x4, "identity", rb_matrix4x4_identity, 0);
    rb_define_singleton_method(rb_cMatrix4x4, "create_billboard", rb_matrix4x4_create_billboard, 4);
    rb_define_singleton_method(rb_cMatrix4x4, "create_constrained_billboard", rb_matrix4x4_create_constrained_billboard, 5);
    rb_define_singleton_method(rb_cMatrix4x4, "create_translation", rb_matrix4x4_create_translation, -1);
    rb_define_singleton_method(rb_cMatrix4x4, "create_scale", rb_matrix4x4_create_scale, -1);
    rb_define_singleton_method(rb_cMatrix4x4, "create_rotation_x", rb_matrix4x4_create_rotation_x, -1);
    rb_define_singleton_method(rb_cMatrix4x4, "create_rotation_y", rb_matrix4x4_create_rotation_y, -1);
    rb_define_singleton_method(rb_cMatrix4x4, "create_rotation_z", rb_matrix4x4_create_rotation_z, -1);
    rb_define_singleton_method(rb_cMatrix4x4, "from_axis_angle", rb_matrix4x4_from_axis_angle, 2);




}

#ifdef HEADER

void Init_matrix4x4(VALUE outer);
static VALUE rb_matrix4x4_allocate(VALUE klass);
VALUE rb_matrix_initialize(int argc, VALUE *argv, VALUE self);

// Instance
VALUE rb_matrix4x4_identity_p(VALUE self);
VALUE rb_matrix4x4_translation(VALUE self);
VALUE rb_matrix4x4_translation_set(VALUE self, VALUE value);

// Class
VALUE rb_matrix4x4_identity(VALUE klass);
VALUE rb_matrix4x4_create_billboard(VALUE klass, VALUE position, VALUE camera, VALUE up, VALUE forward);
VALUE rb_matrix4x4_create_constrained_billboard(VALUE klass, VALUE position, VALUE rotate, VALUE camera, VALUE up, VALUE forward);
VALUE rb_matrix4x4_invert_s(VALUE klass, VALUE matrix);
VALUE rb_matrix4x4_create_translation(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_create_scale(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_create_rotation_x(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_create_rotation_y(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_create_rotation_z(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_from_axis_angle(VALUE klass, VALUE axis, VALUE angle);

// Internal
static inline void numerix_vec3_normalize(Vector3 *v);
static inline void numerix_vec3_cross(Vector3 *v1, Vector3 *v2, Vector3 **result);
static inline float numerix_vec3_dot(Vector3 *v1, Vector3 *v2);
#endif

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
        rb_raise(rb_eArgError, "wrong number of arguments (%d for 0, 16)", argc);

    return Qnil;
}

VALUE rb_matrix4x4_identity_p(VALUE self) {
    MATRIX4X4();
    // Check diagonal element first for early out.
    return m->m11 == 1.0f && m->m22 == 1.0f && m->m33 == 1.0f && m->m44 == 1.0f && 
           m->m12 == 0.0f && m->m13 == 0.0f && m->m14 == 0.0f && m->m21 == 0.0f && 
           m->m23 == 0.0f && m->m24 == 0.0f && m->m31 == 0.0f && m->m32 == 0.0f && 
           m->m34 == 0.0f && m->m41 == 0.0f && m->m42 == 0.0f && m->m43 == 0.0f ? Qtrue : Qfalse;
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

VALUE rb_matrix4x4_create_billboard(VALUE klass, VALUE position, VALUE camera, VALUE up, VALUE forward) {
    const float epsilon = 1e-4f;
    Vector3 *pos, *cam, *u, *f;
    Data_Get_Struct(position, Vector3, pos);
    Data_Get_Struct(cam, Vector3, camera);
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

    numerix_vec3_cross(u, &axis[2], &axis[0]);
    numerix_vec3_normalize(&axis[0]);
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
    Data_Get_Struct(cam, Vector3, camera);
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

    if (absf(dot) > minAngle)
    {
        memcpy(&axis[2], f, sizeof(Vector2));
        // Make sure passed values are useful for compute.
        dot = numerix_vec3_dot(r, &axis[2]);

        if (absf(dot) > minAngle)
        {
            axis[2].y = 0.0f;
            if (absf(r->z) > minAngle)
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
        numerix_vec3_cross(r, &axis[2], &axis[0]);
        numerix_vec3_normalize(&axis[0]);

        numerix_vec3_cross(&axis[0], r, &axis[2]);
        numerix_vec3_normalize(&axis[2]);
    }
    else
    {
        numerix_vec3_cross(r, faceDir, &axis[0]);
        numerix_vec3_normalize(&axis[0]);
        numerix_vec3_cross(&axis[0], &axis[1], &axis[2]);
        numerix_vec3_normalize(&axis[2]);
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

VALUE rb_matrix4x4_create_translation(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_create_scale(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_create_rotation_x(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_create_rotation_y(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_create_rotation_z(int argc, VALUE *argv, VALUE klass);
VALUE rb_matrix4x4_from_axis_angle(VALUE klass, VALUE axis, VALUE angle);













/*
rb_matrix4x4_

        m->m11 = 
        m->m12 = 
        m->m13 = 
        m->m14 = 
        m->m21 = 
        m->m22 = 
        m->m23 = 
        m->m24 = 
        m->m31 = 
        m->m32 = 
        m->m33 = 
        m->m34 = 
        m->m41 = 
        m->m42 = 
        m->m43 = 
        m->m44 = 



VALUE rb_matrix4x4_invert_s(VALUE klass, VALUE matrix) {
    Matrix4x4 *mat, *result;
    Data_Get_Struct(matrix, Matrix4x4, mat);
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
        float invDet = 1.0.0f / det;

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

    return NUMERIX_WRAP(klass, mat);
}

*/
