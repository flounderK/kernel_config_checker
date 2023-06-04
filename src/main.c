#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include "syscall_checks.h"
#include "system_checks.h"
#include "err_lookup.h"


int main (int argc, char *argv[]) {
    all_syscall_checks();
    system_config_checks();
    return 0;
}
