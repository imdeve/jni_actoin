#include <jni.h>
#include <string>

struct DiskInfo
{
    char name[256];
    int serial;
};

static jstring ToJString(JNIEnv *env, const std::string &value)
{
    return env->NewStringUTF(value.c_str());
}




extern "C" JNIEXPORT jstring JNICALL
Java_com_example_freedom_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_freedom_MyJni_displayParms(JNIEnv *env, jobject instance, jstring s,
                                            jint i, jboolean b) {

    const char* szStr = (env)->GetStringUTFChars(s, 0);
    printf("String = [%s]\n", szStr);
    printf("int = %d\n", (int)i);
    printf("boolean = %s\n", (b == JNI_TRUE ? "true" : "false"));
    (env)->ReleaseStringUTFChars(s, szStr);

}
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_freedom_MyJni_add(JNIEnv *env, jobject instance, jint a, jint b) {

    int rtn = (int)(a + b);
    return (jint)rtn;

}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_freedom_MyJni_setArray(JNIEnv *env, jobject instance, jbooleanArray ba) {

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
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_example_freedom_MyJni_getStringArray(JNIEnv *env, jobject instance) {

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

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_freedom_MyJni_getStruct(JNIEnv *env, jobject obj) {

    /* 下面为获取到Java中对应的实例类中的变量*/

    //获取Java中的实例类
    jclass DiskInfoClaz = (env)->FindClass("com/example/freedom/DiskInfo");
    //获取类中每一个变量的定义
    //名字
    jfieldID nameIdTag = (env)->GetFieldID(DiskInfoClaz, "name", "Ljava/lang/String;");
    //序列号
    jfieldID seriaIdTag = (env)->GetFieldID(DiskInfoClaz, "serial", "I");


    //获得得该类型的构造函数  函数名为 <init> 返回类型必须为 void 即 V
    jmethodID constrocMID = env->GetMethodID(DiskInfoClaz,"<init>","()V");

  //  jstring str222 = env->NewStringUTF(" come from Native ");
//CALL 构造函数
    jobject stu_ojb = env->NewObject(DiskInfoClaz,constrocMID);  //构造一个对象，调用该类的构造函数，并且传递参数


    //给每一个实例的变量赋值
    (env)->SetObjectField(stu_ojb, nameIdTag, (env)->NewStringUTF("my name is D:"));
    (env)->SetIntField(stu_ojb, seriaIdTag, 10);

    return stu_ojb;

}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_example_freedom_MyJni_getStructArray(JNIEnv *env, jobject _obj) {

    //申明一个object数组
    jobjectArray args = 0;
    //数组大小
    jsize        len = 5;

    //获取Java中的实例类
    jclass DiskInfoClaz = (env)->FindClass("com/example/freedom/DiskInfo");

    //新建object数组
    args = (env)->NewObjectArray(len, DiskInfoClaz, 0);
    /* 下面为获取到Java中对应的实例类中的变量*/


    //获取类中每一个变量的定义
    //名字
   // jfieldID nameIdTag = (env)->GetFieldID(DiskInfoClaz, "name", "Ljava/lang/String;");
    //序列号
   // jfieldID seriaIdTag = (env)->GetFieldID(DiskInfoClaz, "serial", "I");
    //给每一个实例的变量付值
    std::string msg = "我的磁盘名字是 D:";
    jstring diskName = ToJString(env,msg);

    jmethodID constrocMID = env->GetMethodID(DiskInfoClaz,"<init>","(Ljava/lang/String;I)V");

    //给每一个实例的变量付值，并且将实例作为一个object，添加到objcet数组中
    for(jint  i = 0; i < len; i++)
    {
        //获得得该类型的构造函数  函数名为 <init> 返回类型必须为 void 即 V

//CALL 构造函数
        jobject diskInstance = env->NewObject(DiskInfoClaz,constrocMID,diskName,i);  //构造一个对象，调用该类的构造函数，并且传递参数

        //detail设置
       // (env)->SetObjectField(_obj,nameIdTag,(env)->NewStringUTF("my name is D:"));
      //  (env)->SetIntField(diskInstance, seriaIdTag, 10);
        //添加到objcet数组中
        (env)->SetObjectArrayElement(args, i, diskInstance);
    }
    //返回object数组
    return args;

}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_freedom_MyJni_getStructList(JNIEnv *env, jobject instance) {

    jclass DiskInfoClaz = (env)->FindClass("com/example/freedom/DiskInfo");
    jclass list_cls = env->FindClass("Ljava/util/ArrayList;");
    jmethodID constrocMID = env->GetMethodID(DiskInfoClaz,"<init>","()V");
  //  jfieldID str = (env)->GetFieldID(DiskInfoClaz, "name", "Ljava/lang/String;");
    //序列号
   // jfieldID ival = (env)->GetFieldID(DiskInfoClaz, "serial", "I");
    jfieldID nameIdTag = (env)->GetFieldID(DiskInfoClaz, "name", "Ljava/lang/String;");
    //序列号
    jfieldID seriaIdTag = (env)->GetFieldID(DiskInfoClaz, "serial", "I");

    jmethodID list_costruct = env->GetMethodID(list_cls , "<init>","(Ljava/lang/String;I)V"); //获得得构造函数Id
    std::string pathName = "我的磁盘名字是 D:";
    jstring pathNameValue = ToJString(env,pathName);
    jobject list_obj = env->NewObject(list_cls , list_costruct); //创建一个Arraylist集合对象
    jmethodID list_add  = env->GetMethodID(list_cls,"add","(Ljava/lang/Object;)Z");

    jsize size =5;
    jint i=0;
    for (i=0;i<size;i++)
    {
        jobject diskInstance = env->NewObject(DiskInfoClaz,constrocMID,pathNameValue,i);  //构造一个对象，调用该类的构造函数，并且传递参数
      //  env->SetIntField(diskInstance,seriaIdTag,100);
      //  env->SetObjectField(diskInstance,nameIdTag,(env)->NewStringUTF("my name is F:"));
       // env->CallBooleanMethod(list_obj , list_add , diskInstance); //执行Arraylist类实

    }
    return list_obj;
}