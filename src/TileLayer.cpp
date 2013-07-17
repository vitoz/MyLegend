#include "TileLayer.h"
#include <stdlib.h>
#include "Util.h"
#include "GameSprite.h"

using namespace cocos2d;

TileLayer::TileLayer( int width, int height )
{
  m_width = width;
  m_height = height;

  m_pTileSprites = new GameSprite *[width * height];
  CHECK_NEW_MEMORY(m_pTileSprites);
  for(int i = 0; i < width * height; i++)
  {
    m_pTileSprites[i] = NULL;
  }
}

void TileLayer::setTile( int x, int y, const string path )
{
  assert(x <= m_width && x >= 0);
  assert(y <= m_height && y >= 0);

  m_pTileSprites[y * m_width + x] = new GameSprite (path, CCPoint(x * 48, y * 32));
  CHECK_NEW_MEMORY(m_pTileSprites[y * m_width + x]);
}

void TileLayer::clearTile( int x, int y )
{
  if(x < 0 || x >= m_width || y < 0 || y >= m_height)
  {
    return;
  }

  GameSprite *pSprite = m_pTileSprites[y * m_width + x];
  if(pSprite)
  {
    if(pSprite->getParent() != NULL)
    {
      pSprite->removeFromParent();
    }
  }
}


void TileLayer::loadTileData(int x, int y)
{
  if(x < 0 || x >= m_width || y < 0 || y >= m_height)
  {
    return;
  }
  GameSprite *pSprite = m_pTileSprites[y * m_width + x];
  if(pSprite)
  {
    pSprite->loadData();
  }
}
  

void TileLayer::loadTile( int x, int y )
{
  if(x < 0 || x >= m_width || y < 0 || y >= m_height)
  {
    return;
  }

  GameSprite *pSprite = m_pTileSprites[y * m_width + x];

  if(pSprite)
  {
    if(pSprite->getParent() != NULL)
    {
      return;
    }

    if(pSprite->loadTexture())
    {
      pSprite->setPosition(CCPoint(x * 48, y * 32));
      this->addChild(pSprite);
    }
  }
}

GameSprite * TileLayer::getTile( int x, int y )
{
  return m_pTileSprites[y * m_width + x];
}

void TileLayer::removeTile( int x, int y )
{
  if(m_pTileSprites[y * m_width + x] != NULL)
  {
    delete m_pTileSprites[y * m_width + x];
  }
  m_pTileSprites[y * m_width + x] = NULL;
}
