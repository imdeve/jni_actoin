//
// Created by Administrator on 2019/9/11.
//
#include <jni.h>
#ifndef DIFFERENTCLASSREGISTER_NATIVE_LIB_H
#define DIFFERENTCLASSREGISTER_NATIVE_LIB_H


static jstring stringFromJNI(JNIEnv *env, jobject jobject1);   //so层获取一个字符串

jstring setString(JNIEnv *env, jobject instance,jstring str);//so层获取带参的字符串

static jint add(JNIEnv *env, jclass clazz,jint x,jint y);//HongBao类的native方法

#endif //JNI2_NATIVE_LIB_H
