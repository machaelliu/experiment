/**********************************************************
 * Author        : qingtao
 * Email         : qingtao5@staff.weibo.com
 * Create time   : 2017-06-12 13:54
 * Last modified : 2017-06-12 13:54
 * Filename      : test.cc
 * Description   : 
 * *******************************************************/
#include <queue>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "co_routine.h"

#include<stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

void err_quit(const char *s) {
  cerr << s << endl;
  exit(0);
}

void err_sys(const char *s) {
  cerr << s << "." << strerror(errno) << endl;
  exit(0);
}

void send_recv(int index) {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		err_sys("socket error");
	}

  int flags = fcntl(sockfd, F_GETFL, 0);                                             
  if (flags & O_NONBLOCK) {
    printf("is non block\n");                                                    
  }                    
	
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(1573);
	if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) < 0) {
		err_quit("inet_pton error");
	}

  int ret = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)); 
	if (ret < 0) {
		err_sys("connect error");
	}

	char buf[1024] = { 0 };
  snprintf(buf, 1024, "co index: %d", index);
  int n = 0;


  int i = 0;
  while (i++ < 100) {

    for (;;) {
      if (send(sockfd, buf, strlen(buf), 0) < 0) { // epoll wait timeout
        struct pollfd pf = { 0 };
        pf.fd = -1;
        poll( &pf,1,1000);
        continue;
      } else {
        printf("send ok\n");
        break;
      }
    }

    for (;;) {
      if ((n = recv(sockfd, buf, 1024, 0)) <= 0) {
        // co_poll timeout 
        struct pollfd pf = { 0 };
        pf.fd = -1;
        poll( &pf,1,1000);
        continue;
      } else {
        break;
      }
    }

    buf[n] = '\0';
    printf("n=%d, %s\n",n, buf);
  }

  close(sockfd);
}

void* routine1(void* arg) {
  co_enable_hook_sys();
  send_recv(1);

	return NULL;


}

void* routine2(void* arg) {
  co_enable_hook_sys();
  send_recv(2);

	return NULL;
}

int main(void) {
  stCoRoutine_t *co1 = 0;
  co_create( &co1,NULL, routine1, NULL);
  co_resume(co1);

  stCoRoutine_t *co2 = 0;
  co_create(&co2,NULL, routine2, NULL);
  co_resume(co2 );
  co_eventloop(co_get_epoll_ct(),0,0 );
  return 0;
}
