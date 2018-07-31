
#include "plane.h"

VALUE rb_cPlane;

void Init_plane(VALUE outer) {
    rb_cPlane = rb_define_class_under(outer, "Plane", rb_cNumerixStruct);
}