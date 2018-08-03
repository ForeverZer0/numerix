#ifndef NUMERIX_STRUCTURE_H
#define NUMERIX_STRUCTURE_H 1

#include "common.h"

void Init_numerix_structure(VALUE outer);

VALUE rb_numerix_address(VALUE self);
VALUE rb_numerix_dump(int arc, VALUE *argv, VALUE self);
VALUE rb_numerix_dup(VALUE self);
VALUE rb_numerix_aref(VALUE self, VALUE index);
VALUE rb_numerix_aset(VALUE self, VALUE index, VALUE value);
VALUE rb_numerix_each(VALUE self);

static inline int rb_numerix_isize(VALUE klass);
VALUE rb_numerix_size(VALUE klass);
VALUE rb_numerix_load(VALUE klass, VALUE str);

#endif /* NUMERIX_STRUCTURE_H */