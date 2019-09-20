//
// Created by Administrator on 2019/9/20.
//

#ifndef THREADPOOLCALLBACK_CLOG_H
#define THREADPOOLCALLBACK_CLOG_H

#include <jni.h>
#include <string>

JNIEnv *genv;
void doJavaLog(std::string type,std::string content);


#endif //THREADPOOLCALLBACK_CLOG_H
