#include <jni.h>
#include <string>
#include <iostream>
#include "clog/clog.h"

using namespace std;

void doJavaLog(std::string type,std::string content){
    jclass SdkCliClaz = (genv)->FindClass("com/wenwp/threadpoolcallback/SdkCli");
    jmethodID  m = genv->GetStaticMethodID(SdkCliClaz,"doLog","(Ljava/lang/String;Ljava/lang/String;)V");
    genv->CallStaticVoidMethod(SdkCliClaz,m,genv->NewStringUTF(type.c_str()),genv->NewStringUTF(content.c_str()));

}


extern "C" JNIEXPORT jstring JNICALL
Java_com_wenwp_threadpoolcallback_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_wenwp_threadpoolcallback_SdkCli_sendCallback(JNIEnv *env, jclass clazz) {

  //  jmethodID  m = env->GetStaticMethodID(clazz,"onSendCallback","()V");
  //  env->CallStaticVoidMethod(clazz,m);

    doJavaLog("err","sendCallback ");

}





JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm,void* reserved){
    genv = 0;
    if(vm->GetEnv((void**)&genv,JNI_VERSION_1_6)!=JNI_OK){
        return -1;
    }
   // initSdkJniEnv(vm);
    return JNI_VERSION_1_6;
}
/*****
public void success(T t);
public void failed(String errorMsg);
 ****/
extern "C"
JNIEXPORT void JNICALL
Java_com_wenwp_threadpoolcallback_SdkCli_addCallbackTask(JNIEnv *env, jclass clazz,
                                                     jobject request) {

//    doJavaLog("err","_addCallbackTask ");
    jclass sdkcls = env->GetObjectClass(request);

    jmethodID  onSuccess = env->GetMethodID(sdkcls,"success","(Ljava/lang/String;)V");

    std::string result= "result from sdk";
    env->CallVoidMethod(request,onSuccess,env->NewStringUTF(result.c_str()));

}