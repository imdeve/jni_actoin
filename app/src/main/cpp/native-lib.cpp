#include <jni.h>
#include <string>


static JavaVM* jvm;


extern "C" JNIEXPORT jstring JNICALL
Java_com_wenwp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}





JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm,void* reserved){
    JNIEnv *env;
    jvm = vm;
    if(vm->GetEnv((void**)&env,JNI_VERSION_1_6)!=JNI_OK){
        return -1;
    }
    return JNI_VERSION_1_6;
}
