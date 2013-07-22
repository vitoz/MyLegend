#ifndef __UTIL_H
#define __UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <pthread.h>
#include "cocos2d.h"

#if 0
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
#else
#define LOG(...) CCLOG(__VA_ARGS__)
#endif

#define ERR_EXIT(...) \
  LOG(__VA_ARGS__);\
  exit(1);

class Util
{
public:
  ~Util();

private:
  Util();

  //////////////////////////////////////////////////////////////////////////
  ///static
  //////////////////////////////////////////////////////////////////////////
public:
  static unsigned char *loadImageData(const char *path, int *pwidth, int *pheight);
  static void backDealing(void *value, void *(*func)(void *));

private:
  static Util m_instance;
  static std::vector<pthread_t> m_threads;
  static void cleanup();
};

#endif
