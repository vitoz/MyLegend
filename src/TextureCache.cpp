#include "TextureCache.h"

#include <assert.h>

USING_NS_CC;
using namespace std;

map<string, TextureCacheItem_t> TextureCache::m_texMaps;

cocos2d::CCTexture2D * TextureCache::get( std::string str )
{
  TextureCacheItem_t *pitem = getItem(str);
  if(pitem)
  {
    return pitem->pTexture;
  }
  return NULL;
}

void TextureCache::retain( std::string str )
{
  TextureCacheItem_t *pitem = getItem(str);
  assert(pitem != NULL);
  pitem->refCount++; 
}

void TextureCache::release( std::string str )
{
  TextureCacheItem_t *pitem = getItem(str);
  assert(pitem != NULL);
  pitem->refCount--;
  if(pitem->refCount == 0)
  {
    delete pitem->pTexture;
    m_texMaps.erase(m_texMaps.find(str));
  }
}

void TextureCache::set( std::string str, cocos2d::CCTexture2D *pTexture )
{
  CCLOG("cachesize:%d\n", m_texMaps.size());
  TextureCacheItem_t item;
  item.refCount = 0;
  item.pTexture = pTexture;
  m_texMaps[str] = item;
}

TextureCacheItem_t *TextureCache::getItem( std::string str )
{
  map<string, TextureCacheItem_t>::iterator it;
  it = m_texMaps.find(str);
  if(it == m_texMaps.end())
  {
    return NULL;
  }
  return &it->second;
}

