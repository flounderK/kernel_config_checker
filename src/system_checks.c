#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


static char* g_check_and_dump_paths[] = {
    "/proc/sys/kernel/dmesg_restrict",
    "/proc/sys/kernel/kptr_restrict",
    "/proc/sys/kernel/randomize_va_space",
    "/sys/module/module/parameters/sig_enforce",
    "/proc/sys/kernel/modules_disabled",
    "/proc/sys/net/core/bpf_jit_enable",
    "/proc/sys/kernel/unprivileged_bpf_disabled",
    "/proc/sys/kernel/unprivileged_userns_apparmor_policy",
    "/proc/sys/kernel/unprivileged_userns_clone",
    "/proc/sys/vm/unprivileged_userfaultfd",

};

void system_config_checks(void) {
    char readbuf[512];
    char* pathptr = NULL;
    memset(&readbuf, 0, sizeof(readbuf));

    for (int i = 0; i < sizeof(g_check_and_dump_paths)/sizeof(char*); i++) {
        pathptr = g_check_and_dump_paths[i];
        if (read_file_to_buf(pathptr, readbuf, sizeof(readbuf)) == 0) {
            // no newline because it is included in the file contents
            printf("%s=%s", pathptr, readbuf);
            memset(&readbuf, 0, sizeof(readbuf));
        }
    }


}
