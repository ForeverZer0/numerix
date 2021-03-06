
#include "matrix3x2.h"

void Init_matrix3x2(VALUE outer) {
    rb_define_alloc_func(rb_cMatrix3x2, rb_matrix3x2_allocate);
    rb_define_method(rb_cMatrix3x2, "initialize", rb_matrix3x2_initialize, -1);

    // Instance
    rb_define_method(rb_cMatrix3x2, "identity?", rb_matrix3x2_identity_p, 0);
    rb_define_method(rb_cMatrix3x2, "translation", rb_matrix3x2_translation, 0);
    rb_define_method(rb_cMatrix3x2, "translation=", rb_matrix3x2_translation_set, 1);
    rb_define_method(rb_cMatrix3x2, "determinant", rb_matrix3x2_determinant, 0);
    rb_define_method(rb_cMatrix3x2, "row", rb_matrix3x2_row, 1);
    rb_define_method(rb_cMatrix3x2, "column", rb_matrix3x2_column, 1);
    rb_define_method(rb_cMatrix3x2, "each_row", rb_matrix3x2_each_row, 0);
    rb_define_method(rb_cMatrix3x2, "each_column", rb_matrix3x2_each_column, 0);
    rb_define_method(rb_cMatrix3x2, "invert", rb_matrix3x2_invert, 0);
    rb_define_method(rb_cMatrix3x2, "lerp", rb_matrix3x2_lerp, 2);
    rb_define_method(rb_cMatrix3x2, "lerp!", rb_matrix3x2_lerp_bang, 2);
    rb_define_method(rb_cMatrix3x2, "map", rb_matrix3x2_map, 0);
    rb_define_method(rb_cMatrix3x2, "map!", rb_matrix3x2_map_bang, 0);

    // Alias
    rb_define_alias(rb_cMatrix3x2, "collect", "map");
    rb_define_alias(rb_cMatrix3x2, "collect!", "map!");

    // Conversion
    rb_define_method(rb_cMatrix3x2, "to_s", rb_matrix3x2_to_s, 0);
    rb_define_method(rb_cMatrix3x2, "to_a", rb_matrix3x2_to_a, 0);
    rb_define_method(rb_cMatrix3x2, "to_h", rb_matrix3x2_to_h, 0);

    // Operators
    rb_define_method(rb_cMatrix3x2, "-@", rb_matrix3x2_negate, 0);
    rb_define_method(rb_cMatrix3x2, "+", rb_matrix3x2_add, 1);
    rb_define_method(rb_cMatrix3x2, "-", rb_matrix3x2_subtract, 1);
    rb_define_method(rb_cMatrix3x2, "*", rb_matrix3x2_multiply, 1);
    rb_define_method(rb_cMatrix3x2, "==", rb_matrix3x2_equal, 1);
    rb_define_method(rb_cMatrix3x2, "[]", rb_matrix3x2_aref, -1);
    rb_define_method(rb_cMatrix3x2, "[]=", rb_matrix3x2_aset, -1);
    rb_define_method(rb_cMatrix3x2, "**", rb_matrix3x2_pow, 1);

    // Class
    rb_define_singleton_method(rb_cMatrix3x2, "identity", rb_matrix3x2_identity, 0);
    rb_define_singleton_method(rb_cMatrix3x2, "create_translation", rb_matrix3x2_create_translation, -1);
    rb_define_singleton_method(rb_cMatrix3x2, "create_scale", rb_matrix3x2_create_scale, -1);
    rb_define_singleton_method(rb_cMatrix3x2, "create_skew", rb_matrix3x2_create_skew, -1);
    rb_define_singleton_method(rb_cMatrix3x2, "create_rotation", rb_matrix3x2_create_rotation, -1);
    rb_define_singleton_method(rb_cMatrix3x2, "lerp", rb_matrix3x2_lerp_s, 3);
}

static VALUE rb_matrix3x2_allocate(VALUE klass) {
    Matrix3x2 *m = ALLOC(Matrix3x2);
    memset(m, 0, sizeof(Matrix3x2));
    return NUMERIX_WRAP(klass, m);
}

VALUE rb_matrix3x2_initialize(int argc, VALUE *argv, VALUE self) {
    MATRIX3X2();
    if (argc == 6) {
        m->m11 = NUM2FLT(argv[0]);
        m->m12 = NUM2FLT(argv[1]);
        m->m21 = NUM2FLT(argv[2]);
        m->m22 = NUM2FLT(argv[3]);
        m->m31 = NUM2FLT(argv[4]);
        m->m32 = NUM2FLT(argv[5]);
    } else if (argc != 0)
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 0, 6)", argc);

    return Qnil;
}

