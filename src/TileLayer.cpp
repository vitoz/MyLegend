#include "TileLayer.h"
#include <stdlib.h>
#include "Util.h"
#include "GameSprite.h"

using namespace cocos2d;

TileLayer::TileLayer( int width, int height , const std::string rootPath)
  :m_rootPath(rootPath),
  m_height(height),
  m_width(width)
{
  m_tilesNo = new int[width * height];
  memset(m_tilesNo, 0, width * height * sizeof(int));
  CHECK_NEW_MEMORY(m_tilesNo);
  m_pTileSprites = new GameSprite *[width * height];
  memset(m_pTileSprites, NULL, width * height * sizeof(GameSprite *));
  CHECK_NEW_MEMORY(m_pTileSprites);
  for(int i = 0; i < width * height; i++)
  {
    m_pTileSprites[i] = NULL;
  }
}

void TileLayer::setTile( int x, int y, int no)
{
  assert(x <= m_width && x >= 0);
  assert(y <= m_height && y >= 0);

  m_tilesNo[y * m_width + x] = no;
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
    delete m_pTileSprites[y * m_width + x];
    m_pTileSprites[y * m_width + x] = NULL;
  }
}
  
void TileLayer::loadTile( int x, int y )
{
  if(x < 0 || x >= m_width || y < 0 || y >= m_height)
  {
    return;
  }

  int tileNo = m_tilesNo[y * m_width + x] & 0xffffff;
  int objClass = m_tilesNo[y * m_width + x] >> 24;

  if(tileNo == 0)
  {
    return;
  }

  if(m_pTileSprites[y * m_width + x] == NULL)
  {
    char path[255];
    if(objClass)
    {
      sprintf(path, "%s%d\\%06d.bmp", m_rootPath.c_str(), objClass, tileNo);
    }
    else
    {
      sprintf(path, "%s\\%06d.bmp", m_rootPath.c_str(), tileNo);
    }
    
    m_pTileSprites[y * m_width + x] = new GameSprite (path, CCPoint(0, 0));
    CHECK_NEW_MEMORY(m_pTileSprites[y * m_width + x]);
    GameSprite *pSprite = m_pTileSprites[y * m_width + x];
    if(pSprite->loadTexture())
    {
      pSprite->setPosition(CCPoint(x * 48, y * 32 - pSprite->getContentSize().height + 32));
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
  m_tilesNo[y * m_width + x] = 0;
}

void TileLayer::cleanup()
{
  if(m_pTileSprites == NULL)
  {
    return;
  }

  CCLayer::cleanup();

  removeAllChildren();

  for(int i = 0; i < m_width * m_height; i++)
  {
    if(m_pTileSprites[i] != NULL)
    {
      delete m_pTileSprites[i];
      m_pTileSprites[i] = NULL;
    }
  }

  delete [] m_pTileSprites;
  m_pTileSprites = NULL;
  delete [] m_tilesNo;
  m_tilesNo = NULL;
}

TileLayer::~TileLayer()
{
  cleanup();
}
