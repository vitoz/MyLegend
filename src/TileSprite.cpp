#include "stdafx.h"
#include "TileSprite.h"
#include <string>
#include "Util.h"

using std::string;
using namespace cocos2d;

TileSprite::TileSprite(const string tilePath)
{
  m_tilePath = tilePath;
  CCSprite::CCSprite();
}

void TileSprite::loadTexture()
{
  assert(m_tilePath != "");
  CCTexture2D *pTexture = Util::getCCTexture2D(m_tilePath.c_str());
  initWithTexture(pTexture);
  setAnchorPoint(CCPointZero);
}

void TileSprite::cleanup()
{
  CCSprite::cleanup();
  delete CCSprite::m_pobTexture;
}
