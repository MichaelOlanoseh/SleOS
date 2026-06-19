#include "scheduler.h"
#include "../drivers/vga.h"
#include "../kernel/kernel.h"

static proc_t procs[MAX_PROC];
static int pcount=0,npid=1;

void sched_init(void){
    pcount=0;npid=1;
    sched_add("EduPortal", 5,0,1);
    sched_add("HealthSys", 3,1,2);
    sched_add("AgriData",  7,2,1);
    sched_add("GovService",4,3,3);
}
void sched_add(const char* name,int burst,int arrival,int priority){
    if(pcount>=MAX_PROC)return;
    proc_t* p=&procs[pcount++];
    p->pid=npid++;str_copy(name,p->name);
    p->state=READY;p->burst=burst;p->remaining=burst;
    p->arrival=arrival;p->priority=priority;
    p->finish=p->wait=p->turnaround=0;
}
void sched_ps(void){
    vga_set_color(VGA_COLOR_LIGHT_CYAN,VGA_COLOR_BLACK);
    vga_print("\n=== Process Table ===\n");
    vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    vga_print("PID  Name         State  Burst\n");
    vga_print("---  -----------  -----  -----\n");
    const char* st[]={"READY  ","RUNNING","DONE   "};
    for(int i=0;i<pcount;i++){
        proc_t* p=&procs[i];char buf[8];
        int_to_str(p->pid,buf);vga_print(buf);vga_print("    ");
        vga_print(p->name);
        for(int k=str_len(p->name);k<13;k++)vga_print(" ");
        vga_print(st[p->state]);vga_print("  ");
        int_to_str(p->burst,buf);vga_print(buf);vga_print("\n");
    }
}
void sched_fcfs(void){
    /* Reset states */
    for(int i=0;i<pcount;i++){procs[i].state=READY;procs[i].remaining=procs[i].burst;}
    /* Sort by arrival */
    for(int i=0;i<pcount-1;i++)
        for(int j=0;j<pcount-i-1;j++)
            if(procs[j].arrival>procs[j+1].arrival){
                proc_t t=procs[j];procs[j]=procs[j+1];procs[j+1]=t;
            }
    vga_set_color(VGA_COLOR_LIGHT_CYAN,VGA_COLOR_BLACK);
    vga_print("\n=== FCFS Scheduler ===\n");
    vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    vga_print("PID  Name         Burst  Wait  Turnaround\n");
    vga_print("---  -----------  -----  ----  ----------\n");
    int t=0;
    for(int i=0;i<pcount;i++){
        proc_t* p=&procs[i];char buf[8];
        if(t<p->arrival)t=p->arrival;
        p->wait=t-p->arrival;
        p->finish=t+p->burst;
        p->turnaround=p->finish-p->arrival;
        p->state=DONE;t=p->finish;
        int_to_str(p->pid,buf);vga_print(buf);vga_print("    ");
        vga_print(p->name);
        for(int k=str_len(p->name);k<13;k++)vga_print(" ");
        int_to_str(p->burst,buf);vga_print(buf);vga_print("      ");
        int_to_str(p->wait,buf);vga_print(buf);vga_print("     ");
        int_to_str(p->turnaround,buf);vga_print(buf);vga_print("\n");
    }
    int tw=0,tt=0;
    for(int i=0;i<pcount;i++){tw+=procs[i].wait;tt+=procs[i].turnaround;}
    vga_set_color(VGA_COLOR_LIGHT_GREEN,VGA_COLOR_BLACK);
    char buf[8];
    vga_print("Avg Wait: ");int_to_str(tw/pcount,buf);vga_print(buf);
    vga_print("  Avg Turnaround: ");int_to_str(tt/pcount,buf);vga_print(buf);vga_print("\n");
    vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
}
void sched_rr(void){
    for(int i=0;i<pcount;i++){procs[i].remaining=procs[i].burst;procs[i].state=READY;procs[i].finish=0;}
    vga_set_color(VGA_COLOR_LIGHT_CYAN,VGA_COLOR_BLACK);
    vga_print("\n=== Round-Robin (Quantum=3) ===\n");
    vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    vga_print("Gantt: ");
    int cur=0,safety=0;
    while(safety<500){
        safety++;int all=1;
        for(int i=0;i<pcount;i++){
            proc_t* p=&procs[i];
            if(p->remaining<=0)continue;
            all=0;
            int run=p->remaining<QUANTUM?p->remaining:QUANTUM;
            char buf[8];
            vga_print(p->name);vga_print(":");int_to_str(run,buf);vga_print(buf);vga_print(" ");
            p->remaining-=run;cur+=run;
            if(p->remaining<=0){
                p->state=DONE;p->finish=cur;
                p->turnaround=p->finish-p->arrival;
                p->wait=p->turnaround-p->burst;
            }
        }
        if(all)break;
    }
    int tw=0,tt=0;
    for(int i=0;i<pcount;i++){tw+=procs[i].wait;tt+=procs[i].turnaround;}
    vga_set_color(VGA_COLOR_LIGHT_GREEN,VGA_COLOR_BLACK);
    char buf[8];
    vga_print("\nAvg Wait: ");int_to_str(tw/pcount,buf);vga_print(buf);
    vga_print("  Avg Turnaround: ");int_to_str(tt/pcount,buf);vga_print(buf);vga_print("\n");
    vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
}
