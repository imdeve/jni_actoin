
#include <stdio.h>
#include "com_jniclass_MsgMod.h"

JNIEXPORT void JNICALL Java_com_jniclass_MsgMod_sendMsg
 (JNIEnv * env, jobject ins, jobject req, jobject callback)
  {

    printf("hell world jni");


    return ;
  }