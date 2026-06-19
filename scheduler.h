#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdint.h>
#define MAX_PROC 8
#define QUANTUM  3
typedef enum{READY=0,RUNNING=1,DONE=2}pstate_t;
typedef struct{
    int pid;char name[16];pstate_t state;
    int burst,remaining,arrival,finish,wait,turnaround,priority;
}proc_t;
void sched_init(void);
void sched_add(const char* name,int burst,int arrival,int priority);
void sched_fcfs(void);
void sched_rr(void);
void sched_ps(void);
#endif
