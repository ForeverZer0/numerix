
#include "structure.h"

VALUE rb_cNumerixStruct;

void Init_numerix_structure(VALUE outer) {
    rb_cNumerixStruct = rb_define_class_under(outer, "Structure", rb_cObject);
}