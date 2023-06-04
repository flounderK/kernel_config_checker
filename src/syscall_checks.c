#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "err_lookup.h"
#include "utils.h"

void bpf_syscall_check(void) {
    if (syscall(__NR_bpf, -1, NULL, 0) == -1) {
        printf("CONFIG_BPF_SYSCALL=");
         if (errno == ENOSYS) {
             printf("n\n");
             goto exit;
         } else {
             printf("y\n");
         }
        printf("CONFIG_BPF_UNPRIV_DEFAULT_OFF=");
         if (errno == EPERM) {
            printf("y\n");
         } else {
            printf("n\n");
         }
    }

exit:
    return;
}


void all_syscall_checks(void) {
    bpf_syscall_check();

    if (syscall(__NR_userfaultfd, -1) == -1) {
        printf("CONFIG_USERFAULTFD=");
        if (errno == ENOSYS) {
            printf("n\n");
        } else {
            printf("y\n");
        }
    }

    return;
}
