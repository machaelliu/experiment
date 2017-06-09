/**********************************************************
 * Author        : qingtao
 * Email         : qingtao5@staff.weibo.com
 * Create time   : 2017-06-09 14:56
 * Last modified : 2017-06-09 14:56
 * Filename      : pthread_once.h
 * Description   : 
 * *******************************************************/
#ifndef _PTHREAD_ONCE_H_
#define _PTHREAD_ONCE_H_

void once_init_routine(void);
void *child_thread(void *arg);
int pthread_once_main(void);

#endif
