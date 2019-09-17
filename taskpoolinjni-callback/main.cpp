#include <iostream>
#include <stdlib.h>
#include "task/job.h"
#include <unistd.h>

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
        std::cout << "client_job : result:" << res << std::endl;
        //释放
        free(client);
        free(job);
    }
}
client_t* spoutClentData(){
    client_t *rClient = (client_t*)malloc(sizeof(client_t));
    BZERO(rClient,sizeof(client_t));
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

    printf("worker   ptr init :%p \n",wkqueue->workDict[wid]);
}

static void onWorkExitFn(workqueue_t* wkqueue, int wid){
    printf("worker ptr exit :%p \n",wkqueue->workDict[wid]);
}

int main() {

    workqueue_t wq;
    BZERO(&wq, sizeof(workqueue_t));
    threadpool_init(&wq,2);
    wq.onWorkInitFn =  &onWorkInitFn ;
    wq.onWorkExitFn =  &onWorkExitFn;
    threadpool_init(&wq,10);



    while(flag)
    {

        workqueue_add_job(&wq,spoutTask());
        usleep(500*1000);

    }


    threadpool_exit(&wq);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}