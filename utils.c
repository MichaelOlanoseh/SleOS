#include "kernel.h"
int str_len(const char* s){int i=0;while(s[i])i++;return i;}
int str_cmp(const char* a,const char* b){while(*a&&(*a==*b)){a++;b++;}return *a-*b;}
void str_copy(const char* src,char* dst){while((*dst++=*src++));}
void int_to_str(int n,char* buf){
    if(n==0){buf[0]='0';buf[1]=0;return;}
    char tmp[12];int i=0,neg=0;
    if(n<0){neg=1;n=-n;}
    while(n>0){tmp[i++]='0'+(n%10);n/=10;}
    if(neg)tmp[i++]='-';
    int j=0;while(i>0)buf[j++]=tmp[--i];buf[j]=0;
}
int str_to_int(const char* s){
    int r=0,neg=0;if(*s=='-'){neg=1;s++;}
    while(*s>='0'&&*s<='9')r=r*10+(*s++)-'0';
    return neg?-r:r;
}
