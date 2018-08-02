
#include "structure.h"

VALUE rb_cNumerixStruct;

void Init_numerix_structure(VALUE outer) {
    rb_cNumerixStruct = rb_define_class_under(outer, "Structure", rb_cObject);
    rb_define_method(rb_cNumerixStruct, "address", rb_numerix_address, 0);
    rb_define_method(rb_cNumerixStruct, "_dump", rb_numerix_dump, -1);

    rb_define_singleton_method(rb_cNumerixStruct, "size", rb_numerix_size, 0);
    rb_define_singleton_method(rb_cNumerixStruct, "_load", rb_numerix_load, 1);

    rb_define_alias(rb_cNumerixStruct, "pack", "_dump");
    rb_define_alias(rb_cNumerixStruct, "unpack", "_load");
}

VALUE rb_numerix_address(VALUE self) {
    void *address = RDATA(self)->data;
    #if SIZEOF_INTPTR_T == 4
        return LONG2NUM((long) address);
    #elif SIZEOF_INTPTR_T == 8
        return LL2NUM((long long) address);
    #else 
        return INT2NUM(0);
    #endif
}

static inline int rb_numerix_isize(VALUE klass) {
    if (NUMERIX_INHERIT_P(klass, rb_cVector2))
        return sizeof(Vector2);
    if (NUMERIX_INHERIT_P(klass, rb_cVector3))
        return sizeof(Vector3);
    if (NUMERIX_INHERIT_P(klass, rb_cVector4))
        return sizeof(Vector4);
    if (NUMERIX_INHERIT_P(klass, rb_cMatrix3x2))
        return sizeof(Matrix3x2);
    if (NUMERIX_INHERIT_P(klass, rb_cMatrix4x4))
        return sizeof(Matrix4x4);
    if (NUMERIX_INHERIT_P(klass, rb_cPlane))
        return sizeof(Plane);
    if (NUMERIX_INHERIT_P(klass, rb_cQuaternion))
        return sizeof(Quaternion);
    return 0;
}

VALUE rb_numerix_size(VALUE klass) {
    int size = rb_numerix_isize(klass);
    return INT2NUM(size);
}

VALUE rb_numerix_dump(int arc, VALUE *argv, VALUE self) {
    int size = rb_numerix_isize(CLASS_OF(self));
    VALUE str = rb_str_new(NULL, size);
    void *data = RDATA(self)->data;
    memcpy(RSTRING_PTR(str), data, size);
    return str;
}

VALUE rb_numerix_load(VALUE klass, VALUE str) {
    int size = rb_numerix_isize(klass);
    void *data = ruby_xmalloc(size);
    memcpy(data, RSTRING_PTR(str), size);
    return NUMERIX_WRAP(klass, data);
}