#ifndef __UTIL_H
#define __UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cocos2d.h"

#define LOG(...) \
  {\
    FILE *fp = fopen("game.log", "w");\
    if(fp != NULL)\
    {\
      fprintf(fp, "%s:%s: ", __FILE__, __FUNCTION__);\
      fprintf(fp, __VA_ARGS__);\
      fprintf(fp, "\n");\
      fclose(fp);\
    }\
  }

#define ERR_EXIT(...) \
  LOG(__VA_ARGS__);\
  exit(1);

#define  CHECK_NEW_MEMORY(x) \
  if(x == NULL)\
  {\
    ERR_EXIT("no enougn memory.");\
  }
 
class Util
{
  public:
    static cocos2d::CCTexture2D *getCCTexture2D(const char *path);

};


#endif
