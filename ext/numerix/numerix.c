#include "numerix.h"

VALUE rb_mNumerix;

void
Init_numerix(void)
{
  rb_mNumerix = rb_define_module("Numerix");
}
