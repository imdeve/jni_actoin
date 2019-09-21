//
// Created by Administrator on 2019/9/22.
//

#include "BaseCallbackObject.h"
#include "../../../../../work/android_env_soft/android-ndk-r16b/sysroot/usr/include/jni.h"


jobject BaseCallbackObject::transformData(void *callbackParam) {

    return 0;
}


int BaseCallbackObject::onPreDo() {
    BaseCallback::onPostDo();


}

void BaseCallbackObject::onSuccess() {

}

void BaseCallbackObject::onFail() {


}

jmethodID BaseCallbackObject::getFailMethodId() {

}

jmethodID BaseCallbackObject::getSuccessMethodId() {

}
