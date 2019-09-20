//
// Created by Administrator on 2019/9/18.
//
#include <iostream>
#include "BaseCallback.h"
#include  "../task/JNIThreadPool.h"
std::string BaseCallback::getResultType() {

   // this->env->GetObjectClass("");
    return "";
}

 void BaseCallback::adapterReponseCallback(jobject javaCallback) {
    this->reponseCallback =  javaCallback;
}

//每一个 callback都有自己的接收参数处理;可以重写
void BaseCallback::setReadyReponseCallbackParam(void *param) {
        this->callbackParam = param;
}

void BaseCallback::onInPool(ThreadPool *threadPool) {
     this->pool = (JNIThreadPool*)threadPool;
}

int BaseCallback::onPreDo() {
    Task::onPreDo();
    JNIEnv* e= this->pool->findEnv(this->getWid());
    this->env= e;
    //转换数据
    this->transformData(this->callbackParam);
    return 0;
}

void BaseCallback::transformData( void *callbackParam) {

}

int BaseCallback::onDo() {
    Task::onDo();
   // std::cout << "BaseCallback::onDo;" << std::endl;
    return 0;
}


void BaseCallback::release() {
    this->onRelease();
}

int BaseCallback::onRelease() {
  //  std::cout << "BaseCallback::~onRelease()  ..." << std::endl;
    return 0;
}

int BaseCallback::onPostDo() {
    Task::onPostDo();


    return 0;
}
void BaseCallback::onExit() {
    //释放自己资源
    this->release();
    //调用父类释放
     Task::onExit();
     //最终内存释放
 //    std::cout << "BaseCallback onExit..xxxxxxxxxxxxxxxxxxxxxxxxxxxxx.." << std::endl;
     delete this;
}

BaseCallback::~BaseCallback() {

    // std::cout << "BaseCallback::~BaseCallback() " << std::endl;
}
