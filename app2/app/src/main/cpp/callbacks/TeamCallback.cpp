//
// Created by Administrator on 2019/9/18.
//

#include "TeamCallback.h"
#include <iostream>

using  namespace std;

std::string TeamCallback::getResultType() {

    return "LTeamCallbackclaspath";
}

int TeamCallback::onPreDo() {
    BaseCallback::onPreDo();
    //自己的事情
   // cout <<"TeamCallback::onPreDo...."<<endl;

    return 0;
}

//解析sdk的数据，转换为java的 callback接收的参数类型
//举例::RequestCallback<UserInfo> callback
//将传入的void *param 转成 UserInfo data的数据




void TeamCallback::transformData(void * callbackParam) {
    ///void * responseData = this->callbackParam;



}

/****
 *
 * 通知产生后的回调函数
 * @param t 事件参数
public void success(T t);
public void failed(String errorMsg);
 * ***/

int TeamCallback::onDo() {
    //process resp-callback to java

//if success
   jclass  responseclass = env->GetObjectClass(this->reponseCallback);
   jmethodID  successMethodId = this->env->GetMethodID(responseclass,"success", "(Ljava/lang/String;)V");
    env->CallVoidMethod(this->reponseCallback,successMethodId);

    //if failed
    jmethodID failedMethodId = this->env->GetMethodID(responseclass,"failed", "(Ljava/lang/String;)V");
    env->CallVoidMethod(this->reponseCallback,failedMethodId);
    return 0;
}

/****
static int atomic_int_inc(int* addr,int delta){
    //based on asm : xaddl delta,[ptr]
    int ret = 0;
// input output sys arch
    __asm__ __volatile__(
    "lock; xaddl %2,%1;"
    :"=a"(ret)
    :"m"(*addr) ,"a"(delta)
    :"memory","cc"

    );
    return ret;

}
****/

static int c=0;
int TeamCallback::onRelease() {
    BaseCallback::onRelease();
    //atomic_int_inc(&c,1);
    cout << "TeamCallback::onRelease"<<  this->id << " wid:" << this->getWid() <<endl;
    return 0;
}

TeamCallback::~TeamCallback() {
  //  cout <<"TeamCallback::~TeamCallback..~~~~~~~~.."<<endl;
}