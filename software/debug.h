#ifndef _DEBUG_H_
#define _DEBUG_H_

#define DEBUG_BUCKET_SIZE	4096

void debug_print(const char* str);
void debug_emty_bucket(char ret[DEBUG_BUCKET_SIZE]);

#endif
