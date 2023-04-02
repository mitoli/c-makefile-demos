#ifndef MAKEFILE_DEMOS_SRC_COMMON_H_
#define MAKEFILE_DEMOS_SRC_COMMON_H_

#include <stdio.h>
#include <stdlib.h>

void log_fatal(const char *msg) {
    perror(msg);
    exit(1);
}

#endif  // MAKEFILE_DEMOS_SRC_COMMON_H_
