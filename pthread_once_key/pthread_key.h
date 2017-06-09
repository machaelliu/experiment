/**********************************************************
 * Author        : qingtao
 * Email         : qingtao5@staff.weibo.com
 * Create time   : 2017-06-09 15:02
 * Last modified : 2017-06-09 15:02
 * Filename      : pthread_key.h
 * Description   : 
 * *******************************************************/
#ifndef _PTHREAD_KEY_H_
#define _PTHREAD_KEY_H_
struct data_t {
  int i;
  double d;
};

void *thread1(void *arg);
void *thread2(void *arg);
void pthread_key_main();
#endif

