//
// Created by Administrator on 2019/9/18.
//

#ifndef TASKOK_BASECALLBACK_H
#define TASKOK_BASECALLBACK_H

#include <string>
#include <jni.h>
#include "../task/Task.h"
#include "../task/JNIThreadPool.h"

/****
class JNIEnv;
class JNIThreadPool;
****/

/***
 * 自定义回调基类
 * 每一个自定义回调类 对应了，上层的JAVA的RequestCallback
******/




class BaseCallback :public Task {
    enum CallBackStatus{
        SUCCESS=0,
        FAIL =1
    };
protected:
    JNIEnv *env;
    JNIThreadPool *pool;
    jobject  reponseCallback;
    void *   callbackParam;
    CallBackStatus state;

protected:
    virtual std::string getResultType();
    virtual int onPreDo();
    virtual void onInPool(ThreadPool *threadPool);
    virtual int onDo();
    virtual int onPostDo();
    virtual int onRelease();
    void onExit();


    virtual void onSuccess()=0;
    virtual void onFail()=0;
    virtual jmethodID getSuccessMethodId();
    virtual jmethodID getFailMethodId();
    void setState(CallBackStatus state);


private:
    void release();
public:
    void adapterReponseCallback(jobject javaCallback);
    void setReadyReponseCallbackParam(void * param);
    virtual ~BaseCallback();


};


#endif //TASKOK_BASECALLBACK_H
