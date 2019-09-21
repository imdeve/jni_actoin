//
// Created by Administrator on 2019/9/21.
//

#include <job.h>
#include "testcpool.h"
#include "../src/main/cpp/WlAndroidLog.h"
#include "stdlib.h"
static bool  flag =true;

#define BZERO(buf,size) do {\
        if (buf!=0) \
        {   \
            memset(buf,0,size);\
        }\
}while(0);

typedef struct {
    int a;
    int b;
}client_t;


void client_job(job_t* job){
    client_t* client = (client_t*) job->user_data;
    if (client!= nullptr)
    {
        int res = (client->a)+(client->b);

        LOGD("生产者通知消费者有产品产生，产品数量为：%d", res);
        //释放
        free(client);
        free(job);
    }
}
client_t* spoutClentData(){
    client_t *rClient = (client_t*)malloc(sizeof(client_t));
    BZERO(rClient,sizeof(client_t));
    rClient->b=10;
    rClient->a=20;
    return rClient;
}

job_t* spoutTask(){
    job_t* job = (job_t*)malloc(sizeof(job_t));
    BZERO(job,sizeof(job_t));
    job->job_function = client_job;
    job->user_data = spoutClentData();

    return job;
}

static void onWorkInitFn(workqueue_t* wkqueue, int wid){

    // printf("worker   ptr init :%p wid=%d \n",wkqueue->workDict[wid],wid);
    LOGD("onWorkInitFn...");
}

static void onWorkExitFn(workqueue_t* wkqueue, int wid){
    LOGD("onWorkExitFn...");
    //printf("worker ptr exit :%p wid=%d \n",wkqueue->workDict[wid],wid);
}
workqueue_t wq;

void  test_c_taskpool() {

    BZERO(&wq, sizeof(workqueue_t));
    threadpool_init(&wq,1);
    wq.onWorkInitFn =  &onWorkInitFn ;
    wq.onWorkDestoryFn =  &onWorkExitFn;
    threadpool_init(&wq,10);

    int i=0;
    for(;i<100;i++){
        workqueue_add_job(&wq,spoutTask());
    }
    // threadpool_exit(&wq);

}






