//
// Created by Administrator on 2019/9/19.
//

#include "JNIThreadPool.h"
#include <stdlib.h>
#include <pthread.h>
JNIThreadPool::JNIThreadPool() {

}

void JNIThreadPool::init(JavaVM* jvm,int numWorkers) {
     this->jvm = jvm;
     ThreadPool::init(numWorkers);
}

void JNIThreadPool::onWorkThreadEnter(workqueue_t *wq, int wid) {
    ThreadPool::onWorkThreadEnter(wq,wid);

    JNIEnv *env =0;
    if (jvm!=0)
    {
        jvm->AttachCurrentThread(&env, 0);
        worker_t *worker= this->queryWorker(wid);
        worker->userData = env;
    }
}

void JNIThreadPool::onWorkThreadExit(workqueue_t *wq, int wid) {
    ThreadPool::onWorkThreadExit(wq,wid);
    worker_t *worker= this->queryWorker(wid);
    worker->userData = 0;
    if (jvm!=0)
    {
        jvm->DetachCurrentThread();
    }
}

JNIEnv* JNIThreadPool::findEnv(int wid) {
   worker_t *w= queryWorker(wid);
   if (w!=0)
   {
       return (JNIEnv*)w->userData;
   }
    return 0;
}

JNIThreadPool::~JNIThreadPool() {

}