//
// Created by Administrator on 2019/9/11.
//

#ifndef JNI2_STRUTILS_H
#define JNI2_STRUTILS_H

#include <jni.h>
#include <string>

jstring ToJString(JNIEnv *env, const std::string &value);

char *_JString2CStr(JNIEnv *env, jstring jstr);
std::string ToCppString(JNIEnv *env, jstring value);

#endif //JNI2_STRUTILS_H
