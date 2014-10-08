/*
  sulliticker is a ncurses program that pulls in data off the internet
  and displays it in panels.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "cJSON.h"
#include "curlhelper.h"

void status_bar(){
  mvprintw(LINES - 1, 0, "Staus:");
}

int main(void){
  ResponseBuffer responseBuf;
  char *url = "https://api.bitcoinaverage.com/ticker/NZD/";
  cJSON *jsonRoot;
  double askPrice;
  initscr();
  printw("Hello World is loading !!!\n");	
  /*status_bar();*/
  refresh();
  
  responseBuf = sul_getUrlResponse(url);
  if(responseBuf != NULL){
    jsonRoot = cJSON_Parse(sul_getContent(responseBuf));
    askPrice = cJSON_GetObjectItem(jsonRoot, "ask")->valuedouble;
    printw("Ask price is %.2f\n", askPrice);

  }
 
  getch();
  endwin();
  sul_freeUrlResponse(responseBuf);
  return EXIT_SUCCESS;
}
