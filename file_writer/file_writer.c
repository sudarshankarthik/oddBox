#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "data_generator.h"

#define CHUNK 128*1024 // 1 MB Buffer (each element is 64 bytes) 

int file_write(size_t file_size)
{
	size_t buff_size = CHUNK;

    FILE *file = fopen("fast_random.bin", "wb");
    if (!file) { perror("fopen"); return 1; }

    uint64_t buffer[buff_size]; // 1 KB

    for (size_t i = 0; i < file_size; ++i) {
        fill_u64_buff(buffer, buff_size);
        if (fwrite(buffer, sizeof(uint64_t), buff_size, file) != buff_size) {
            perror("fwrite");
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    return 0;
}
