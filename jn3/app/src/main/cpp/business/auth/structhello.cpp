#include <stdio.h>
#include <stdlib.h>
#include <jni.h>

#include "structhello.h"
#include "../../utils/strutils.h"


//硬盘信息
struct DiskInfo
{
    char name[256];
    int serial;
};

//输入常用的数值类型 Boolean,Byte,Char,Short,Int,Float,Double
static void  displayParms(JNIEnv *env, jobject obj, jstring s, jint i, jboolean b)
{
        const char* szStr = (env)->GetStringUTFChars(s, 0);
        printf("String = [%s]\n", szStr);
        printf("int = %d\n", (int)i);
        printf("boolean = %s\n", (b == JNI_TRUE ? "true" : "false"));
        (env)->ReleaseStringUTFChars(s, szStr);
}

//调用一个静态方法,只有一个简单类型输出
static jint  add(JNIEnv *env, jobject, jint a, jint b)
{
        int rtn = (int)(a + b);
        return (jint)rtn;
}

//输入一个数组,这里输入的是一个Boolean类型的数组
static void setArray(JNIEnv *env, jobject, jbooleanArray ba)
{
    jboolean* pba = (env)->GetBooleanArrayElements(ba, 0);
    jsize len = (env)->GetArrayLength(ba);
    // change even array elements
    for(int i = 0; i < len; i += 2)
    {
    pba[i] = JNI_FALSE;  //JNI_FALSE是在jni.h中定义的
    printf("boolean = %s\n", (pba[i] == JNI_TRUE ? "true" : "false"));
    }
    (env)->ReleaseBooleanArrayElements(ba, pba, 0);
}

////返回一个字符串数组
static  jobjectArray  getStringArray(JNIEnv *env, jobject)
{
    jstring      str;
    jobjectArray args = 0;
    jsize        len = 5;
    const char* sa[] = { "Hello,", "world!", " JNI", " is", " fun" };
    //int          i=0;
    args = (env)->NewObjectArray(len, (env)->FindClass("java/lang/String"), 0);
    for(int i = 0; i < len; i++)
    {
        str = (env)->NewStringUTF(sa[i]);
        (env)->SetObjectArrayElement(args, i, str);
    }
    return args;
}

//返回一个结构,这里返回一个硬盘信息的简单结构类型
static jobject getStruct(JNIEnv *env, jobject obj)
{
        /* 下面为获取到Java中对应的实例类中的变量*/

        //获取Java中的实例类
        jclass objectClass = (env)->FindClass("com/example/jn3/DiskInfo");
        //获取类中每一个变量的定义
        //名字
        jfieldID str = (env)->GetFieldID(objectClass, "name", "Ljava/lang/String;");
        //序列号
        jfieldID ival = (env)->GetFieldID(objectClass, "serial", "I");

        //给每一个实例的变量赋值
        (env)->SetObjectField(obj, str, (env)->NewStringUTF("my name is D:"));
        (env)->SetShortField(obj, ival, 10);

        return obj;
}

//返回一个结构数组，返回一个硬盘信息的结构数组
static jobjectArray  getStructArray(JNIEnv *env, jobject _obj)
{
    //申明一个object数组
    jobjectArray args = 0;
    //数组大小
    jsize        len = 5;
    //获取object所属类,一般为ava/lang/Object就可以了
    jclass objClass = (env)->FindClass("java/lang/Object");
    //新建object数组
    args = (env)->NewObjectArray(len, objClass, 0);
    /* 下面为获取到Java中对应的实例类中的变量*/

    //获取Java中的实例类
    jclass objectClass = (env)->FindClass("com/example/jn3/DiskInfo");
    //获取类中每一个变量的定义
    //名字
    jfieldID str = (env)->GetFieldID(objectClass, "name", "Ljava/lang/String;");
    //序列号
    jfieldID ival = (env)->GetFieldID(objectClass, "serial", "I");
    //给每一个实例的变量付值，并且将实例作为一个object，添加到objcet数组中
    for(int  i = 0; i < len; i++)
    {
    //给每一个实例的变量付值
    std::string msg = "我的磁盘名字是 D:";
    jstring jstr = ToJString(env,msg);


    //(env)->SetObjectField(_obj,str,(env)->NewStringUTF("my name is D:"));
    (env)->SetObjectField(_obj, str, jstr);
    (env)->SetShortField(_obj, ival, 10);

    //添加到objcet数组中
    (env)->SetObjectArrayElement(args, i, _obj);
    }
    //返回object数组
        return args;
}




/***********
    public class com.example.jn3.MyJNI {
  public com.example.jn3.MyJNI();
    Signature: ()V

  public native void displayParms(java.lang.String, int, boolean);
    Signature: (Ljava/lang/String;IZ)V

  public native int add(int, int);
    Signature: (II)I

  public native void setArray(boolean[]);
    Signature: ([Z)V

  public native java.lang.String[] getStringArray();
    Signature: ()[Ljava/lang/String;

  public native com.example.jn3.DiskInfo getStruct();
    Signature: ()Lcom/example/jn3/DiskInfo;

  public native com.example.jn3.DiskInfo[] getStructArray();
    Signature: ()[Lcom/example/jn3/DiskInfo;

  public static void testGo();
    Signature: ()V
}

 *
 *
 * *****/



//参数映射表
//这是在MainActivity中的native方法
static JNINativeMethod gMethods_MainActivity[] = {
        {"displayParms", "(Ljava/lang/String;IZ)V", (void *) displayParms},
        {"add", "(II)I", (void *) add},
        {"setArray", "([Z)V", (void *) setArray},
        {"getStringArray", "()[Ljava/lang/String;", (void *) getStringArray},
        {"getStruct", "()Lcom/example/jn3/DiskInfo;", (void *) getStruct},
        {"getStructArray", "()[Lcom/example/jn3/DiskInfo;", (void *) getStructArray},
};


//找到MainActivity.java类
int registerNatives_MYJNI(JNIEnv *engv) {
    jclass clazz;
    clazz = engv->FindClass("com/example/jn3/MainActivity");   //找到MainActivity类
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    //int len = sizeof(methods) / sizeof(methods[0]);
    if (engv->RegisterNatives(clazz, gMethods_MainActivity,
                              sizeof(gMethods_MainActivity) / sizeof(gMethods_MainActivity[0])) <
        0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}
