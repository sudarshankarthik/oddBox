#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "file_writer.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size_in_MB>\n", argv[0]);
        return 1;
    }

    errno = 0;
    char *endptr = NULL;
    unsigned long long size_mb = strtoull(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid size: '%s'\n", argv[1]);
        return 1;
    }

    if (size_mb == 0) {
        fprintf(stderr, "Size must be greater than 0\n");
        return 1;
    }

    file_write((size_t)size_mb);
    return 0;
}
