#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdbool.h>
#include <unistd.h>

bool pathexists(char* path);
int read_file_to_buf(char* path, char* buf, size_t bufsize);
char* read_file(char* path);
#endif // __UTILS_H__
