#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "curlhelper.h"
 
struct MemoryStruct {
  char *memory;
  size_t size;
};
 
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  /*struct MemoryStruct *mem = (struct MemoryStruct *)userp;*/
  ResponseBuffer mem = (ResponseBuffer) userp;
 
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
 
 
ResponseBuffer sul_getUrlResponse(char *url){
  CURL *curl_handle;
  CURLcode res;
  ResponseBuffer buf;
 
  buf = malloc(sizeof *buf);
  buf->size = 0;
  buf->memory = malloc(1); /* will grow later */
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();
 
  /* specify URL to get */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, url);
 
  /* send all data to this function  */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
  /* we pass our 'chunk' struct to the callback function */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)buf);
 
  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */ 
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
  /* get it! */ 
  res = curl_easy_perform(curl_handle);
 
  /* check for errors */ 
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
    /* free memory and set response to null */
    buf = sul_freeUrlResponse(buf);
  }
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);

  /* we're done with libcurl, so clean it up */ 
  curl_global_cleanup();
  
  return buf;
}

ResponseBuffer sul_freeUrlResponse(ResponseBuffer buf){
  free(buf->memory);
  free(buf);
  return NULL;
}

char *sul_getContent(ResponseBuffer buf){
  return buf->memory;
}
