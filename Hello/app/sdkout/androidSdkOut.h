//
// Created by Administrator on 2019/9/20.
//

#ifndef TASKOK_ANDROIDSDKOUT_H
#define TASKOK_ANDROIDSDKOUT_H

#include "jni.h"

#include "../task/JNIThreadPool.h"
#include "../callbacks/BaseCallback.h"


class AndroidSdkCli {

private:
    int requestWorkerNum;
    JavaVM * jvm;
    JNIThreadPool callbacksWorkerPool;

private:
    AndroidSdkCli();
public:
    static AndroidSdkCli& getInstance();

      void initJNIEnv(JavaVM * javaVm);
      void initRequestWorkerNum(int num);
      int  start();

      void sendRequestCallback(BaseCallback * callback);

     // void listenData(int type,int type_u,void*data);


};


#endif //TASKOK_ANDROIDSDKOUT_H
