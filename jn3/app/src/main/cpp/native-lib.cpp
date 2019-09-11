#include <jni.h>
#include <string>

#include "utils/strutils.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jn3_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}




//实现在MainActivity类的两个方法stringFromJNI()    setString()
static jstring stringFromJNI(JNIEnv *env, jobject obj) {
    return env->NewStringUTF("欢迎来到jin的世界...");
}

jstring setString(JNIEnv *env, jobject instance, jstring str_) {


    char * str = _JString2CStr(env,str_);
    char buffer[1024]={0};
    sprintf(buffer," hahaha :%s",str);
    std::string s = buffer;

    printf("set strnig :%s",str);
    return ToJString(env,s);
}


//参数映射表
//这是在MainActivity中的native方法
static JNINativeMethod gMethods_MainActivity[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *) stringFromJNI},
        {"setString", "(Ljava/lang/String;)Ljava/lang/String;", (void *) setString},
};


//找到MainActivity.java类
static int registerNatives(JNIEnv *engv) {
    jclass clazz;
    clazz = engv->FindClass("com/example/jn3/MainActivity");   //找到MainActivity类
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


JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = -1;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }
    assert(env != NULL);
    //为了方便管理我们将不同java类中的native方法分别注册
    if (registerNatives(env) < 0) {
        return result;
    }

    return JNI_VERSION_1_6;
}
