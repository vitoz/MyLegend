#include "GameSprite.h"
#include <string>
#include "Util.h"
#include "TextureCache.h"

using std::string;
using namespace cocos2d;

GameSprite::GameSprite(const string path)
  :m_path(path)
  ,m_pos(0, 0)
{

}

bool GameSprite::loadTexture()
{
  if(m_pobTexture != NULL)
  {
    return true;
  }

  CCTexture2D *pTexture = TextureCache::get(m_path);
  if(pTexture == NULL)
  {
    int width, height;
    unsigned char *rawData = Util::loadImageData(m_path.c_str(), &width, &height);
    if(rawData != NULL)
    {
      pTexture = new CCTexture2D();
      pTexture->initWithData(rawData, kCCTexture2DPixelFormat_RGBA8888, width, height, CCSize(width, height));
      delete rawData;
      TextureCache::set(m_path, pTexture);
    }
  }

  if(pTexture)
  {
    TextureCache::retain(m_path);
    initWithTexture(pTexture);
    setAnchorPoint(CCPointZero);
    setPosition(m_pos);
    return true;
  }
  return false;
}

void GameSprite::cleanup()
{
  if(m_pobTexture != NULL)
  {
    CCSprite::cleanup();
    TextureCache::release(m_path);
  }
  m_pobTexture = NULL;
}

GameSprite::~GameSprite()
{
  cleanup();
}
