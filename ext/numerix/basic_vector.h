#ifndef NUMERIX_BASIC_VECTOR_H
#define NUMERIX_BASIC_VECTOR_H 1

#include "common.h"

#define BASIC_VECTOR() \
    BasicVector *v;    \
    Data_Get_Struct(self, BasicVector, v)

#define BASIC_VECTOR_RESULT()                 \
    BASIC_VECTOR();                           \
    BasicVector *result = ALLOC(BasicVector); \
    result->count = v->count;                 \
    result->values = ruby_xmalloc(sizeof(float) * v->count)

#define BASIC_VECTOR_OTHER_RESULT()                       \
    BasicVector *v1, *v2, *result;                        \
    Data_Get_Struct(self, BasicVector, v1);               \
    Data_Get_Struct(other, BasicVector, v2);              \
    result = ALLOC(BasicVector);                          \
    if (v1->count != v2->count)                           \
        rb_raise(rb_eArgError, "unequal length vectors"); \
    int count = v1->count;                                \
    result->count = count;                                \
    result->values = ruby_xmalloc(sizeof(float) * count)

void Init_basic_vector(VALUE outer);
VALUE rb_basic_vector_alloc(VALUE klass);

// Instance
VALUE rb_basic_vector_length(VALUE self);
VALUE rb_basic_vector_length_squared(VALUE self);
VALUE rb_basic_vector_normalize(VALUE self);
VALUE rb_basic_vector_normalize_bang(VALUE self);

VALUE rb_basic_vector_add(VALUE self, VALUE other);
VALUE rb_basic_vector_subtract(VALUE self, VALUE other);
VALUE rb_basic_vector_multiply(VALUE self, VALUE other);
VALUE rb_basic_vector_divide(VALUE self, VALUE other);
VALUE rb_basic_vector_negate(VALUE self, VALUE other);
VALUE rb_basic_vector_equal(VALUE self, VALUE other);

VALUE rb_basic_vector_size(VALUE self);
VALUE rb_basic_vector_address(VALUE self);
VALUE rb_basic_vector_count(VALUE self);

// Class
VALUE rb_basic_vector_create(int argc, VALUE *argv, VALUE self);
#endif
