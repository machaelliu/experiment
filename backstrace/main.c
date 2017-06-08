/**********************************************************
 * Author        : qingtao
 * Email         : qingtao5@staff.weibo.com
 * Create time   : 2017-06-08 13:49
 * Last modified : 2017-06-08 13:49
 * Filename      : main.c
 * Description   : let programm tell the stack info when  
 *  seg fault happens
 * *******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>
#define BUF_SIZE (10)

int inv_ptr_error() {
  char *p = NULL;
  *p = 'c';
  return 0;
}

static void segv_handler(int signo) {
  signal(signo, SIG_DFL); // use default 

  void *buffer[BUF_SIZE];
  size_t stack_size = backtrace(buffer, BUF_SIZE);
  char **stack_info = (char **)backtrace_symbols(buffer, stack_size);

  fprintf(stderr, "Reeceived SIGSEGV. Stack trace:\n");
  for (size_t i = 0; i < stack_size; ++i) {
    fprintf(stderr, "%lu %s\n", i, stack_info[i]);
  }

  free(stack_info);
  exit(signo);
}

int main() {
  signal(SIGSEGV, segv_handler);
  signal(SIGABRT, segv_handler);
  inv_ptr_error();
  return 0;
}

