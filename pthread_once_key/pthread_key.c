/**********************************************************
 * Author        : qingtao
 * Email         : qingtao5@staff.weibo.com
 * Create time   : 2017-06-09 15:02
 * Last modified : 2017-06-09 15:02
 * Filename      : pthread_key.c
 * Description   : 
 * *******************************************************/
#include <stdio.h>
#include <pthread.h>
#include "pthread_key.h"

pthread_key_t key;

void *thread1(void *arg) {
  struct data_t data;
  data.i = 1;
  data.d = 2.0;
  pthread_setspecific(key, &data);
  printf("data addr in thread1:%p\n", &data);

  struct data_t *addr = (struct data_t *)pthread_getspecific(key);;
  printf("key data addr in thread1:%p\n", addr);
  printf("i=%d, d=%f\n", addr->i, addr->d);
  return NULL;
}

void *thread2(void *arg) {
  int i = 200;
  pthread_setspecific(key, &i);
  printf("data addr in thread2:%p\n", &i);

  int *addr = (int *)pthread_getspecific(key);
  printf("key data addr in thread2:%p\n", addr);
  printf("i=%d\n", *addr);
  return NULL;
}

void pthread_key_main() {
  pthread_t tid1, tid2;
  pthread_key_create(&key, NULL);
  pthread_create(&tid1, NULL, thread1, NULL);
  pthread_create(&tid2, NULL, thread2, NULL);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_key_delete(key);
}
