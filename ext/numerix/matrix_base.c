
#include "matrix_base.h"

VALUE rb_cMatrixBase;
VALUE rb_cMatrix3x2;
VALUE rb_cMatrix4x4;

void Init_matrix_base(VALUE outer) {
    rb_cMatrixBase = rb_define_class_under(outer, "MatrixBase", rb_cNumerixStruct);
    rb_cMatrix3x2 = rb_define_class_under(outer, "Matrix3x2", rb_cMatrixBase);
    rb_cMatrix4x4 = rb_define_class_under(outer, "Matrix4x4", rb_cMatrixBase);

    rb_define_method(rb_cMatrix3x2, "m11", rb_matrix3x2_m11, 0);
    rb_define_method(rb_cMatrix3x2, "m12", rb_matrix3x2_m12, 0);
    rb_define_method(rb_cMatrix3x2, "m21", rb_matrix3x2_m21, 0);
    rb_define_method(rb_cMatrix3x2, "m22", rb_matrix3x2_m22, 0);
    rb_define_method(rb_cMatrix3x2, "m31", rb_matrix3x2_m31, 0);
    rb_define_method(rb_cMatrix3x2, "m32", rb_matrix3x2_m32, 0);

    rb_define_method(rb_cMatrix3x2, "m11=", rb_matrix3x2_m11_set, 1);
    rb_define_method(rb_cMatrix3x2, "m12=", rb_matrix3x2_m12_set, 1);
    rb_define_method(rb_cMatrix3x2, "m21=", rb_matrix3x2_m21_set, 1);
    rb_define_method(rb_cMatrix3x2, "m22=", rb_matrix3x2_m22_set, 1);
    rb_define_method(rb_cMatrix3x2, "m31=", rb_matrix3x2_m31_set, 1);
    rb_define_method(rb_cMatrix3x2, "m32=", rb_matrix3x2_m32_set, 1);

    rb_define_method(rb_cMatrix4x4, "m11", rb_matrix4x4_m11, 0);
    rb_define_method(rb_cMatrix4x4, "m12", rb_matrix4x4_m12, 0);
    rb_define_method(rb_cMatrix4x4, "m13", rb_matrix4x4_m13, 0);
    rb_define_method(rb_cMatrix4x4, "m14", rb_matrix4x4_m14, 0);
    rb_define_method(rb_cMatrix4x4, "m21", rb_matrix4x4_m21, 0);
    rb_define_method(rb_cMatrix4x4, "m22", rb_matrix4x4_m22, 0);
    rb_define_method(rb_cMatrix4x4, "m23", rb_matrix4x4_m23, 0);
    rb_define_method(rb_cMatrix4x4, "m24", rb_matrix4x4_m24, 0);
    rb_define_method(rb_cMatrix4x4, "m31", rb_matrix4x4_m31, 0);
    rb_define_method(rb_cMatrix4x4, "m32", rb_matrix4x4_m32, 0);
    rb_define_method(rb_cMatrix4x4, "m33", rb_matrix4x4_m33, 0);
    rb_define_method(rb_cMatrix4x4, "m34", rb_matrix4x4_m34, 0);
    rb_define_method(rb_cMatrix4x4, "m41", rb_matrix4x4_m41, 0);
    rb_define_method(rb_cMatrix4x4, "m42", rb_matrix4x4_m42, 0);
    rb_define_method(rb_cMatrix4x4, "m43", rb_matrix4x4_m43, 0);
    rb_define_method(rb_cMatrix4x4, "m44", rb_matrix4x4_m44, 0);

    rb_define_method(rb_cMatrix4x4, "m11=", rb_matrix4x4_m11_set, 1);
    rb_define_method(rb_cMatrix4x4, "m12=", rb_matrix4x4_m12_set, 1);
    rb_define_method(rb_cMatrix4x4, "m13=", rb_matrix4x4_m13_set, 1);
    rb_define_method(rb_cMatrix4x4, "m14=", rb_matrix4x4_m14_set, 1);
    rb_define_method(rb_cMatrix4x4, "m21=", rb_matrix4x4_m21_set, 1);
    rb_define_method(rb_cMatrix4x4, "m22=", rb_matrix4x4_m22_set, 1);
    rb_define_method(rb_cMatrix4x4, "m23=", rb_matrix4x4_m23_set, 1);
    rb_define_method(rb_cMatrix4x4, "m24=", rb_matrix4x4_m24_set, 1);
    rb_define_method(rb_cMatrix4x4, "m31=", rb_matrix4x4_m31_set, 1);
    rb_define_method(rb_cMatrix4x4, "m32=", rb_matrix4x4_m32_set, 1);
    rb_define_method(rb_cMatrix4x4, "m33=", rb_matrix4x4_m33_set, 1);
    rb_define_method(rb_cMatrix4x4, "m34=", rb_matrix4x4_m34_set, 1);
    rb_define_method(rb_cMatrix4x4, "m41=", rb_matrix4x4_m41_set, 1);
    rb_define_method(rb_cMatrix4x4, "m42=", rb_matrix4x4_m42_set, 1);
    rb_define_method(rb_cMatrix4x4, "m43=", rb_matrix4x4_m43_set, 1);
    rb_define_method(rb_cMatrix4x4, "m44=", rb_matrix4x4_m44_set, 1);
}

