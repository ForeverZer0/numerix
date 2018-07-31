
#include "matrix4x4.h"


void Init_matrix4x4(VALUE outer) {
    
}

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

    return NUMERIX_WRAP(klass, mat);
}
