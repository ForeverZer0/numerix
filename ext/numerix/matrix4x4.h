#ifndef NUMERIX_MATRIX4X4_H
#define NUMERIX_MATRIX4X4_H 1

#include "common.h"
#include "matrix_base.h"

void Init_matrix4x4(VALUE outer);

VALUE rb_matrix4x4_invert_s(VALUE klass, VALUE matrix);

#endif /* NUMERIX_MATRIX4X4_H */