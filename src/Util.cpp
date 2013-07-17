#include "stdafx.h"
#include "Util.h"

#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#include <vector>

using std::vector;

struct RGBA 
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};

struct RGB 
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
}i;

struct BmpHeadData 
{
  unsigned char notuse[18];
  unsigned char width[4];
  unsigned char height[4];
  unsigned char planes[2];
  unsigned char bitsPerPixel[2];
  unsigned char notuse2[24];
};

struct Bmp8Data 
{
  BmpHeadData head;
  RGBA colorTable[256];
  unsigned char colorIndexes[1];
};

struct Bmp24Data 
{
  BmpHeadData head;
  unsigned char colorData[1];   
};

Util Util::m_instance;
vector<pthread_t> Util::m_threads;

Util::~Util()
{
  Util::cleanup();
}

Util::Util()
{

}

unsigned char *Util::loadImageData(const char *path, int *pwidth, int *pheight)
{
  assert(path != NULL);

  FILE *fp;
  fp = fopen(path, "rb");
  if(fp == NULL)
  {
    //LOG("fopen() File don't exist.%s\n", path);
    return NULL;
  }

  fseek(fp, 0, SEEK_END);
  int size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  BmpHeadData *bmp = NULL;
  bmp = (BmpHeadData*)malloc(size);
  if(bmp == NULL)
  {
    LOG("malloc() no memory.\n");
    LOG("m_size:%d\n", size);
    goto bmp_malloc_err;
  }

  fread(bmp, size, 1, fp);

  int width = bmp->width[3];
  width <<= 8;
  width |= bmp->width[2];
  width <<= 8;
  width |= bmp->width[1];
  width <<= 8;
  width |= bmp->width[0];

  int height = bmp->height[3];
  height <<= 8;
  height |= bmp->height[2];
  height <<= 8;
  height |= bmp->height[1];
  height <<= 8;
  height |= bmp->height[0];

  RGBA *imageData = (RGBA *)malloc(width * height * 4);
  if(imageData == NULL)
  {
    LOG("malloc() no memory.\n");
    LOG("width:%d height:%d\n", width, height);
    goto image_malloc_err;
  }

  switch(bmp->bitsPerPixel[0])
  {
  case 8:
    {
      Bmp8Data *bmp8 = (Bmp8Data*)bmp;
      int alignLineSize;
      alignLineSize = ((width % 4) > 0) ? \
        width + (4 - width % 4) : width;
      for(int i = 0; i < height; i++)
      {
        for(int j = 0; j < width; j++)
        {
          int pos = i * width + j;
          int colorIndex = bmp8->colorIndexes[i * alignLineSize + j];
          imageData[pos].r = bmp8->colorTable[colorIndex].b;
          imageData[pos].g = bmp8->colorTable[colorIndex].g;
          imageData[pos].b = bmp8->colorTable[colorIndex].r;
          imageData[pos].a = 0xff;

          if((imageData[pos].r == 0) 
            && imageData[pos].g == 0 
            && imageData[pos].b == 0)
          {
            imageData[pos].a = 0;
          }

        }
      }
    }
    break;
  case 24:
    {
      Bmp24Data *bmp24= (Bmp24Data *)bmp;
      int alignLineSize;
      int lineSize = width * 3;
      alignLineSize = ((lineSize % 4) > 0) ? \
        lineSize + (4 - lineSize % 4) : lineSize;
      for(int i = 0; i < height; i++)
      {
        for(int j = 0; j < width; j++)
        {
          int pos = (height - 1 - i) * width + j;
          int colorIndex = i * alignLineSize + j;
          imageData[pos].r = bmp24->colorData[alignLineSize * i + j * 3 + 2];
          imageData[pos].g = bmp24->colorData[alignLineSize * i + j * 3 + 1];
          imageData[pos].b = bmp24->colorData[alignLineSize * i + j * 3];
          imageData[pos].a = 0xff;
          if(colorIndex == 0)
          {
            imageData[pos].a = 0;
          }
        }
      }
    }
    break;
  default:
    LOG("error file type.\n");
    goto type_error;
    break;
  }
  free(bmp);
  fclose(fp);

  *pwidth = width;
  *pheight = height;
  return (unsigned char *)imageData;

type_error:
  free(imageData);
image_malloc_err:
  free(bmp);
bmp_malloc_err:
  fclose(fp);
  return NULL;
}

void Util::backDealing(void *value, void *(*func)(void *))
{
  pthread_t pid;
  if(pthread_create(&pid, NULL, func, value) < 0)
  {
    LOG("Thread Create fail.");
    return;
  }
  m_threads.push_back(pid);
}

void Util::cleanup()
{
  for(vector<pthread_t>::iterator it = m_threads.begin(); it != m_threads.end(); it++)
  {
    pthread_cancel(*it);
    pthread_join(*it, NULL);
  }
}
