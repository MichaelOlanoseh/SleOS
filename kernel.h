#ifndef KERNEL_H
#define KERNEL_H
#include <stdint.h>
typedef int bool;
#define true 1
#define false 0
#ifndef NULL
#define NULL ((void*)0)
#endif
void kernel_main(void);
void shell_run(void);
int  str_len(const char* s);
int  str_cmp(const char* a, const char* b);
void str_copy(const char* src, char* dst);
void int_to_str(int n, char* buf);
int  str_to_int(const char* s);
#endif
