
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

bool pathexists(char* path) {
    bool ret = false;
    int err = -1;
    struct stat s;
    memset(&s, 0, sizeof(s));
    if (path == NULL) {
        goto exit;
    }

    err = stat(path, &s);
    if (err == -1) {
        if (errno == ENOENT) {
            goto exit;
        }
    }

    ret = true;
exit:
    return ret;
}

int read_file_to_buf(char* path, char* buf, size_t bufsize) {
    int ret = -1;
    int fd = -1;
    if (buf == NULL) {
        goto exit;
    }
    fd = open(path, O_RDONLY);
    if (fd == -1) {
        goto exit;
    }

    if (read(fd, buf, bufsize) == -1) {
        goto exit;
    }

    ret = 0;
exit:
    if (fd != -1) {
        close(fd);
    }
    return ret;
}

char* read_file(char* path) {
    char* buf = NULL;
    int fd = -1;
    size_t bufsize = 0;

    fd = open(path, O_RDONLY);
    if (fd == -1) {
        goto exit;
    }

    bufsize = lseek(fd, 0, SEEK_END);
    if (bufsize == -1) {
        goto exit;
    }
    lseek(fd, 0, SEEK_SET);
    buf = (char*)malloc(bufsize);
    if (buf == NULL) {
        goto exit;
    }
    memset(buf, 0, bufsize);

    if (read(fd, buf, bufsize) == -1) {
        free(buf);
        buf = NULL;
        goto exit;
    }

exit:
    if (fd != -1) {
        close(fd);
    }
    return buf;
}
