#ifndef MEMORY_H
#define MEMORY_H
#define NFRAMES 16
void mm_init(void);
int  mm_alloc(void);
void mm_free(int f);
void mm_show(void);
void mm_demo(void);
#endif
