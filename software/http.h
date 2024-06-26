#ifndef _HTTP_H_
#define _HTTP_H_

#define HTTP_THREAD_STACK_SIZE 	8192
#define HTTP_THREAD_PORT       	80
#define HTTP_THREAD_PRIORITY   	(LOWPRIO + 2)

void http_init(void);

#endif
