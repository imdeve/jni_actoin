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

protected:
    JNIEnv *env;
    JNIThreadPool *pool;
    jobject  reponseCallback;
    void *   callbackParam;


protected:
    virtual std::string getResultType();
    virtual int onPreDo();
    virtual void onInPool(ThreadPool *threadPool);
    virtual int onDo();
    virtual int onPostDo();
    virtual int onRelease();
    void onExit();

private:
    void release();
public:
    void adapterReponseCallback(jobject javaCallback);
    void setReadyReponseCallbackParam(void * param);
    virtual ~BaseCallback();

protected:
    virtual void transformData( void * callbackParam);

};


#endif //TASKOK_BASECALLBACK_H
