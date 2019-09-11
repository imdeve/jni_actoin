//
// Created by Administrator on 2019/9/11.
//
#include <string>
#include "strutils.h"
#include <jni.h>

// std::string转jstring
jstring ToJString(JNIEnv *env, const std::string &value)
{
    return env->NewStringUTF(value.c_str());
}

// jstring转std::string
std::string ToCppString(JNIEnv *env, jstring value)
{
    jboolean isCopy;
    const char *c_value = env->GetStringUTFChars(value, &isCopy);
    std::string result(c_value);
    if (isCopy == JNI_TRUE)
        env->ReleaseStringUTFChars(value, c_value);
    return result;
}

/**
* 将一个jstring转换成一个c语言的char* 类型.
*/
char *_JString2CStr(JNIEnv *env, jstring jstr)
{
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid =
            env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray)env->CallObjectMethod(
            jstr, mid, strencode); // String .getByte("GB2312");
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0)
    {
        rtn = (char *)malloc(alen + 1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}