//
// Created by Administrator on 2019/9/21.
//

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "testcpp_pool.h"
#include "../callbacks/TeamCallback.h"

static Task* newTask(int id){
    TeamCallback *add = new  TeamCallback();
    add->id = id;
    return  add;
}

static JNIThreadPool pool;

void test_cpp(){

    pool.init(0,3);

    for (int i=0;i<100;i++)
    {
        pool.addTask(newTask(i));
    }


}
