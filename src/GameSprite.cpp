#include "GameSprite.h"
#include <string>
#include "Util.h"
#include "TextureCache.h"

using std::string;
using namespace cocos2d;

GameSprite::GameSprite(const string path, const CCPoint &pos)
  :m_rawData(NULL),
  m_path(path),
  m_pos(pos)
{

}

void GameSprite::loadData()
{
  assert(m_path != "");
  if(m_rawData == NULL && TextureCache::get(m_path) == NULL)
  {
    m_rawData = Util::loadImageData(m_path.c_str(), &m_width, &m_height);
  }
}

bool GameSprite::loadTexture()
{
  CCTexture2D *pTexture = NULL;

  loadData();

  if(m_rawData != NULL)
  {
    pTexture = new CCTexture2D();
    //    CCImage image;
    //     image.initWithImageData(m_rawData, 4 * m_width * m_height, CCImage::kFmtRawData, m_width, m_height, 8);
    //     pTexture->initWithImage(&image);
    CCSize size;
    size.setSize(m_width, m_height);
    pTexture->initWithData(m_rawData, kCCTexture2DPixelFormat_RGBA8888, m_width, m_height, size);
    delete m_rawData;
    TextureCache::set(m_path, pTexture);
    m_rawData = NULL;
  }

  pTexture = TextureCache::get(m_path);
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
  CCSprite::cleanup();
  m_pobTexture = NULL;
  TextureCache::release(m_path);
}