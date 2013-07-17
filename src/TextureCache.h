#ifndef __TEXTURECACHE_H
#define __TEXTURECACHE_H

#include <map>
#include <string>
#include "cocos2d.h"
#include "pthread.h"

typedef struct TextureCacheItem_st
{
  cocos2d::CCTexture2D *pTexture;
  int refCount;
}TextureCacheItem_t;

class TextureCache
{

public:
  static cocos2d::CCTexture2D *get(std::string str);
  static void retain(std::string str);
  static void release(std::string str);
  static void set(std::string str, cocos2d::CCTexture2D *pTexture);

private:
  static pthread_mutex_t m_lock;
  static std::map<std::string, TextureCacheItem_t> m_texMaps;

  static TextureCacheItem_t *getItem(std::string str);
};


#endif