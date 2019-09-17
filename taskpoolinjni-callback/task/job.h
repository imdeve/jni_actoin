
//
// Created by Administrator on 2019/9/17.
//


//
// Created by Administrator on 2019/9/17.
//

#ifndef HELLOTASK_TASK_H
#define HELLOTASK_TASK_H

#include <pthread.h>


#define LL_ADD(item, list) { \
	item->prev = NULL; \
	item->next = list; \
	list = item; \
}

#define LL_REMOVE(item, list) { \
	if (item->prev != NULL) item->prev->next = item->next; \
	if (item->next != NULL) item->next->prev = item->prev; \
	if (list == item) list = item->next; \
	item->prev = item->next = NULL; \
}
struct worker;
typedef struct worker worker_t;
struct workqueue;
typedef struct workqueue workqueue_t;

struct worker {
    pthread_t thread;
    int terminate;
    struct workqueue *workqueue;
    struct worker *prev;
    struct worker *next;
    int wid;//worker id
} ;

typedef struct job {
    void (*job_function)(struct job *job);
    void *user_data;
    struct job *prev;
    struct job *next;
} job_t;


typedef  void (*OnWorkerExit)(workqueue_t* wkqueue, int wid);
typedef  void (*OnWorkerInit)(workqueue_t* wkqueue, int wid);
typedef  void (*OnWorkqueueExit)(workqueue_t* wkqueue);
struct workqueue{
    struct worker *workers;
    struct worker **workDict;
    int workNum;
    struct job *waiting_jobs;
    pthread_mutex_t jobs_mutex;
    pthread_cond_t jobs_cond;
    OnWorkerExit onWorkExitFn;
    OnWorkerInit onWorkInitFn;
    OnWorkqueueExit onWorkqueueExitFn;

} ;

void workqueue_shutdown(workqueue_t *workqueue);
void workqueue_add_job(workqueue_t *workqueue, job_t *job);
int threadpool_init(workqueue_t *workqueue, int numWorkers);

int threadpool_exit(workqueue_t *workqueue);
worker_t* threadpool_queryWorker(workqueue_t *workqueue,int wid);

#endif