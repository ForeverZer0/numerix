module Numerix
  class MatrixBase < Structure

=begin
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

    rb_define_method(rb_cMatrixBase, "map2", rb_matrix_base_map, 0);
    rb_define_method(rb_cMatrixBase, "map2!", rb_matrix_base_map_bang, 0);

    rb_define_method(rb_cMatrixBase, "**", rb_matrix_base_pow, 1);
    rb_define_singleton_method(rb_cMatrixBase, "pow", rb_matrix_base_pow_s, 2);
=end
  end
end