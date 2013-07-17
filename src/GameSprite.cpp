#include "stdafx.h"
#include "GameSprite.h"
#include <string>
#include "Util.h"

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
  if(m_rawData == NULL && getParent() == NULL)
  {
    m_rawData = Util::loadImageData(m_path.c_str(), &m_width, &m_height);
  }
}

bool GameSprite::loadTexture()
{
  if(m_rawData != NULL)
  {
    CCTexture2D *pTexture = new CCTexture2D();
    CCImage image;
    image.initWithImageData(m_rawData, 4 * m_width * m_height, CCImage::kFmtRawData, m_width, m_height, 8);
    pTexture->initWithImage(&image);
//     CCSize size;
//     size.setSize(m_width, m_height);
//     pTexture->initWithData(m_rawData, kCCTexture2DPixelFormat_RGBA8888, m_width, m_height, size);
    initWithTexture(pTexture);
    setAnchorPoint(CCPointZero);
    setPosition(m_pos);
    delete m_rawData;
    m_rawData = NULL;
    return true;
  }
  return false;
}

void GameSprite::cleanup()
{
  CCSprite::cleanup();
  delete m_pobTexture;
}