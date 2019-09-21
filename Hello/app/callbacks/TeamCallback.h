//
// Created by Administrator on 2019/9/18.
//

#ifndef TASKOK_TEAMCALLBACK_H
#define TASKOK_TEAMCALLBACK_H


#include "BaseCallback.h"

/***
 *
 * 自定义回调类 每一个自定义回调类 对应了，上层的JAVA的RequestCallback
 *
 *   举例子:void getUserDetail(String account, RequestCallback<UserInfo> callback);
 * **/

class TeamCallback : public BaseCallback {
public:
    int id;

protected:
     std::string getResultType();
     int onPreDo();
     void onDestroy();
     virtual  int onRelease();
     int onDo();

public:
    ~TeamCallback();

protected:
    void transformData(void * callbackParam);
};


#endif //TASKOK_TEAMCALLBACK_H
