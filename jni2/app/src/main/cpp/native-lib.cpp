#include <jni.h>
#include <string>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "native-lib.h"  //引入头文件...
//参数映射表
//这是在MainActivity中的native方法
static JNINativeMethod gMethods_MainActivity[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *) stringFromJNI},
        {"setString", "(Ljava/lang/String;)Ljava/lang/String;", (void *) setString},
};

//这是在HongBao中的native方法
static JNINativeMethod gMethods_HongBao[] = {
        {"add", "(II)I", (void *) add},
};

//实现在MainActivity类的两个方法stringFromJNI()    setString()
static jstring stringFromJNI(JNIEnv *env, jobject obj) {
    return env->NewStringUTF("欢迎来到jin的世界...");
}

jstring setString(JNIEnv *env, jobject instance, jstring str_) {

    return str_;
}

static jint add(JNIEnv *env, jclass clazz, jint x, jint y) {
    return x + y;
}

//找到MainActivity.java类
static int registerNatives(JNIEnv *engv) {
    jclass clazz;
    clazz = engv->FindClass("com/example/jni2/MainActivity");   //找到MainActivity类
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    //int len = sizeof(methods) / sizeof(methods[0]);
    if (engv->RegisterNatives(clazz, gMethods_MainActivity,
                              sizeof(gMethods_MainActivity) / sizeof(gMethods_MainActivity[0])) <
        0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

//注册 HongBao 中的native方法
static int registerNatives_HongBao(JNIEnv *engv) {
    jclass clazz;
    clazz = engv->FindClass("fj/clover/differentclassregister/HongBao");    //找到HongBao类

    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (engv->RegisterNatives(clazz, gMethods_HongBao,
                              sizeof(gMethods_HongBao) / sizeof(gMethods_HongBao[0])) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = -1;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }
    assert(env != NULL);
    //为了方便管理我们将不同java类中的native方法分别注册
    if (registerNatives(env) < 0) {  //注册HongBao类的native方法
        return result;
    }
  //  if (registerNatives_HongBao(env) < 0) {  //注册MainActivity类的native方法
  //      return result;
  //  }

    /*registerNatives(env);
    registerNatives_HongBao(env); */
    return JNI_VERSION_1_6;
}