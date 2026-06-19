#include "filesystem.h"
#include "../drivers/vga.h"
#include "../kernel/kernel.h"
typedef struct{char name[MAX_FNAME];char data[MAX_FDATA];int size;int used;}file_t;
static file_t files[MAX_FILES];
static file_t* find(const char* n){for(int i=0;i<MAX_FILES;i++)if(files[i].used&&str_cmp(files[i].name,n)==0)return &files[i];return 0;}
void fs_init(void){
    for(int i=0;i<MAX_FILES;i++)files[i].used=0;
    fs_create("readme.txt");fs_write("readme.txt","Welcome to SLeOS! Sierra Leone OS v1.0");
    fs_create("sdg.txt");fs_write("sdg.txt","SDG4: Quality Education for Sierra Leone");
}
int fs_create(const char* n){
    if(find(n)){vga_print("File exists\n");return -1;}
    for(int i=0;i<MAX_FILES;i++)if(!files[i].used){str_copy(n,files[i].name);files[i].data[0]=0;files[i].size=0;files[i].used=1;return 0;}
    vga_print("FS full\n");return -1;
}
int fs_write(const char* n,const char* d){
    file_t* f=find(n);if(!f){fs_create(n);f=find(n);}if(!f)return -1;
    int i=0;while(d[i]&&i<MAX_FDATA-1){f->data[i]=d[i];i++;}f->data[i]=0;f->size=i;return 0;
}
int fs_read(const char* n){
    file_t* f=find(n);
    if(!f){vga_print("Not found: ");vga_print(n);vga_print("\n");return -1;}
    vga_set_color(VGA_COLOR_LIGHT_GREEN,VGA_COLOR_BLACK);
    vga_print("--- ");vga_print(n);vga_print(" ---\n");
    vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    vga_print(f->data);vga_print("\n");return 0;
}
void fs_list(void){
    vga_set_color(VGA_COLOR_LIGHT_CYAN,VGA_COLOR_BLACK);
    vga_print("\n=== Files ===\n");
    vga_set_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    int cnt=0;
    for(int i=0;i<MAX_FILES;i++){
        if(!files[i].used)continue;
        char buf[8];
        vga_print(files[i].name);
        for(int k=str_len(files[i].name);k<18;k++)vga_print(" ");
        int_to_str(files[i].size,buf);vga_print(buf);vga_print(" bytes\n");
        cnt++;
    }
    if(!cnt)vga_print("(empty)\n");
    char buf[8];int_to_str(cnt,buf);vga_print(buf);vga_print(" file(s)\n");
}
int fs_delete(const char* n){
    file_t* f=find(n);if(!f){vga_print("Not found\n");return -1;}
    f->used=0;vga_print("Deleted: ");vga_print(n);vga_print("\n");return 0;
}
