
#include "vector_base.h"

VALUE rb_cVectorBase;
VALUE rb_cVector2;
VALUE rb_cVector3;
VALUE rb_cVector4;
VALUE rb_cQuaternion;

void Init_vector_base(VALUE outer) {
    rb_cVectorBase = rb_define_class_under(outer, "VectorBase", rb_cNumerixStruct);
    rb_cVector2 = rb_define_class_under(outer, "Vector2", rb_cVectorBase);
    rb_cVector3 = rb_define_class_under(outer, "Vector3", rb_cVectorBase);
    rb_cVector4 = rb_define_class_under(outer, "Vector4", rb_cVectorBase);
    rb_cQuaternion = rb_define_class_under(outer, "Quaternion", rb_cNumerixStruct);

    rb_define_method(rb_cVector2, "x", rb_vector_base_x, 0);
    rb_define_method(rb_cVector2, "y", rb_vector_base_y, 0);
    rb_define_method(rb_cVector2, "x=", rb_vector_base_x_set, 1);
    rb_define_method(rb_cVector2, "y=", rb_vector_base_y_set, 1);

    rb_define_method(rb_cVector3, "x", rb_vector_base_x, 0);
    rb_define_method(rb_cVector3, "y", rb_vector_base_y, 0);
    rb_define_method(rb_cVector3, "z", rb_vector_base_z, 0);
    rb_define_method(rb_cVector3, "x=", rb_vector_base_x_set, 1);
    rb_define_method(rb_cVector3, "y=", rb_vector_base_y_set, 1);
    rb_define_method(rb_cVector3, "z=", rb_vector_base_z_set, 1);

    rb_define_method(rb_cVector4, "x", rb_vector_base_x, 0);
    rb_define_method(rb_cVector4, "y", rb_vector_base_y, 0);
    rb_define_method(rb_cVector4, "z", rb_vector_base_z, 0);
    rb_define_method(rb_cVector4, "w", rb_vector_base_w, 0);
    rb_define_method(rb_cVector4, "x=", rb_vector_base_x_set, 1);
    rb_define_method(rb_cVector4, "y=", rb_vector_base_y_set, 1);
    rb_define_method(rb_cVector4, "z=", rb_vector_base_z_set, 1);
    rb_define_method(rb_cVector4, "w=", rb_vector_base_w_set, 1);

    rb_define_method(rb_cQuaternion, "x", rb_vector_base_x, 0);
    rb_define_method(rb_cQuaternion, "y", rb_vector_base_y, 0);
    rb_define_method(rb_cQuaternion, "z", rb_vector_base_z, 0);
    rb_define_method(rb_cQuaternion, "w", rb_vector_base_w, 0);
    rb_define_method(rb_cQuaternion, "x=", rb_vector_base_x_set, 1);
    rb_define_method(rb_cQuaternion, "y=", rb_vector_base_y_set, 1);
    rb_define_method(rb_cQuaternion, "z=", rb_vector_base_z_set, 1);
    rb_define_method(rb_cQuaternion, "w=", rb_vector_base_w_set, 1);  

    rb_define_method(rb_cVectorBase, "map2", rb_vector_base_map, 0);
    rb_define_method(rb_cVectorBase, "map2!", rb_vector_base_map_bang, 0);
    rb_define_alias(rb_cVectorBase, "collect2", "map2");
    rb_define_alias(rb_cVectorBase, "collect2!", "map2!");
    
    rb_define_method(rb_cVectorBase, "**", rb_vector_base_pow, 1);
    rb_define_singleton_method(rb_cVectorBase, "pow", rb_vector_base_pow_s, 2);


    rb_include_module(rb_cVectorBase, rb_mEnumerable);
}

VALUE rb_vector_base_map(VALUE self) {
    struct RData *rdata = RDATA(self);
    int size = 0;

    if (NUMERIX_INHERIT_P(rdata->basic.klass, rb_cVector2))
        size = sizeof(float) * 2;
    else if (NUMERIX_INHERIT_P(rdata->basic.klass, rb_cVector3))
        size = sizeof(float) * 3;
    else if (NUMERIX_INHERIT_P(rdata->basic.klass, rb_cVector4))
        size = sizeof(float) * 4;

    float *flt = (float*) rdata->data;
    float *result = (float*) ruby_xmalloc(size);

    int count = size / sizeof(float);
    for (int i = 0; i < count; i++)
    {
        result[i] = NUM2FLT(rb_yield(DBL2NUM(flt[i])));
    }
    
    return NUMERIX_WRAP(rdata->basic.klass, result);
}

VALUE rb_vector_base_map_bang(VALUE self) {
    struct RData *rdata = RDATA(self);

    int count = 0;
    if (NUMERIX_INHERIT_P(rdata->basic.klass, rb_cVector2))
        count = 2;
    else if (NUMERIX_INHERIT_P(rdata->basic.klass, rb_cVector3))
        count = 3;
    else if (NUMERIX_INHERIT_P(rdata->basic.klass, rb_cVector4))
        count = 4;

    float *flt = (float*) rdata->data;

    for (int i = 0; i < count; i++)
    {
        flt[i] = NUM2FLT(rb_yield(DBL2NUM(flt[i])));
    }

    return self;
}

VALUE rb_vector_base_x(VALUE self) {
    VECTOR2();
    return DBL2NUM(v->x);
}

VALUE rb_vector_base_y(VALUE self) {
    VECTOR2();
    return DBL2NUM(v->y);
}

VALUE rb_vector_base_z(VALUE self) {
    VECTOR3();
    return DBL2NUM(v->z);
}

VALUE rb_vector_base_w(VALUE self) {
    VECTOR4();
    return DBL2NUM(v->w);
}

VALUE rb_vector_base_x_set(VALUE self, VALUE value) {
    VECTOR2();
    v->x = NUM2FLT(value);
    return value;
}

VALUE rb_vector_base_y_set(VALUE self, VALUE value) {
    VECTOR2();
    v->y = NUM2FLT(value);
    return value;
}

VALUE rb_vector_base_z_set(VALUE self, VALUE value) {
    VECTOR3();
    v->z = NUM2FLT(value);
    return value;
}

VALUE rb_vector_base_w_set(VALUE self, VALUE value) {
    VECTOR4();
    v->w = NUM2FLT(value);
    return value;
}

VALUE rb_vector_base_pow(VALUE self, VALUE exponent) {
    return rb_vector_base_pow_s(CLASS_OF(self), self, exponent);
}

static inline VALUE rb_vector_base_pow_s(VALUE klass, VALUE vector, VALUE exponent) {
    int count = 0;
    if (NUMERIX_INHERIT_P(klass, rb_cVector2))
        count = 2;
    else if (NUMERIX_INHERIT_P(klass, rb_cVector3))
        count = 3;
    else if (NUMERIX_INHERIT_P(klass, rb_cVector4))
        count = 4;
    
    float *v = RDATA(vector)->data;
    float *result = ruby_xmalloc(count * sizeof(float));
    float e = fabsf(NUM2FLT(exponent));

    for (int i = 0; i < count; i++)
        result[i] = powf(fabsf(v[i]), e);

    return NUMERIX_WRAP(klass, result);
}