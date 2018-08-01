#ifndef NUMERIX_MATRIX4X4_H
#define NUMERIX_MATRIX4X4_H 1

#include "common.h"
#include "matrix_base.h"

#define MATRIX4X4() \
    Matrix4x4 *m;   \
    Data_Get_Struct(self, Matrix4x4, m)

#endif /* NUMERIX_MATRIX4X4_H */