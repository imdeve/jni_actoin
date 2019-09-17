//
// Created by Administrator on 2019/9/16.
//

#include <stdio.h>
#include "com_model_classes_MsgMod.h"
JNIEXPORT jint JNICALL Java_com_example_myjni_classes_MsgMod_sendMsg
  (JNIEnv * env, jobject msgModThis, jobject req , jobject callback)
  {
    printf("sendmsg... \n" );
    return (jint)0;
  }