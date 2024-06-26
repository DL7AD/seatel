#ifndef _API_H_
#define _API_H_

#define API_THREAD_STACK_SIZE   8192
#define API_THREAD_PORT         4533
#define API_THREAD_PRIORITY     (LOWPRIO + 3)

void api_init(void);
bool api_is_connected(void);

#endif
