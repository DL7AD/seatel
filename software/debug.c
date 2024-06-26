#include "ch.h"
#include "hal.h"

#include "chprintf.h"
#include "debug.h"
#include <string.h>

char bucket[DEBUG_BUCKET_SIZE];

void debug_print(const char* str)
{
    size_t used = strlen(bucket);
    size_t in_len = strlen(str);
    if(in_len+1 < sizeof(bucket)-used)
        memcpy(&bucket[used], str, in_len+1);
}

void debug_emty_bucket(char ret[DEBUG_BUCKET_SIZE])
{
    strcpy(ret, bucket);
    bucket[0] = 0;
}
