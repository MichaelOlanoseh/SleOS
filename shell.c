#include "kernel.h"
#include "../drivers/vga.h"
#include "../drivers/keyboard.h"
#include "../sched/scheduler.h"
#include "../mm/memory.h"
#include "../fs/filesystem.h"

#define CMDBUF 80
#define ARGBUF 48
#define MAX_FDATA 256

/* Declared in kernel.c */

static void prompt(void){
    vga_set_color(VGA_COLOR_LIGHT_GREEN,VGA_COLOR_BLACK);
    vga_print("sleos");
    vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    vga_print("> ");
}

static void parse(char* in,char* cmd,char* arg){
    int i=0,j=0;
    while(in[i]&&in[i]!=' ')cmd[j++]=in[i++];
    cmd[j]=0;j=0;
    while(in[i]==' ')i++;
    while(in[i])arg[j++]=in[i++];
    arg[j]=0;
}

static void cmd_help(void){
    vga_set_color(VGA_COLOR_LIGHT_CYAN,VGA_COLOR_BLACK);
    vga_print("\n=== SLeOS Commands ===\n");
    vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    vga_print("  help          - Show this help\n");
    vga_print("  ps            - Show process table\n");
    vga_print("  fcfs          - Run FCFS scheduler demo\n");
    vga_print("  rr            - Run Round-Robin demo\n");
    vga_print("  mem           - Show memory map\n");
    vga_print("  memtest       - Memory allocation demo\n");
    vga_print("  ls            - List files\n");
    vga_print("  cat <file>    - Read a file\n");
    vga_print("  touch <file>  - Create a file\n");
    vga_print("  write <file>  - Write text to file\n");
    vga_print("  rm <file>     - Delete a file\n");
    vga_print("  sdg           - Show SDG relevance\n");
    vga_print("  about         - About SLeOS\n");
    vga_print("  clear         - Clear screen\n");
    vga_print("  halt          - Halt the system\n\n");
}

static void cmd_sdg(void){
    vga_set_color(VGA_COLOR_LIGHT_CYAN,VGA_COLOR_BLACK);
    vga_print("\n=== UN SDG Relevance ===\n");
    vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    vga_print("  SDG 4 : Quality Education\n");
    vga_print("          Teach OS concepts in low-resource SL schools\n");
    vga_print("  SDG 9 : Industry & Innovation\n");
    vga_print("          Build local computing capacity in Sierra Leone\n");
    vga_print("  SDG 10: Reduced Inequalities\n");
    vga_print("          Open-source OS for digital inclusion\n");
    vga_print("  SDG 17: Partnerships for Goals\n");
    vga_print("          Open collaboration via GitHub\n\n");
}

static void cmd_about(void){
    vga_set_color(VGA_COLOR_LIGHT_GREEN,VGA_COLOR_BLACK);
    vga_print("\n  Sierra Leone OS (SLeOS) v1.0\n");
    vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    vga_print("  Limkokwing University - Sierra Leone\n");
    vga_print("  License: MIT Open Source\n");
    vga_print("  Tools: NASM + GCC + GNU LD + QEMU\n\n");
}

void shell_run(void){
    char input[CMDBUF],cmd[ARGBUF],arg[ARGBUF];
    while(1){
        prompt();
        keyboard_readline(input,CMDBUF);
        if(!input[0])continue;
        parse(input,cmd,arg);
        if     (str_cmp(cmd,"help")==0)    cmd_help();
        else if(str_cmp(cmd,"ps")==0)      sched_ps();
        else if(str_cmp(cmd,"fcfs")==0)    sched_fcfs();
        else if(str_cmp(cmd,"rr")==0)      sched_rr();
        else if(str_cmp(cmd,"mem")==0)     mm_show();
        else if(str_cmp(cmd,"memtest")==0) mm_demo();
        else if(str_cmp(cmd,"ls")==0)      fs_list();
        else if(str_cmp(cmd,"cat")==0)     fs_read(arg);
        else if(str_cmp(cmd,"touch")==0)   fs_create(arg);
        else if(str_cmp(cmd,"rm")==0)      fs_delete(arg);
        else if(str_cmp(cmd,"sdg")==0)     cmd_sdg();
        else if(str_cmp(cmd,"about")==0)   cmd_about();
        else if(str_cmp(cmd,"clear")==0){  vga_clear(); }
        else if(str_cmp(cmd,"write")==0){
            if(!arg[0]){vga_print("Usage: write <filename>\n");continue;}
            vga_print("Enter text: ");
            char text[MAX_FDATA];keyboard_readline(text,MAX_FDATA);
            fs_write(arg,text);vga_print("Written.\n");
        }
        else if(str_cmp(cmd,"halt")==0){
            vga_print("Goodbye!\n");
            __asm__ volatile("cli; hlt");
        }
        else{
            vga_set_color(VGA_COLOR_LIGHT_RED,VGA_COLOR_BLACK);
            vga_print("Unknown: ");vga_print(cmd);vga_print(" (type 'help')\n");
            vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
        }
    }
}