VALUE rb_matrix3x2_m11(VALUE self) {
    MATRIX3X2();
    return DBL2NUM(m->m11);
}

VALUE rb_matrix3x2_m12(VALUE self) {
    MATRIX3X2();
    return DBL2NUM(m->m12);
}

VALUE rb_matrix3x2_m21(VALUE self) {
    MATRIX3X2();
    return DBL2NUM(m->m21);
}

VALUE rb_matrix3x2_m22(VALUE self) {
    MATRIX3X2();
    return DBL2NUM(m->m22);
}

VALUE rb_matrix3x2_m31(VALUE self) {
    MATRIX3X2();
    return DBL2NUM(m->m31);
}

VALUE rb_matrix3x2_m32(VALUE self) {
    MATRIX3X2();
    return DBL2NUM(m->m32);
}

VALUE rb_matrix4x4_m11(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m11);
}

VALUE rb_matrix4x4_m12(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m12);
}

VALUE rb_matrix4x4_m13(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m13);
}

VALUE rb_matrix4x4_m14(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m14);
}

VALUE rb_matrix4x4_m21(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m21);
}

VALUE rb_matrix4x4_m22(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m22);
}

VALUE rb_matrix4x4_m23(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m23);
}

VALUE rb_matrix4x4_m24(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m24);
}

VALUE rb_matrix4x4_m31(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m31);
}

VALUE rb_matrix4x4_m32(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m32);
}

VALUE rb_matrix4x4_m33(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m33);
}

VALUE rb_matrix4x4_m34(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m34);
}

VALUE rb_matrix4x4_m41(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m41);
}

VALUE rb_matrix4x4_m42(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m42);
}

VALUE rb_matrix4x4_m43(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m43);
}

VALUE rb_matrix4x4_m44(VALUE self) {
    MATRIX4X4();
    return DBL2NUM(m->m44);
}

VALUE rb_matrix3x2_m11_set(VALUE self, VALUE value) {
    MATRIX3X2();
    m->m11 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix3x2_m12_set(VALUE self, VALUE value) {
    MATRIX3X2();
    m->m12 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix3x2_m21_set(VALUE self, VALUE value) {
    MATRIX3X2();
    m->m21 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix3x2_m22_set(VALUE self, VALUE value) {
    MATRIX3X2();
    m->m22 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix3x2_m31_set(VALUE self, VALUE value) {
    MATRIX3X2();
    m->m31 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix3x2_m32_set(VALUE self, VALUE value) {
    MATRIX3X2();
    m->m32 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m11_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m11 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m12_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m12 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m13_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m13 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m14_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m14 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m21_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m21 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m22_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m22 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m23_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m23 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m24_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m24 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m31_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m31 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m32_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m32 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m33_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m33 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m34_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m34 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m41_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m41 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m42_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m42 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m43_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m43 = NUM2FLT(value);
    return value;
}

VALUE rb_matrix4x4_m44_set(VALUE self, VALUE value) {
    MATRIX4X4();
    m->m44 = NUM2FLT(value);
    return value;
}