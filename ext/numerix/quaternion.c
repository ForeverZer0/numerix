
#include "quaternion.h"

VALUE rb_cQuaternion;

void Init_quaternion(VALUE outer) {
    rb_cQuaternion = rb_define_class_under(outer, "Quaternion", rb_cNumerixStruct);
}