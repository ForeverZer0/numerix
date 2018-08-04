
#include "basic_vector.h"

VALUE rb_cBasicVector;

// to_a (aka elements)
// to_s
// size
// count
// address

void Init_basic_vector(VALUE outer) {
    rb_cBasicVector = rb_define_class_under(outer, "BasicVector", rb_cObject);
    rb_define_alloc_func(rb_cBasicVector, rb_basic_vector_alloc);
    rb_define_method(rb_cBasicVector, "initialize", rb_basic_vector_initialize, -1);

    // Instance
    rb_define_method(rb_cBasicVector, "size", rb_basic_vector_size, 0);
    rb_define_method(rb_cBasicVector, "address", rb_basic_vector_address, 0);
    rb_define_method(rb_cBasicVector, "count", rb_basic_vector_count, 0);
    rb_define_method(rb_cBasicVector, "length", rb_basic_vector_length, 0);
    rb_define_method(rb_cBasicVector, "length_squared", rb_basic_vector_length_squared, 0);
    rb_define_method(rb_cBasicVector, "normalize", rb_basic_vector_normalize, 0);
    rb_define_method(rb_cBasicVector, "normalize!", rb_basic_vector_normalize_bang, 0);

    // Operators
    rb_define_method(rb_cBasicVector, "+", rb_basic_vector_add, 1);
    rb_define_method(rb_cBasicVector, "-", rb_basic_vector_subtract, 1);
    rb_define_method(rb_cBasicVector, "*", rb_basic_vector_multiply, 1);
    rb_define_method(rb_cBasicVector, "/", rb_basic_vector_divide, 1);
    rb_define_method(rb_cBasicVector, "-@", rb_basic_vector_negate, 0);
    rb_define_method(rb_cBasicVector, "==", rb_basic_vector_equal, 1);

    // Alias
    rb_define_alias(rb_cBasicVector, "magnitude", "length");

    // Class
    rb_define_singleton_method(rb_cBasicVector, "[]", rb_basic_vector_create, -1);
}

