//
// Created by Administrator on 2019/9/20.
//

#include "androidSdkOut.h"
#include "../task/JNIThreadPool.h"
#include <jni.h>

AndroidSdkCli::AndroidSdkCli() {

}

AndroidSdkCli& AndroidSdkCli::getInstance() {
    static AndroidSdkCli sdkcli;
    return sdkcli;
}

void AndroidSdkCli::initJNIEnv(JavaVM *javaVm) {
    this->jvm = javaVm;

}

void AndroidSdkCli::initRequestWorkerNum(int num) {
    this->requestWorkerNum = num;

}

int AndroidSdkCli::start() {
    callbacksWorkerPool.init(this->jvm,this->requestWorkerNum);
    return 0;
}
void AndroidSdkCli::sendRequestCallback(BaseCallback *callback) {
    this->callbacksWorkerPool.addTask(callback);
}