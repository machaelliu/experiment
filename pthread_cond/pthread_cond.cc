#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;

pthread_cond_t g_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
char *g_p = NULL;

void *thread(void *arg) {
  pthread_detach(pthread_self());
  pthread_mutex_lock(&g_mutex);
  cout << "before wait, thread ix:" << *(int *)arg << endl;
  while (NULL == g_p) {
    pthread_cond_wait(&g_cond, &g_mutex);
  }
  pthread_mutex_unlock(&g_mutex);
  cout << "after wait, thread ix:" << *(int *)arg << endl;
}


int main(int argc,char *argv[]) {
  cout << "main start" << endl;
  int i = 0;
  int arr[] = {1, 2, 3, 4, 5};
  for (i = 0; i < 5; ++i) {
    pthread_t child_thread_id;    
    pthread_create(&child_thread_id,NULL,thread, arr+i);
  }
  sleep(2);
  char m = 0;
  g_p = &m;
  // pthread_cond_broadcast(&g_cond);
  pthread_cond_signal(&g_cond);
  sleep(2);
  cout << "main end" << endl;
  return 0;
}    
