#ifndef SULLI_CURL_HELPER_H_
#define SULLI_CURL_HELPER_H_
#include <curl/curl.h>

typedef struct MemoryStruct *ResponseBuffer;

ResponseBuffer sul_getUrlResponse(char *url);
ResponseBuffer sul_freeUrlResponse(ResponseBuffer buf);
char *sul_getContent(ResponseBuffer buf);

#endif
