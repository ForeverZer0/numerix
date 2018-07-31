#include "numerix.h"

VALUE rb_mNumerix;

void Init_numerix(void) {
  rb_mNumerix = rb_define_module("Numerix");

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

}
