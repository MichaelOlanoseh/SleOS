#include "memory.h"
#include "../drivers/vga.h"
#include "../kernel/kernel.h"
#include <stdint.h>
static uint8_t bitmap[NFRAMES];
static int used=0;
void mm_init(void){for(int i=0;i<NFRAMES;i++)bitmap[i]=0;used=0;for(int i=0;i<4;i++){bitmap[i]=1;used++;}}
int mm_alloc(void){for(int i=0;i<NFRAMES;i++)if(!bitmap[i]){bitmap[i]=1;used++;return i;}return -1;}
void mm_free(int f){if(f>=0&&f<NFRAMES&&bitmap[f]){bitmap[f]=0;used--;}}
void mm_show(void){
    vga_set_color(VGA_COLOR_LIGHT_CYAN,VGA_COLOR_BLACK);
    vga_print("\n=== Memory Map (16 frames x 4KB) ===\n");
    vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    for(int i=0;i<NFRAMES;i++){
        if(bitmap[i]){vga_set_color(VGA_COLOR_LIGHT_RED,VGA_COLOR_BLACK);vga_print("[X]");}
        else{vga_set_color(VGA_COLOR_LIGHT_GREEN,VGA_COLOR_BLACK);vga_print("[ ]");}
        vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    }
    char buf[8];
    vga_print("\n[X]=Used  [ ]=Free  Used:");
    int_to_str(used,buf);vga_print(buf);
    vga_print("/");int_to_str(NFRAMES,buf);vga_print(buf);
    vga_print("  Free:");int_to_str(NFRAMES-used,buf);vga_print(buf);vga_print("\n");
}
void mm_demo(void){
    vga_set_color(VGA_COLOR_LIGHT_CYAN,VGA_COLOR_BLACK);
    vga_print("\n=== Memory Allocation Demo ===\n");
    vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    char buf[8];
    int f1=mm_alloc(),f2=mm_alloc(),f3=mm_alloc();
    vga_print("Allocated frames: ");
    int_to_str(f1,buf);vga_print(buf);vga_print(", ");
    int_to_str(f2,buf);vga_print(buf);vga_print(", ");
    int_to_str(f3,buf);vga_print(buf);vga_print("\n");
    mm_show();
    mm_free(f1);
    vga_print("Freed frame ");int_to_str(f1,buf);vga_print(buf);vga_print("\n");
    mm_show();
}
