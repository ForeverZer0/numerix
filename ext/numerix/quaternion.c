
#include "quaternion.h"

void Init_quaternion(VALUE outer) {
    rb_define_alloc_func(rb_cQuaternion, rb_quaternion_alloc);
    rb_define_method(rb_cQuaternion, "initialize", rb_quaternion_initialize, -1);

    // Instance
    rb_define_method(rb_cQuaternion, "identity?", rb_quaternion_identity_p, 0);
    rb_define_method(rb_cQuaternion, "length", rb_quaternion_length, 0);
    rb_define_method(rb_cQuaternion, "length_squared", rb_quaternion_length_squared, 0);
    rb_define_method(rb_cQuaternion, "normalize", rb_quaternion_normalize, 0);
    rb_define_method(rb_cQuaternion, "normalize!", rb_quaternion_normalize_bang, 0);
    rb_define_method(rb_cQuaternion, "conjugate", rb_quaternion_conjugate, 0);
    rb_define_method(rb_cQuaternion, "conjugate!", rb_quaternion_conjugate_bang, 0);
    rb_define_method(rb_cQuaternion, "inverse", rb_quaternion_inverse, 0);
    rb_define_method(rb_cQuaternion, "dot", rb_quaternion_dot, 1);
    rb_define_method(rb_cQuaternion, "concatenate", rb_quaternion_concatenate, 1);
    rb_define_method(rb_cQuaternion, "concatenate!", rb_quaternion_concatenate_bang, 1);
    rb_define_method(rb_cQuaternion, "lerp", rb_quaternion_lerp, 2);
    rb_define_method(rb_cQuaternion, "lerp!", rb_quaternion_lerp_bang, 2);
    rb_define_method(rb_cQuaternion, "slerp", rb_quaternion_slerp, 2);
    rb_define_method(rb_cQuaternion, "slerp!", rb_quaternion_slerp_bang, 2);

    // Conversion
    rb_define_method(rb_cQuaternion, "to_s", rb_quaternion_to_s, 0);
    rb_define_method(rb_cQuaternion, "to_a", rb_quaternion_to_a, 0);
    rb_define_method(rb_cQuaternion, "to_h", rb_quaternion_to_h, 0);
    rb_define_method(rb_cQuaternion, "to_vec4", rb_quaternion_to_vec4, 0);

    // Operators
    rb_define_method(rb_cQuaternion, "-@", rb_quaternion_negate, 0);
    rb_define_method(rb_cQuaternion, "+", rb_quaternion_add, 1);
    rb_define_method(rb_cQuaternion, "-", rb_quaternion_subtract, 1);
    rb_define_method(rb_cQuaternion, "*", rb_quaternion_multiply, 1);
    rb_define_method(rb_cQuaternion, "/", rb_quaternion_divide, 1);
    rb_define_method(rb_cQuaternion, "==", rb_quaternion_equal, 1);

    // Class
    rb_define_singleton_method(rb_cQuaternion, "identity", rb_quaternion_identity, 0);
    rb_define_singleton_method(rb_cQuaternion, "from_axis_angle", rb_quaternion_from_axis_angle, 2);
    rb_define_singleton_method(rb_cQuaternion, "from_yaw_pitch_roll", rb_quaternion_from_yaw_pitch_roll, 3);
    rb_define_singleton_method(rb_cQuaternion, "from_rotation_matrix", rb_quaternion_from_rotation_matrix, 1);
    rb_define_singleton_method(rb_cQuaternion, "slerp", rb_quaternion_slerp_s, 3);
    rb_define_singleton_method(rb_cQuaternion, "lerp", rb_quaternion_lerp_s, 3);
}

VALUE rb_quaternion_alloc(VALUE klass) {
    Quaternion *q = ALLOC(Quaternion);
    memset(q, 0, sizeof(Quaternion));
    return NUMERIX_WRAP(klass, q);
}

VALUE rb_quaternion_initialize(int argc, VALUE *argv, VALUE self) {
    QUATERNION();
    switch (argc) {
        case 0:
            break;
        case 2: {
            Vector3 *v;
            Data_Get_Struct(argv[0], Vector3, v);
            q->x = v->x;
            q->y = v->y;
            q->z = v->z;
            q->w = NUM2FLT(argv[1]);
            break;
        }
        case 4: {
            q->x = NUM2FLT(argv[0]);
            q->y = NUM2FLT(argv[1]);
            q->z = NUM2FLT(argv[2]);
            q->w = NUM2FLT(argv[3]);
            break;
        }
        default:
            rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 0, 2, 4)", argc);
            break;
    }
    return Qnil;
}

