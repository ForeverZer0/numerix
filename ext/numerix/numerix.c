#include "numerix.h"

VALUE rb_mNumerix;
VALUE rb_eNumerixError;

void Init_numerix(void) {
    rb_mNumerix = rb_define_module("Numerix");
    rb_eNumerixError = rb_define_class_under(rb_mNumerix, "NumerixError", rb_eStandardError);

    Init_basic_vector(rb_mNumerix);
    Init_numerix_structure(rb_mNumerix);
    Init_vector_base(rb_mNumerix);
    Init_matrix_base(rb_mNumerix);
    Init_vector2(rb_mNumerix);
    Init_vector3(rb_mNumerix);
    Init_vector4(rb_mNumerix);
    Init_matrix3x2(rb_mNumerix);
    Init_matrix4x4(rb_mNumerix);
    Init_quaternion(rb_mNumerix);
    Init_plane(rb_mNumerix);

    rb_define_const(rb_mNumerix, "SIZEOF_VECTOR2", INT2NUM(sizeof(Vector2)));
    rb_define_const(rb_mNumerix, "SIZEOF_VECTOR3", INT2NUM(sizeof(Vector3)));
    rb_define_const(rb_mNumerix, "SIZEOF_VECTOR4", INT2NUM(sizeof(Vector4)));
    rb_define_const(rb_mNumerix, "SIZEOF_MATRIX3X2", INT2NUM(sizeof(Matrix3x2)));
    rb_define_const(rb_mNumerix, "SIZEOF_MATRiX4X4", INT2NUM(sizeof(Matrix4x4)));
    rb_define_const(rb_mNumerix, "SIZEOF_QUATERNION", INT2NUM(sizeof(Quaternion)));
    rb_define_const(rb_mNumerix, "SIZEOF_PLANE", INT2NUM(sizeof(Plane)));
}

VALUE rb_numerix_abstract_initialize(VALUE self) {
    rb_raise(rb_eNumerixError, "cannot create instance of abstract class %s", rb_class2name(CLASS_OF(self)));
}
