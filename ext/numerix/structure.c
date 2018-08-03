
#include "structure.h"

VALUE rb_cNumerixStruct;

#if RUBY_API_VERSION_MAJOR >= 2
    VALUE rb_numerix_cFiddlePointer;
#endif

void Init_numerix_structure(VALUE outer) {
    rb_cNumerixStruct = rb_define_class_under(outer, "Structure", rb_cObject);

    rb_define_method(rb_cNumerixStruct, "dup", rb_numerix_dup, 0);
    rb_define_method(rb_cNumerixStruct, "address", rb_numerix_address, 0);
    rb_define_method(rb_cNumerixStruct, "_dump", rb_numerix_dump, -1);
    rb_define_method(rb_cNumerixStruct, "[]", rb_numerix_aref, 1);
    rb_define_method(rb_cNumerixStruct, "[]=", rb_numerix_aset, 2);
    rb_define_method(rb_cNumerixStruct, "each", rb_numerix_each, 0);

    rb_define_singleton_method(rb_cNumerixStruct, "size", rb_numerix_size, 0);
    rb_define_singleton_method(rb_cNumerixStruct, "_load", rb_numerix_load, 1);
    rb_define_singleton_method(rb_cNumerixStruct, "unpack", rb_numerix_load, 1);

    rb_define_alias(rb_cNumerixStruct, "pack", "_dump");
    
    #if RUBY_API_VERSION_MAJOR >= 2
        rb_require("fiddle");
        VALUE fiddle = rb_const_get(rb_cObject, rb_intern("Fiddle"));
        rb_numerix_cFiddlePointer = rb_const_get(fiddle, rb_intern("Pointer"));
        rb_define_method(rb_cNumerixStruct, "ptr", rb_numerix_fiddle_ptr, 0);
    #endif
}

#if RUBY_API_VERSION_MAJOR >= 2

    VALUE rb_numerix_fiddle_ptr(VALUE self) {
        // Get basic data about the struct
        struct RData *rdata = RDATA(self);
        VALUE *args = xmalloc(sizeof(VALUE) * 2);
        // Set the platform pointer-size address
        #if SIZEOF_INTPTR_T == 4
            args[0] = LONG2NUM((long) rdata->data);
        #elif SIZEOF_INTPTR_T == 8
            args[0] = LL2NUM((long long) rdata->data);
        #else 
            args[0] = INT2NUM(0);
        #endif
        // Get size of structure
        int size = rb_numerix_isize(rdata->basic.klass);
        args[1] = INT2NUM(size);
        VALUE ptr = rb_class_new_instance(2, args, rb_numerix_cFiddlePointer);
        xfree(args);
        return ptr;
    }

#endif

VALUE rb_numerix_each(VALUE self) {
    struct RData *rdata = RDATA(self);
    int count = rb_numerix_isize(rdata->basic.klass) / sizeof(float);

    volatile VALUE str = self;

    RETURN_SIZED_ENUMERATOR(str, 0, 0, count);

    float *flt = (float*) rdata->data;
    for (int i = 0; i < count; i++)
        rb_yield(DBL2NUM(flt[i]));

    return str;
}

VALUE rb_numerix_aref(VALUE self, VALUE index)
{
    struct RData *rdata = RDATA(self);
    int max = rb_numerix_isize(rdata->basic.klass) / sizeof(float);
    int i = NUM2INT(index);

    if (i < 0 || i >= max)
        return Qnil;
    
    float *flt = (float*) rdata->data;
    return DBL2NUM(flt[i]);
}

VALUE rb_numerix_aset(VALUE self, VALUE index, VALUE value) {
    struct RData *rdata = RDATA(self);
    int max = rb_numerix_isize(rdata->basic.klass) / sizeof(float);
    int i = NUM2INT(index);

    if (i >= 0 || i < max)
    {
        float *flt = (float*) rdata->data;
        flt[i] = NUM2FLT(value);
    }

    return value;
}

VALUE rb_numerix_dup(VALUE self) {
    struct RData *rdata = RDATA(self);
    int size = rb_numerix_isize(rdata->basic.klass);
    void *data = ruby_xmalloc(size);
    memcpy(data, rdata->data, size);
    return NUMERIX_WRAP(rdata->basic.klass, data);
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