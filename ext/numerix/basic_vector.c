
#include "basic_vector.h"

VALUE rb_cBasicVector;

void Init_basic_vector(VALUE outer) {
    rb_cBasicVector = rb_define_class_under(outer, "BasicVector", rb_cObject);


}

VALUE rb_basic_vector_alloc(VALUE klass) {
    BasicVector *v = ALLOC(BasicVector);
    v->count = 0;
    v->values = NULL;
    return NUMERIX_WRAP(klass, v);
}

VALUE rb_basic_vector_initialize(int argc, VALUE *argv, VALUE self) {
    BASIC_VECTOR();
    if (argc == 1)
    {
        int count = NUM2INT(argv[0]);
        if (count < 2)
        {
            rb_raise(rb_eArgError, "vector size must be 2 or greater");
            return Qnil;
        }
        v->count = count;
        v->values = (float*) ruby_xmalloc(sizeof(float) * count);
        memset(v->values, 0, count * sizeof(float));
    }
    else if (argc > 1)
    {
        v->count = argc;
        v->values = (float*) ruby_xmalloc(sizeof(float) * argc);
        for (int i = 0; i < argc; i++)
            v->values[i] = NUM2FLT(argv[i]);
    }
    else
        rb_raise(rb_eArgError, "no arguments given");

    return Qnil;
}