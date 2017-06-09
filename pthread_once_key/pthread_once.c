/**********************************************************
 * Author        : qingtao
 * Email         : qingtao5@staff.weibo.com
 * Create time   : 2017-06-09 14:54
 * Last modified : 2017-06-09 14:54
 * Filename      : pthread_once.c
 * Description   : 
 * *******************************************************/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_once_t once=PTHREAD_ONCE_INIT; // one control var
pthread_mutex_t mutex; // be inited, mutex itself is not essential for once_t 

void once_init_routine(void) {
  int status;
  status=pthread_mutex_init(&mutex,NULL);
  if(status==0)
    printf("Init success! My id is %u\n", (unsigned)pthread_self());
}

void *child_thread(void *arg) {
  printf("I’m child ,My id is %u\n", (unsigned)pthread_self());
  pthread_once(&once, once_init_routine); 
  return NULL;
}    

int pthread_once_main(void) {
  pthread_t child_thread_id;    
  pthread_create(&child_thread_id, NULL, child_thread, NULL);
  sleep(1);

  printf("I’m father,my id is %u\n", (unsigned)pthread_self());
  pthread_once(&once, once_init_routine);
  pthread_join(child_thread_id, NULL);
  return 0;
}    
