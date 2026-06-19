#ifndef FS_H
#define FS_H
#define MAX_FILES 8
#define MAX_FNAME 16
#define MAX_FDATA 256
void fs_init(void);
int  fs_create(const char* name);
int  fs_write(const char* name,const char* data);
int  fs_read(const char* name);
void fs_list(void);
int  fs_delete(const char* name);
#endif