VALUE rb_matrix3x2_identity_p(VALUE self) {
    MATRIX3X2();
    // Check diagonal element first for early out.
    return m->m11 == 1.0f && m->m22 == 1.0f && m->m12 == 0.0f &&
                   m->m21 == 0.0f && m->m31 == 0.0f && m->m32 == 0.0f
               ? Qtrue
               : Qfalse;
}

VALUE rb_matrix3x2_identity(VALUE klass) {
    Matrix3x2 *m = ALLOC(Matrix3x2);
    m->m11 = 1.0f;
    m->m12 = 0.0f;
    m->m21 = 0.0f;
    m->m22 = 1.0f;
    m->m31 = 0.0f;
    m->m32 = 0.0f;
    return NUMERIX_WRAP(klass, m);
}

VALUE rb_matrix3x2_translation(VALUE self) {
    MATRIX3X2();
    Vector2 *v = ALLOC(Vector2);
    v->x = m->m31;
    v->y = m->m32;
    return NUMERIX_WRAP(rb_cVector2, v);
}

VALUE rb_matrix3x2_translation_set(VALUE self, VALUE value) {
    MATRIX3X2();
    Vector2 *v;
    Data_Get_Struct(value, Vector2, v);
    m->m31 = v->x;
    m->m32 = v->y;
    return value;
}