VALUE rb_quaternion_identity_p(VALUE self) {
    QUATERNION();
    return q->x == 0.0f && q->y == 0.0f && q->z == 0.0f && q->w == 1.0f ? Qtrue : Qfalse;
}

VALUE rb_quaternion_length(VALUE self) {
    QUATERNION();
    return DBL2NUM(sqrtf(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w));
}

VALUE rb_quaternion_length_squared(VALUE self) {
    QUATERNION();
    return DBL2NUM(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
}

VALUE rb_quaternion_negate(VALUE self) {
    QUATERNION();
    Quaternion *result = ALLOC(Quaternion);

    result->x = -q->x;
    result->y = -q->y;
    result->z = -q->z;
    result->w = -q->w;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_quaternion_add(VALUE self, VALUE other) {
    Quaternion *q1, *q2, *result;
    Data_Get_Struct(self, Quaternion, q1);
    Data_Get_Struct(other, Quaternion, q2);
    result = ALLOC(Quaternion);

    result->x = q1->x + q2->x;
    result->y = q1->y + q2->y;
    result->z = q1->z + q2->z;
    result->w = q1->w + q2->w;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_quaternion_subtract(VALUE self, VALUE other) {
    Quaternion *q1, *q2, *result;
    Data_Get_Struct(self, Quaternion, q1);
    Data_Get_Struct(other, Quaternion, q2);
    result = ALLOC(Quaternion);

    result->x = q1->x - q2->x;
    result->y = q1->y - q2->y;
    result->z = q1->z - q2->z;
    result->w = q1->w - q2->w;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_quaternion_multiply(VALUE self, VALUE other) {
    Quaternion *q1, *result;
    Data_Get_Struct(self, Quaternion, q1);
    result = ALLOC(Quaternion);

    if (NUMERIX_TYPE_P(other, rb_cQuaternion)) {
        Quaternion *q2;
        Data_Get_Struct(other, Quaternion, q2);

        float q1x = q1->x;
        float q1y = q1->y;
        float q1z = q1->z;
        float q1w = q1->w;

        float q2x = q2->x;
        float q2y = q2->y;
        float q2z = q2->z;
        float q2w = q2->w;

        // cross(av, bv)
        float cx = q1y * q2z - q1z * q2y;
        float cy = q1z * q2x - q1x * q2z;
        float cz = q1x * q2y - q1y * q2x;

        float dot = q1x * q2x + q1y * q2y + q1z * q2z;

        result->x = q1x * q2w + q2x * q1w + cx;
        result->y = q1y * q2w + q2y * q1w + cy;
        result->z = q1z * q2w + q2z * q1w + cz;
        result->w = q1w * q2w - dot;
    } else {
        float scalar = NUM2FLT(other);
        result->x = q1->x * scalar;
        result->y = q1->y * scalar;
        result->z = q1->z * scalar;
        result->w = q1->w * scalar;
    }

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_quaternion_divide(VALUE self, VALUE other) {
    Quaternion *q1, *q2, *result;
    Data_Get_Struct(self, Quaternion, q1);
    Data_Get_Struct(other, Quaternion, q2);
    result = ALLOC(Quaternion);

    float q1x = q1->x;
    float q1y = q1->y;
    float q1z = q1->z;
    float q1w = q1->w;

    //-------------------------------------
    // Inverse part.
    float ls = q2->x * q2->x + q2->y * q2->y + q2->z * q2->z + q2->w * q2->w;
    float invNorm = 1.0f / ls;

    float q2x = -q2->x * invNorm;
    float q2y = -q2->y * invNorm;
    float q2z = -q2->z * invNorm;
    float q2w = q2->w * invNorm;

    //-------------------------------------
    // Multiply part.

    // cross(av, bv)
    float cx = q1y * q2z - q1z * q2y;
    float cy = q1z * q2x - q1x * q2z;
    float cz = q1x * q2y - q1y * q2x;

    float dot = q1x * q2x + q1y * q2y + q1z * q2z;

    result->x = q1x * q2w + q2x * q1w + cx;
    result->y = q1y * q2w + q2y * q1w + cy;
    result->z = q1z * q2w + q2z * q1w + cz;
    result->w = q1w * q2w - dot;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_quaternion_equal(VALUE self, VALUE other) {
    if (CLASS_OF(other) != CLASS_OF(self))
        return Qfalse;
    Quaternion *q1, *q2;
    Data_Get_Struct(self, Quaternion, q1);
    Data_Get_Struct(other, Quaternion, q2);
    return FLT_EQUAL(q1->x, q2->x) && FLT_EQUAL(q1->y, q2->y) && FLT_EQUAL(q1->z, q2->z) && FLT_EQUAL(q1->w, q2->w) ? Qtrue : Qfalse;
}

VALUE rb_quaternion_to_s(VALUE self) {
    QUATERNION();
    return rb_sprintf("{%f, %f, %f, %f}", q->x, q->y, q->z, q->w);
}

VALUE rb_quaternion_to_a(VALUE self) {
    QUATERNION();
    VALUE ary = rb_ary_new_capa(4);
    rb_ary_store(ary, 0, DBL2NUM(q->x));
    rb_ary_store(ary, 1, DBL2NUM(q->y));
    rb_ary_store(ary, 2, DBL2NUM(q->z));
    rb_ary_store(ary, 3, DBL2NUM(q->w));
    return ary;
}

VALUE rb_quaternion_to_h(VALUE self) {
    QUATERNION();
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, ID2SYM(rb_intern("x")), DBL2NUM(q->x));
    rb_hash_aset(hash, ID2SYM(rb_intern("y")), DBL2NUM(q->y));
    rb_hash_aset(hash, ID2SYM(rb_intern("z")), DBL2NUM(q->z));
    rb_hash_aset(hash, ID2SYM(rb_intern("w")), DBL2NUM(q->w));
    return hash;
}

VALUE rb_quaternion_to_vec4(VALUE self) {
    QUATERNION();
    Vector4 *v = ALLOC(Vector4);
    memcpy(v, q, sizeof(Quaternion));
    return NUMERIX_WRAP(rb_cVector4, v);
}

VALUE rb_quaternion_normalize(VALUE self) {
    QUATERNION();
    Quaternion *result = ALLOC(Quaternion);

    float invNorm = 1.0f / sqrtf(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
    result->x = q->x * invNorm;
    result->y = q->y * invNorm;
    result->z = q->z * invNorm;
    result->w = q->w * invNorm;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_quaternion_normalize_bang(VALUE self) {
    QUATERNION();

    float invNorm = 1.0f / sqrtf(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
    q->x = q->x * invNorm;
    q->y = q->y * invNorm;
    q->z = q->z * invNorm;
    q->w = q->w * invNorm;

    return self;
}

VALUE rb_quaternion_conjugate(VALUE self) {
    QUATERNION();
    Quaternion *result = ALLOC(Quaternion);

    result->x = -q->x;
    result->y = -q->y;
    result->z = -q->z;
    result->w = q->w;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_quaternion_conjugate_bang(VALUE self) {
    QUATERNION();

    q->x = -q->x;
    q->y = -q->y;
    q->z = -q->z;
    q->w = q->w;

    return self;
}

VALUE rb_quaternion_dot(VALUE self, VALUE other) {
    Quaternion *q1, *q2;
    Data_Get_Struct(self, Quaternion, q1);
    Data_Get_Struct(other, Quaternion, q2);

    return DBL2NUM(q1->x * q2->x + q1->y * q2->y + q1->z * q2->z + q1->w * q2->w);
}

VALUE rb_quaternion_identity(VALUE klass) {
    Quaternion *q = ALLOC(Quaternion);
    q->x = 0.0f;
    q->y = 0.0f;
    q->z = 0.0f;
    q->w = 1.0f;
    return NUMERIX_WRAP(klass, q);
}

VALUE rb_quaternion_inverse(VALUE self) {
    QUATERNION();
    Quaternion *result = ALLOC(Quaternion);

    //  -1   (       a              -v       )
    // q   = ( -------------   ------------- )
    //       (  a^2 + |v|^2  ,  a^2 + |v|^2  )

    float ls = q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w;
    float invNorm = 1.0f / ls;

    result->x = -q->x * invNorm;
    result->y = -q->y * invNorm;
    result->z = -q->z * invNorm;
    result->w = q->w * invNorm;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_quaternion_concatenate(VALUE self, VALUE other) {
    Quaternion *q1, *q2, *result;
    Data_Get_Struct(self, Quaternion, q1);
    Data_Get_Struct(other, Quaternion, q2);
    result = ALLOC(Quaternion);

    // Concatenate rotation is actually q2 * q1 instead of q1 * q2.
    // So that's why q2 goes q1 and q1 goes q2.
    float q1x = q2->x;
    float q1y = q2->y;
    float q1z = q2->z;
    float q1w = q2->w;

    float q2x = q1->x;
    float q2y = q1->y;
    float q2z = q1->z;
    float q2w = q1->w;

    // cross(av, bv)
    float cx = q1y * q2z - q1z * q2y;
    float cy = q1z * q2x - q1x * q2z;
    float cz = q1x * q2y - q1y * q2x;

    float dot = q1x * q2x + q1y * q2y + q1z * q2z;

    result->x = q1x * q2w + q2x * q1w + cx;
    result->y = q1y * q2w + q2y * q1w + cy;
    result->z = q1z * q2w + q2z * q1w + cz;
    result->w = q1w * q2w - dot;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_quaternion_concatenate_bang(VALUE self, VALUE other) {
    Quaternion *q1, *q2;
    Data_Get_Struct(self, Quaternion, q1);
    Data_Get_Struct(other, Quaternion, q2);

    // Concatenate rotation is actually q2 * q1 instead of q1 * q2.
    // So that's why q2 goes q1 and q1 goes q2.
    float q1x = q2->x;
    float q1y = q2->y;
    float q1z = q2->z;
    float q1w = q2->w;

    float q2x = q1->x;
    float q2y = q1->y;
    float q2z = q1->z;
    float q2w = q1->w;

    // cross(av, bv)
    float cx = q1y * q2z - q1z * q2y;
    float cy = q1z * q2x - q1x * q2z;
    float cz = q1x * q2y - q1y * q2x;

    float dot = q1x * q2x + q1y * q2y + q1z * q2z;

    q1->x = q1x * q2w + q2x * q1w + cx;
    q1->y = q1y * q2w + q2y * q1w + cy;
    q1->z = q1z * q2w + q2z * q1w + cz;
    q1->w = q1w * q2w - dot;

    return self;
}

VALUE rb_quaternion_lerp(VALUE self, VALUE other, VALUE amount) {
    Quaternion *q1, *q2, *result;
    Data_Get_Struct(self, Quaternion, q1);
    Data_Get_Struct(other, Quaternion, q2);
    result = ALLOC(Quaternion);

    float t = amount;
    float t1 = 1.0f - t;
    float dot = q1->x * q2->x + q1->y * q2->y + q1->z * q2->z + q1->w * q2->w;

    if (dot >= 0.0f) {
        result->x = t1 * q1->x + t * q2->x;
        result->y = t1 * q1->y + t * q2->y;
        result->z = t1 * q1->z + t * q2->z;
        result->w = t1 * q1->w + t * q2->w;
    } else {
        result->x = t1 * q1->x - t * q2->x;
        result->y = t1 * q1->y - t * q2->y;
        result->z = t1 * q1->z - t * q2->z;
        result->w = t1 * q1->w - t * q2->w;
    }

    // Normalize it.
    float ls = result->x * result->x + result->y * result->y + result->z * result->z + result->w * result->w;
    float invNorm = 1.0f / sqrtf(ls);

    result->x *= invNorm;
    result->y *= invNorm;
    result->z *= invNorm;
    result->w *= invNorm;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_quaternion_lerp_bang(VALUE self, VALUE other, VALUE amount) {
    Quaternion *q1, *q2;
    Data_Get_Struct(self, Quaternion, q1);
    Data_Get_Struct(other, Quaternion, q2);

    float t = amount;
    float t1 = 1.0f - t;
    float dot = q1->x * q2->x + q1->y * q2->y + q1->z * q2->z + q1->w * q2->w;

    if (dot >= 0.0f) {
        q1->x = t1 * q1->x + t * q2->x;
        q1->y = t1 * q1->y + t * q2->y;
        q1->z = t1 * q1->z + t * q2->z;
        q1->w = t1 * q1->w + t * q2->w;
    } else {
        q1->x = t1 * q1->x - t * q2->x;
        q1->y = t1 * q1->y - t * q2->y;
        q1->z = t1 * q1->z - t * q2->z;
        q1->w = t1 * q1->w - t * q2->w;
    }

    // Normalize it.
    float ls = q1->x * q1->x + q1->y * q1->y + q1->z * q1->z + q1->w * q1->w;
    float invNorm = 1.0f / sqrtf(ls);

    q1->x *= invNorm;
    q1->y *= invNorm;
    q1->z *= invNorm;
    q1->w *= invNorm;

    return self;
}

VALUE rb_quaternion_slerp(VALUE self, VALUE other, VALUE amount) {
    Quaternion *q1, *q2, *result;
    Data_Get_Struct(self, Quaternion, q1);
    Data_Get_Struct(other, Quaternion, q2);

    const float epsilon = 1e-6f;

    float t = amount;
    float cosOmega = q1->x * q2->x + q1->y * q2->y + q1->z * q2->z + q1->w * q2->w;
    int flip = 0;
    float s1, s2;

    if (cosOmega < 0.0f) {
        flip = 1;
        cosOmega = -cosOmega;
    }

    if (cosOmega > (1.0f - epsilon)) {
        // Too close, do straight linear interpolation.
        s1 = 1.0f - t;
        s2 = (flip) ? -t : t;
    } else {
        float omega = acosf(cosOmega);
        float invSinOmega = 1.0f / sinf(omega);

        s1 = sinf((1.0f - t) * omega) * invSinOmega;
        s2 = (flip)
                 ? -sinf(t * omega) * invSinOmega
                 : sinf(t * omega) * invSinOmega;
    }

    result = ALLOC(Quaternion);
    result->x = s1 * q1->x + s2 * q2->x;
    result->y = s1 * q1->y + s2 * q2->y;
    result->z = s1 * q1->z + s2 * q2->z;
    result->w = s1 * q1->w + s2 * q2->w;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_quaternion_slerp_bang(VALUE self, VALUE other, VALUE amount) {
    Quaternion *q1, *q2;
    Data_Get_Struct(self, Quaternion, q1);
    Data_Get_Struct(other, Quaternion, q2);

    const float epsilon = 1e-6f;

    float t = amount;
    float cosOmega = q1->x * q2->x + q1->y * q2->y + q1->z * q2->z + q1->w * q2->w;
    int flip = 0;
    float s1, s2;

    if (cosOmega < 0.0f) {
        flip = 1;
        cosOmega = -cosOmega;
    }

    if (cosOmega > (1.0f - epsilon)) {
        // Too close, do straight linear interpolation.
        s1 = 1.0f - t;
        s2 = (flip) ? -t : t;
    } else {
        float omega = acosf(cosOmega);
        float invSinOmega = 1.0f / sinf(omega);

        s1 = sinf((1.0f - t) * omega) * invSinOmega;
        s2 = (flip)
                 ? -sinf(t * omega) * invSinOmega
                 : sinf(t * omega) * invSinOmega;
    }

    q1->x = s1 * q1->x + s2 * q2->x;
    q1->y = s1 * q1->y + s2 * q2->y;
    q1->z = s1 * q1->z + s2 * q2->z;
    q1->w = s1 * q1->w + s2 * q2->w;

    return self;
}

VALUE rb_quaternion_from_axis_angle(VALUE klass, VALUE vec3, VALUE angle) {
    Vector3 *axis;
    Data_Get_Struct(vec3, Vector3, axis);
    Quaternion *result = ALLOC(Quaternion);

    float half = NUM2FLT(angle) * 0.5f;
    float s = sinf(half);

    result->x = axis->x * s;
    result->y = axis->y * s;
    result->z = axis->z * s;
    result->w = cosf(half);

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_quaternion_from_yaw_pitch_roll(VALUE klass, VALUE yaw, VALUE pitch, VALUE roll) {
    //  Roll first, about axis the object is facing, then
    //  pitch upward, then yaw to face into the new heading

    float sr, cr, sp, cp, sy, cy;

    float halfRoll = roll * 0.5f;
    sr = sinf(halfRoll);
    cr = cosf(halfRoll);

    float halfPitch = pitch * 0.5f;
    sp = sinf(halfPitch);
    cp = cosf(halfPitch);

    float halfYaw = yaw * 0.5f;
    sy = sinf(halfYaw);
    cy = cosf(halfYaw);

    Quaternion *result = ALLOC(Quaternion);

    result->x = cy * sp * cr + sy * cp * sr;
    result->y = sy * cp * cr - cy * sp * sr;
    result->z = cy * cp * sr - sy * sp * cr;
    result->w = cy * cp * cr + sy * sp * sr;

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_quaternion_from_rotation_matrix(VALUE klass, VALUE matrix) {
    Matrix4x4 *m;
    Data_Get_Struct(matrix, Matrix4x4, m);
    Quaternion *q = ALLOC(Quaternion);

    float trace = m->m11 + m->m22 + m->m33;
    float s;
    if (trace > 0.0f) {
        s = sqrtf(trace + 1.0f);
        q->w = s * 0.5f;
        s = 0.5f / s;
        q->x = (m->m23 - m->m32) * s;
        q->y = (m->m31 - m->m13) * s;
        q->z = (m->m12 - m->m21) * s;
    } else {
        float invS;
        if (m->m11 >= m->m22 && m->m11 >= m->m33) {
            s = sqrtf(1.0f + m->m11 - m->m22 - m->m33);
            invS = 0.5f / s;
            q->x = 0.5f * s;
            q->y = (m->m12 + m->m21) * invS;
            q->z = (m->m13 + m->m31) * invS;
            q->w = (m->m23 - m->m32) * invS;
        } else if (m->m22 > m->m33) {
            s = sqrtf(1.0f + m->m22 - m->m11 - m->m33);
            invS = 0.5f / s;
            q->x = (m->m21 + m->m12) * invS;
            q->y = 0.5f * s;
            q->z = (m->m32 + m->m23) * invS;
            q->w = (m->m31 - m->m13) * invS;
        } else {
            s = sqrtf(1.0f + m->m33 - m->m11 - m->m22);
            invS = 0.5f / s;
            q->x = (m->m31 + m->m13) * invS;
            q->y = (m->m32 + m->m23) * invS;
            q->z = 0.5f * s;
            q->w = (m->m12 - m->m21) * invS;
        }
    }

    return NUMERIX_WRAP(klass, q);
}

static inline VALUE rb_quaternion_slerp_s(VALUE klass, VALUE quaternion1, VALUE quaternion2, VALUE amount) {
    Quaternion *q1, *q2, *result;
    Data_Get_Struct(quaternion1, Quaternion, q1);
    Data_Get_Struct(quaternion2, Quaternion, q2);

    const float epsilon = 1e-6f;

    float t = amount;
    float cosOmega = q1->x * q2->x + q1->y * q2->y + q1->z * q2->z + q1->w * q2->w;
    int flip = 0;
    float s1, s2;

    if (cosOmega < 0.0f) {
        flip = 1;
        cosOmega = -cosOmega;
    }

    if (cosOmega > (1.0f - epsilon)) {
        // Too close, do straight linear interpolation.
        s1 = 1.0f - t;
        s2 = (flip) ? -t : t;
    } else {
        float omega = acosf(cosOmega);
        float invSinOmega = 1.0f / sinf(omega);

        s1 = sinf((1.0f - t) * omega) * invSinOmega;
        s2 = (flip)
                 ? -sinf(t * omega) * invSinOmega
                 : sinf(t * omega) * invSinOmega;
    }

    result = ALLOC(Quaternion);
    result->x = s1 * q1->x + s2 * q2->x;
    result->y = s1 * q1->y + s2 * q2->y;
    result->z = s1 * q1->z + s2 * q2->z;
    result->w = s1 * q1->w + s2 * q2->w;

    return NUMERIX_WRAP(klass, result);
}

static inline VALUE rb_quaternion_lerp_s(VALUE klass, VALUE quaternion1, VALUE quaternion2, VALUE amount) {
    Quaternion *q1, *q2, *result;
    Data_Get_Struct(quaternion1, Quaternion, q1);
    Data_Get_Struct(quaternion2, Quaternion, q2);
    result = ALLOC(Quaternion);

    float t = amount;
    float t1 = 1.0f - t;
    float dot = q1->x * q2->x + q1->y * q2->y + q1->z * q2->z + q1->w * q2->w;

    if (dot >= 0.0f) {
        result->x = t1 * q1->x + t * q2->x;
        result->y = t1 * q1->y + t * q2->y;
        result->z = t1 * q1->z + t * q2->z;
        result->w = t1 * q1->w + t * q2->w;
    } else {
        result->x = t1 * q1->x - t * q2->x;
        result->y = t1 * q1->y - t * q2->y;
        result->z = t1 * q1->z - t * q2->z;
        result->w = t1 * q1->w - t * q2->w;
    }

    // Normalize it.
    float ls = result->x * result->x + result->y * result->y + result->z * result->z + result->w * result->w;
    float invNorm = 1.0f / sqrtf(ls);

    result->x *= invNorm;
    result->y *= invNorm;
    result->z *= invNorm;
    result->w *= invNorm;

    return NUMERIX_WRAP(klass, result);
}
