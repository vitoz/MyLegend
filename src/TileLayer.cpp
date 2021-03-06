#include "TileLayer.h"
#include <stdlib.h>
#include "Util.h"
#include "TileSprite.h"

using namespace cocos2d;

TileLayer::TileLayer( int width, int height )
{
  m_width = width;
  m_height = height;
  m_pTileSprites = new TileSprite *[width * height];
  CHECK_NEW_MEMORY(m_pTileSprites);
}

void TileLayer::setTile( int x, int y, const string path )
{
  assert(x <= m_width && x >= 0);
  assert(y <= m_height && y >= 0);

  m_pTileSprites[y * m_width + x] = new TileSprite (path);
  CHECK_NEW_MEMORY(m_pTileSprites[y * m_width + x]);
}

void TileLayer::clearTile( int x, int y )
{
  m_pTileSprites[y * m_width + x]->removeFromParent();
}

void TileLayer::loadTile( int x, int y )
{
  m_pTileSprites[y * m_width + x]->loadTexture();
  m_pTileSprites[y * m_width + x]->setPosition(CCPoint(x * 48, y * 32));
  this->addChild(m_pTileSprites[y * m_width + x]);
}