VALUE rb_matrix3x2_create_translation(int argc, VALUE *argv, VALUE klass) {
    Matrix3x2 *result = ALLOC(Matrix3x2);

    if (argc == 1) {
        Vector2 *v;
        Data_Get_Struct(argv[0], Vector2, v);
        result->m31 = v->x;
        result->m32 = v->y;

    } else if (argc == 2) {
        result->m31 = NUM2FLT(argv[0]);
        result->m32 = NUM2FLT(argv[1]);
    } else
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 2)", argc);

    result->m11 = 1.0f;
    result->m12 = 0.0f;
    result->m21 = 0.0f;
    result->m22 = 1.0f;

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix3x2_negate(VALUE self) {
    MATRIX4X4();
    Matrix3x2 *result = ALLOC(Matrix3x2);

    result->m11 = -m->m11;
    result->m12 = -m->m12;
    result->m21 = -m->m21;
    result->m22 = -m->m22;
    result->m31 = -m->m31;
    result->m32 = -m->m32;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_matrix3x2_add(VALUE self, VALUE other) {
    Matrix3x2 *m1, *m2, *result;
    Data_Get_Struct(self, Matrix3x2, m1);
    Data_Get_Struct(other, Matrix3x2, m2);
    result = ALLOC(Matrix3x2);

    result->m11 = m1->m11 + m2->m11;
    result->m12 = m1->m12 + m2->m12;
    result->m21 = m1->m21 + m2->m21;
    result->m22 = m1->m22 + m2->m22;
    result->m31 = m1->m31 + m2->m31;
    result->m32 = m1->m32 + m2->m32;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_matrix3x2_subtract(VALUE self, VALUE other) {
    Matrix3x2 *m1, *m2, *result;
    Data_Get_Struct(self, Matrix3x2, m1);
    Data_Get_Struct(other, Matrix3x2, m2);
    result = ALLOC(Matrix3x2);

    result->m11 = m1->m11 - m2->m11;
    result->m12 = m1->m12 - m2->m12;
    result->m21 = m1->m21 - m2->m21;
    result->m22 = m1->m22 - m2->m22;
    result->m31 = m1->m31 - m2->m31;
    result->m32 = m1->m32 - m2->m32;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_matrix3x2_multiply(VALUE self, VALUE other) {
    Matrix3x2 *m1, *result;
    Data_Get_Struct(self, Matrix3x2, m1);
    result = ALLOC(Matrix3x2);
    VALUE klass = CLASS_OF(self);
    if (NUMERIX_TYPE_P(other, klass)) {
        Matrix3x2 *m2, *result;
        Data_Get_Struct(other, Matrix3x2, m2);

        // First row
        result->m11 = m1->m11 * m2->m11 + m1->m12 * m2->m21;
        result->m12 = m1->m11 * m2->m12 + m1->m12 * m2->m22;

        // Second row
        result->m21 = m1->m21 * m2->m11 + m1->m22 * m2->m21;
        result->m22 = m1->m21 * m2->m12 + m1->m22 * m2->m22;

        // Third row
        result->m31 = m1->m31 * m2->m11 + m1->m32 * m2->m21 + m2->m31;
        result->m32 = m1->m31 * m2->m12 + m1->m32 * m2->m22 + m2->m32;
    } else {
        float scalar = NUM2FLT(other);
        result->m11 = m1->m11 * scalar;
        result->m12 = m1->m12 * scalar;
        result->m21 = m1->m21 * scalar;
        result->m22 = m1->m22 * scalar;
        result->m31 = m1->m31 * scalar;
        result->m32 = m1->m32 * scalar;
    }

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix3x2_pow(VALUE self, VALUE exponent) {
    struct RData *rdata = RDATA(self);
    const int count = 6;
    float *result = ruby_xmalloc(sizeof(float) * count);
    float *m = (float *)rdata->data;
    float e = fabsf(NUM2FLT(exponent));
    for (int i = 0; i < count; i++)
        result[i] = powf(fabsf(m[i]), e);

    return NUMERIX_WRAP(rdata->basic.klass, result);
}

VALUE rb_matrix3x2_equal(VALUE self, VALUE other) {
    if (CLASS_OF(other) != CLASS_OF(self))
        return Qfalse;
    Matrix3x2 *m1, *m2;
    Data_Get_Struct(self, Matrix3x2, m1);
    Data_Get_Struct(other, Matrix3x2, m2);
    return FLT_EQUAL(m1->m11, m2->m11) && FLT_EQUAL(m1->m12, m2->m12) &&
                   FLT_EQUAL(m1->m21, m2->m21) && FLT_EQUAL(m1->m22, m2->m22) &&
                   FLT_EQUAL(m1->m31, m2->m31) && FLT_EQUAL(m1->m32, m2->m32)
               ? Qtrue
               : Qfalse;
}

VALUE rb_matrix3x2_row(VALUE self, VALUE row) {
    MATRIX3X2();
    VALUE args = rb_ary_new_capa(4);
    int r = NUM2INT(row);
    switch (r) {
        case 0: {
            rb_ary_push(args, DBL2NUM(m->m11));
            rb_ary_push(args, DBL2NUM(m->m12));
            break;
        }
        case 1: {
            rb_ary_push(args, DBL2NUM(m->m21));
            rb_ary_push(args, DBL2NUM(m->m22));
            break;
        }
        case 2: {
            rb_ary_push(args, DBL2NUM(m->m31));
            rb_ary_push(args, DBL2NUM(m->m32));
            break;
        }
        default:
            break;
    }
    return args;
}

VALUE rb_matrix3x2_column(VALUE self, VALUE column) {
    MATRIX3X2();
    VALUE args = rb_ary_new_capa(3);
    int c = NUM2INT(column);
    if (c == 0) {
        rb_ary_push(args, DBL2NUM(m->m11));
        rb_ary_push(args, DBL2NUM(m->m21));
        rb_ary_push(args, DBL2NUM(m->m31));
    } else if (c == 1) {
        rb_ary_push(args, DBL2NUM(m->m12));
        rb_ary_push(args, DBL2NUM(m->m22));
        rb_ary_push(args, DBL2NUM(m->m32));
    }
    return args;
}

VALUE rb_matrix3x2_map(VALUE self) {
    const int count = 6;

    struct RData *rdata = RDATA(self);
    float *flt = (float *)rdata->data;
    float *result = (float *)ruby_xmalloc(count * sizeof(float));

    for (int i = 0; i < count; i++)
        result[i] = NUM2FLT(rb_yield(DBL2NUM(flt[i])));

    return NUMERIX_WRAP(rdata->basic.klass, result);
}

VALUE rb_matrix3x2_map_bang(VALUE self) {
    const int count = 6;

    float *flt = (float *)RDATA(self)->data;
    for (int i = 0; i < count; i++)
        flt[i] = NUM2FLT(rb_yield(DBL2NUM(flt[i])));

    return self;
}

VALUE rb_matrix3x2_to_s(VALUE self) {
    MATRIX3X2();
    return rb_sprintf("{{%f, %f}, {%f, %f}, {%f, %f}}", m->m11, m->m12, m->m21, m->m22, m->m31, m->m32);
}

VALUE rb_matrix3x2_to_a(VALUE self) {
    MATRIX3X2();
    VALUE array = rb_ary_new_capa(3);
    // Row 1
    VALUE r1 = rb_ary_new_capa(2);
    rb_ary_store(r1, 0, DBL2NUM(m->m11));
    rb_ary_store(r1, 1, DBL2NUM(m->m12));
    rb_ary_push(array, r1);
    // Row 2
    VALUE r2 = rb_ary_new_capa(2);
    rb_ary_store(r2, 0, DBL2NUM(m->m21));
    rb_ary_store(r2, 1, DBL2NUM(m->m22));
    rb_ary_push(array, r2);
    // Row 3
    VALUE r3 = rb_ary_new_capa(2);
    rb_ary_store(r3, 0, DBL2NUM(m->m31));
    rb_ary_store(r3, 1, DBL2NUM(m->m32));
    rb_ary_push(array, r3);
    return array;
}

VALUE rb_matrix3x2_to_h(VALUE self) {
    MATRIX3X2();
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, ID2SYM(rb_intern("m11")), DBL2NUM(m->m11));
    rb_hash_aset(hash, ID2SYM(rb_intern("m12")), DBL2NUM(m->m12));
    rb_hash_aset(hash, ID2SYM(rb_intern("m21")), DBL2NUM(m->m21));
    rb_hash_aset(hash, ID2SYM(rb_intern("m22")), DBL2NUM(m->m22));
    rb_hash_aset(hash, ID2SYM(rb_intern("m31")), DBL2NUM(m->m31));
    rb_hash_aset(hash, ID2SYM(rb_intern("m32")), DBL2NUM(m->m32));
    return hash;
}

VALUE rb_matrix3x2_create_scale(int argc, VALUE *argv, VALUE klass) {
    Matrix3x2 *result = ALLOC(Matrix3x2);
    result->m12 = 0.0f;
    result->m21 = 0.0f;
    switch (argc) {
        case 1: {
            result->m31 = 0.0f;
            result->m32 = 0.0f;
            if (NUMERIX_TYPE_P(argv[0], rb_cVector2)) {
                Vector2 *vscale;
                Data_Get_Struct(argv[0], Vector2, vscale);
                result->m11 = vscale->x;
                result->m22 = vscale->y;
            } else {
                float scale = NUM2FLT(argv[0]);
                result->m11 = scale;
                result->m22 = scale;
            }
        }
        case 2: {
            if (NUMERIX_TYPE_P(argv[0], rb_cVector2)) {
                Vector2 *v1, *v2;
                Data_Get_Struct(argv[0], Vector2, v1);
                Data_Get_Struct(argv[1], Vector2, v2);
                result->m11 = v1->x;
                result->m22 = v1->y;
                result->m31 = v2->x * (1.0f - v1->x);
                result->m32 = v2->y * (1.0f - v1->y);
            } else {
                if (NUMERIX_TYPE_P(argv[1], rb_cVector2)) {
                    float s = NUM2FLT(argv[0]);
                    Vector2 *cp;
                    Data_Get_Struct(argv[1], Vector2, cp);
                    result->m11 = s;
                    result->m22 = s;
                    result->m31 = cp->x * (1.0f - s);
                    result->m32 = cp->y * (1.0f - s);
                } else {
                    result->m11 = NUM2FLT(argv[0]);
                    result->m22 = NUM2FLT(argv[1]);
                    result->m31 = 0.0f;
                    result->m32 = 0.0f;
                }
            }
            break;
        }
        case 3: {
            Vector2 *vec2;
            Data_Get_Struct(argv[2], Vector2, vec2);
            float xscale = NUM2FLT(argv[0]);
            float yscale = NUM2FLT(argv[1]);

            result->m11 = xscale;
            result->m22 = yscale;
            result->m31 = vec2->x * (1.0f - xscale);
            result->m32 = vec2->y * (1.0f - yscale);
        }
        default:
            rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 2, 3)", argc);
    }

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix3x2_create_skew(int argc, VALUE *argv, VALUE klass) {
    if (argc != 2 && argc != 3)
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 2, 3)", argc);

    Matrix3x2 *result = ALLOC(Matrix3x2);

    float xTan = tanf(NUM2FLT(argv[0]));
    float yTan = tanf(NUM2FLT(argv[1]));

    result->m12 = yTan;
    result->m21 = xTan;
    result->m11 = 1.0f;
    result->m22 = 1.0f;

    if (argc == 3) {
        Vector2 *cp;
        Data_Get_Struct(argv[2], Vector2, cp);
        result->m31 = -cp->x * xTan;
        result->m32 = -cp->y * yTan;
    } else {
        result->m31 = 0.0f;
        result->m32 = 0.0f;
    }

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix3x2_create_rotation(int argc, VALUE *argv, VALUE klass) {
    if (argc != 1 && argc != 2)
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 2)", argc);

    Matrix3x2 *result = ALLOC(Matrix3x2);
    float radians = remainderf(NUM2FLT(argv[0]), NUMERIX_PI * 2.0f);
    const float epsilon = 0.001f * NUMERIX_PI / 180.0f;  // 0.1% of a degree
    float c, s;

    if (radians > -epsilon && radians < epsilon) {
        // Exact case for zero rotation.
        c = 1;
        s = 0;
    } else if (radians > NUMERIX_HALF_PI - epsilon && radians < NUMERIX_HALF_PI + epsilon) {
        // Exact case for 90 degree rotation.
        c = 0;
        s = 1;
    } else if (radians < -NUMERIX_PI + epsilon || radians > NUMERIX_PI - epsilon) {
        // Exact case for 180 degree rotation.
        c = -1;
        s = 0;
    } else if (radians > -NUMERIX_HALF_PI - epsilon && radians < -NUMERIX_HALF_PI + epsilon) {
        // Exact case for 270 degree rotation.
        c = 0;
        s = -1;
    } else {
        // Arbitrary rotation.
        c = cosf(radians);
        s = sinf(radians);
    }

    // [  c  s ]
    // [ -s  c ]
    // [  0  0 ]
    result->m11 = c;
    result->m12 = s;
    result->m21 = -s;
    result->m22 = c;
    if (argc == 2) {
        Vector2 *cp;
        Data_Get_Struct(argv[1], Vector2, cp);
        result->m31 = cp->x * (1.0f - c) + cp->y * s;
        result->m32 = cp->y * (1.0f - c) - cp->x * s;
    } else {
        result->m31 = 0.0f;
        result->m32 = 0.0f;
    }

    return NUMERIX_WRAP(klass, result);
}

VALUE rb_matrix3x2_determinant(VALUE self) {
    MATRIX3X2();
    // There isn't actually any such thing as a determinant for a non-square matrix,
    // but this 3x2 type is really just an optimization of a 3x3 where we happen to
    // know the rightmost column is always (0, 0, 1). So we expand to 3x3 format:
    //
    //  [ M11, M12, 0 ]
    //  [ M21, M22, 0 ]
    //  [ M31, M32, 1 ]
    //
    // Sum the diagonal products:
    //  (M11 * M22 * 1) + (M12 * 0 * M31) + (0 * M21 * M32)
    //
    // Subtract the opposite diagonal products:
    //  (M31 * M22 * 0) + (M32 * 0 * M11) + (1 * M21 * M12)
    //
    // Collapse out the constants and oh look, this is just a 2x2 determinant!
    return DBL2NUM((m->m11 * m->m22) - (m->m21 * m->m12));
}

VALUE rb_matrix3x2_each_row(VALUE self) {
    MATRIX3X2();
    for (int i = 0; i < 3; i++) {
        VALUE index = INT2NUM(i);
        rb_yield(rb_matrix3x2_row(self, index));
    }
    return self;
}

VALUE rb_matrix3x2_each_column(VALUE self) {
    MATRIX3X2();
    for (int i = 0; i < 2; i++) {
        VALUE index = INT2NUM(i);
        rb_yield(rb_matrix3x2_column(self, index));
    }
    return self;
}

VALUE rb_matrix3x2_aref(int argc, VALUE *argv, VALUE self) {
    if (argc == 1) {
        return rb_call_super(1, argv);
    } else if (argc == 2) {
        int r = NUM2INT(argv[0]);
        int c = NUM2INT(argv[1]);
        if (r < 0 || r > 2 || c < 0 || c > 1)
            return Qnil;
        VALUE arg = INT2NUM(r + (c * 4));
        return rb_call_super(1, &arg);
    }
    rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 2)", argc);
    return Qnil;
}

VALUE rb_matrix3x2_aset(int argc, VALUE *argv, VALUE self) {
    if (argc == 2) {
        return rb_call_super(2, argv);
    } else if (argc == 3) {
        int r = NUM2INT(argv[0]);
        int c = NUM2INT(argv[1]);
        if (r < 0 || r > 2 || c < 0 || c > 1)
            return Qnil;
        argv[1] = INT2NUM(r + (c * 3));
        return rb_call_super(2, &argv[1]);
    }
    rb_raise(rb_eArgError, "wrong number of arguments (%d for 2, 3)", argc);
    return Qnil;
}

VALUE rb_matrix3x2_invert(VALUE self) {
    Matrix3x2 *m, *result;
    Data_Get_Struct(self, Matrix3x2, m);
    result = ALLOC(Matrix3x2);

    float det = (m->m11 * m->m22) - (m->m21 * m->m12);

    if (fabsf(det) < FLT_EPSILON) {
        float *ptr = (float *)result;
        for (int i = 0; i < 6; i++)
            ptr[i] = NAN;
    } else {
        float invDet = 1.0f / det;
        result->m11 = m->m22 * invDet;
        result->m12 = -m->m12 * invDet;
        result->m21 = -m->m21 * invDet;
        result->m22 = m->m11 * invDet;
        result->m31 = (m->m21 * m->m32 - m->m31 * m->m22) * invDet;
        result->m32 = (m->m31 * m->m12 - m->m11 * m->m32) * invDet;
    }

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_matrix3x2_lerp(VALUE self, VALUE other, VALUE amount) {
    Matrix3x2 *m1, *m2, *result;
    Data_Get_Struct(self, Matrix3x2, m1);
    Data_Get_Struct(other, Matrix3x2, m2);
    result = ALLOC(Matrix3x2);

    float weight = NUMERIX_CLAMP(NUM2FLT(amount), 0.0f, 1.0f);
    // First row
    result->m11 = m1->m11 + (m2->m11 - m1->m11) * weight;
    result->m12 = m1->m12 + (m2->m12 - m1->m12) * weight;

    // Second row
    result->m21 = m1->m21 + (m2->m21 - m1->m21) * weight;
    result->m22 = m1->m22 + (m2->m22 - m1->m22) * weight;

    // Third row
    result->m31 = m1->m31 + (m2->m31 - m1->m31) * weight;
    result->m32 = m1->m32 + (m2->m32 - m1->m32) * weight;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_matrix3x2_lerp_bang(VALUE self, VALUE other, VALUE amount) {
    Matrix3x2 *m1, *m2;
    Data_Get_Struct(self, Matrix3x2, m1);
    Data_Get_Struct(other, Matrix3x2, m2);

    float weight = NUMERIX_CLAMP(NUM2FLT(amount), 0.0f, 1.0f);
    // First row
    m1->m11 = m1->m11 + (m2->m11 - m1->m11) * weight;
    m1->m12 = m1->m12 + (m2->m12 - m1->m12) * weight;

    // Second row
    m1->m21 = m1->m21 + (m2->m21 - m1->m21) * weight;
    m1->m22 = m1->m22 + (m2->m22 - m1->m22) * weight;

    // Third row
    m1->m31 = m1->m31 + (m2->m31 - m1->m31) * weight;
    m1->m32 = m1->m32 + (m2->m32 - m1->m32) * weight;

    return self;
}

static inline VALUE rb_matrix3x2_lerp_s(VALUE klass, VALUE matrix1, VALUE matrix2, VALUE amount) {
    Matrix3x2 *m1, *m2, *result;
    Data_Get_Struct(matrix1, Matrix3x2, m1);
    Data_Get_Struct(matrix2, Matrix3x2, m2);
    result = ALLOC(Matrix3x2);

    float weight = NUMERIX_CLAMP(NUM2FLT(amount), 0.0f, 1.0f);
    // First row
    result->m11 = m1->m11 + (m2->m11 - m1->m11) * weight;
    result->m12 = m1->m12 + (m2->m12 - m1->m12) * weight;

    // Second row
    result->m21 = m1->m21 + (m2->m21 - m1->m21) * weight;
    result->m22 = m1->m22 + (m2->m22 - m1->m22) * weight;

    // Third row
    result->m31 = m1->m31 + (m2->m31 - m1->m31) * weight;
    result->m32 = m1->m32 + (m2->m32 - m1->m32) * weight;

    return NUMERIX_WRAP(klass, result);
}
