#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ncurses.h>

static void *run(void *ptr){
  int i = 1;
  while(1) {
    mvprintw(0,0, "Status: %d", i);
    refresh();
    sleep(3);
    i++;
  }
  return NULL;
}

pthread_t sul_NetworkStart(){
  pthread_t thread;
  int threadRet;

  threadRet = pthread_create(&thread, NULL, run, NULL);
  if(threadRet){
    fprintf(stderr, "Could not create net thread code: %d\n", threadRet);
    exit(1);
  }

  return thread;
}
