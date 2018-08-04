#ifndef NUMERIX_BASIC_VECTOR_H
#define NUMERIX_BASIC_VECTOR_H 1

#include "common.h"

#define BASIC_VECTOR() \
    BasicVector *v;    \
    Data_Get_Struct(self, BasicVector, v)

void Init_basic_vector(VALUE outer);
VALUE rb_basic_vector_alloc(VALUE klass);
VALUE rb_basic_vector_create(int argc, VALUE *argv, VALUE self);

#endif