VALUE rb_basic_vector_alloc(VALUE klass) {
    BasicVector *v = ALLOC(BasicVector);
    v->count = 0;
    v->values = NULL;
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_basic_vector_initialize(int argc, VALUE *argv, VALUE self) {
    BASIC_VECTOR();
    if (argc == 1)
    {
        int count = NUM2INT(argv[0]);
        if (count < 2)
        {
            rb_raise(rb_eArgError, "vector size must be 2 or greater");
            return Qnil;
        }
        v->count = count;
        v->values = (float*) ruby_xmalloc(sizeof(float) * count);
        memset(v->values, 0, count * sizeof(float));
    }
    else if (argc > 1)
    {
        v->count = argc;
        v->values = (float*) ruby_xmalloc(sizeof(float) * argc);
        for (int i = 0; i < argc; i++)
            v->values[i] = NUM2FLT(argv[i]);
    }
    else
        rb_raise(rb_eArgError, "no arguments given");

    return Qnil;
}

rb_basic_vector_create(int argc, VALUE *argv, VALUE klass) {
    rb_scan_args(argc, argv, "2*");

    BasicVector *v = ALLOC(BasicVector);
    v->count = argc;
    v->values = ruby_xmalloc(sizeof(float) * argc);
    for (int i = 0; i < argc; i++)
        v->values[i] = NUM2FLT(argv[i]);

    return NUMERIX_WRAP(klass, v);
}

VALUE rb_basic_vector_length(VALUE self) {
    BASIC_VECTOR();
    int c = v->count;
    float length = 0.0f;
    for (int i = 0; i < c; i++)
        length += v->values[i] * v->values[i];
    
    return DBL2NUM(sqrtf(length));
}

VALUE rb_basic_vector_length_squared(VALUE self) {
    BASIC_VECTOR();
    int c = v->count;
    float length = 0.0f;
    for (int i = 0; i < c; i++)
        length += v->values[i] * v->values[i];
    
    return DBL2NUM(length);
}

VALUE rb_basic_vector_normalize(VALUE self) {
    BASIC_VECTOR_RESULT();

    int c = v->count;
    float length = 0.0f;
    for (int i = 0; i < c; i++)
        length += v->values[i] * v->values[i];

    int inverse = sqrtf(length);
    for (int i = 0; i < c; i++)
        result->values[i] = v->values[i] * inverse;

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_basic_vector_normalize_bang(VALUE self) {
    BASIC_VECTOR();

    int c = v->count;
    float length = 0.0f;
    for (int i = 0; i < c; i++)
        length += v->values[i] * v->values[i];

    int inverse = sqrtf(length);
    for (int i = 0; i < c; i++)
        v->values[i] *= inverse;

    return self;
}

VALUE rb_basic_vector_add(VALUE self, VALUE other) {
    BASIC_VECTOR_OTHER_RESULT();
    for (int i = 0; i < count; i++)
        result->values[i] = v1->values[i] + v2->values[i];

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_basic_vector_subtract(VALUE self, VALUE other) {
    BASIC_VECTOR_OTHER_RESULT();
    for (int i = 0; i < count; i++)
        result->values[i] = v1->values[i] - v2->values[i];

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_basic_vector_multiply(VALUE self, VALUE other) {
    BASIC_VECTOR_RESULT();
    int count = v->count;
    if (NUMERIX_TYPE_P(other, rb_cBasicVector))
    {
        BasicVector *v2;
        Data_Get_Struct(other, BasicVector, v2);
        if (count != v2->count)
            rb_raise(rb_eArgError, "unequal length vectors");
        for (int i = 0; i < count; i++)
            result->values[i] = v->values[i] * v2->values[i];
    }
    else
    {
        float scalar = NUM2FLT(other);
        for (int i = 0; i < count; i++)
            result->values[i] = v->values[i] * scalar;
    }

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_basic_vector_divide(VALUE self, VALUE other) {
    BASIC_VECTOR_RESULT();
    int count = v->count;
    if (NUMERIX_TYPE_P(other, rb_cBasicVector))
    {
        BasicVector *v2;
        Data_Get_Struct(other, BasicVector, v2);
        if (count != v2->count)
            rb_raise(rb_eArgError, "unequal length vectors");
        for (int i = 0; i < count; i++)
            result->values[i] = v->values[i] / v2->values[i];
    }
    else
    {
        float scalar = 1.0f / NUM2FLT(other);
        for (int i = 0; i < count; i++)
            result->values[i] = v->values[i] * scalar;
    }

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_basic_vector_negate(VALUE self, VALUE other) {
    BASIC_VECTOR_RESULT();

    int c = v->count;
    for (int i = 0; i < c; i++)
        result->values[i] = -v->values[i];

    return NUMERIX_WRAP(CLASS_OF(self), result);
}

VALUE rb_basic_vector_equal(VALUE self, VALUE other) {
    if (CLASS_OF(self) != CLASS_OF(other))
        return Qfalse;

    BasicVector *v1, *v2;
    Data_Get_Struct(self, BasicVector, v1);
    Data_Get_Struct(other, BasicVector, v2);

    int count = v1->count;

    if (count != v2->count)
        return Qfalse;

    for (int i = 0; i < count; i++)
    {
        if (!FLT_EQUAL(v1->values[i], v2->values[i]))
            return Qfalse;
    }

    return Qtrue;
}

VALUE rb_basic_vector_size(VALUE self) {
    BASIC_VECTOR();
    return INT2NUM(v->count * sizeof(float));
}

VALUE rb_basic_vector_address(VALUE self) {
    BASIC_VECTOR();
    #if (SIZEOF_INTPTR_T == 4)
        return LONG2NUM((long) v->values);
    #elif (SIZEOF_INTPTR_T == 8)
        return LL2NUM((long long) v->values)
    #else
        return INT2NUM(0);
    #endif
}

VALUE rb_basic_vector_count(VALUE self) {
    BASIC_VECTOR();
    return INT2NUM(v->count);
}