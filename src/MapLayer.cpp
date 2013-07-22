#include "MapLayer.h"

#include <stdio.h>

#include "Util.h"
#include "TileLayer.h"
#include "VFile.h"

USING_NS_CC;

const char *TILE_ROOTPATH = "D:\\project\\cocos2dx\\Debug.win32\\data\\map\\pic\\tiles";
const char *STILE_ROOTPATH = "D:\\project\\cocos2dx\\Debug.win32\\data\\map\\pic\\stiles";
const char *OBJECT_ROOTPATH = "D:\\project\\cocos2dx\\Debug.win32\\data\\map\\pic\\object";

bool MapLayer::load(const char * path)
{
  setPosition(-4800 , -3200);

  if(loadMapFile(path))
  {
    addChild(m_tileLayer);
    addChild(m_stileLayer);
    addChild(m_objectLayer);
    return true;
  }
  return false;
}

bool MapLayer::loadMapFile( const char *path )
{
  int width;
  int height;
  VFile file;
  if(file.open(path, "r") < 0)
  {
    LOG("map:%s is not existed.", path);
    return false;
  }

  unsigned char *pMapData = new unsigned char[file.size()];

  file.read(pMapData, file.size());
  width = pMapData[0]+(pMapData[1]<<8);
  height = pMapData[2]+(pMapData[3]<<8);

  m_blockFlag = new BlockFlag_t[width * height];
  m_tileLayer = new TileLayer(width, height, TILE_ROOTPATH);
  m_stileLayer = new TileLayer(width, height, STILE_ROOTPATH);
  m_objectLayer = new TileLayer(width, height, OBJECT_ROOTPATH);

  for (int i = 0; i < width * height; i++)
  {
    int n = i * 12 + 52;
    if (pMapData[n+1]&0x80 || pMapData[n+3]&0x80 || pMapData[n+5]&0x80)
    {
      pMapData[n+1] &= ~0x80;
      pMapData[n+3] &= ~0x80;
      pMapData[n+5] &= ~0x80;
      m_blockFlag[i].moveable = 0;
    }
    else
    {
      m_blockFlag[i].moveable = 1;
    }

    int tileNo, stileNo, objectNo, objectClassNo;

    tileNo = ((pMapData[n]+(pMapData[n+1]<<8)))-1;
    stileNo = pMapData[n+2]+(pMapData[n+3]<<8)-1;
    objectNo = (pMapData[n+4]+(pMapData[n+5]<<8))-1;

    objectClassNo = pMapData[n + 10]+1;

    if(objectNo == 2723 && objectClassNo == 1)
    {
      objectNo = -1;
    }

    int x, y;
    x = i / height;
    y = i % height;

    if(tileNo >= 0)
    {
      m_tileLayer->setTile(x, y, tileNo & 0xffffff);
    }

    if(stileNo >= 0)
    {
      m_stileLayer->setTile(x, y, stileNo & 0xffffff);
    }

    if(objectNo >= 0)
    {
      m_objectLayer->setTile(x, y, (objectClassNo << 24) | (objectNo & 0xffffff));
    }
  }

  //–ﬁ’˝Tile
  for (int i = 0; i < height-1; i++)
  {
    for (int j = 0; j < width-1; j++)
    {
      if (m_tileLayer->getTile(j, i) != NULL)
      {
        m_tileLayer->removeTile(j + 1, i);
        m_tileLayer->removeTile(j, i + 1);
        m_tileLayer->removeTile(j + 1, i + 1);
      }
    }
  }

  m_width = width;
  m_height = height;

  delete [] pMapData;
  file.close();
  return true;
}

#define CHECK_MAX(n, max) \
  if(n > max)\
{\
  n = max;\
}

#define CHECK_ZERO(n) \
  n = n < 0 ? 0 : n;

void MapLayer::update( cocos2d::CCTime dt )
{
  CCPoint pos = getPosition();
  int x = pos.x / 48;
  int y = pos.y / 32;

  x = -x;
  y = -y;

  int x1, x2, y1, y2;

  x1 = x - 20;
  x2 = x + 20;
  y1 = y - 20;
  y2 = y + 20;

  CHECK_ZERO(x1);
  CHECK_ZERO(y1);

  for(int i = x1 - 1; i < x2 + 1; i++)
  {
    for(int j = y1 - 1; j < y2 + 1; j++)
    {
      if(i < x1 || i >= x2 || j < y1 || j >= y2)
      {
        m_tileLayer->clearTile(i, j);
        m_stileLayer->clearTile(i, j);
        m_objectLayer->clearTile(i, j);
      }
      else
      {
        m_tileLayer->loadTile(i, j);
        m_stileLayer->loadTile(i, j);
        m_objectLayer->loadTile(i, j);
      }
    }
  }
}

MapLayer::~MapLayer()
{
  cleanup();
}

void MapLayer::cleanup()
{
  //±‹√‚÷ÿ∏¥cleanup
  if(m_tileLayer == NULL)
  {
    return;
  }

  CCLayer::cleanup();

  removeChild(m_tileLayer);
  removeChild(m_stileLayer);
  removeChild(m_objectLayer);
  delete m_tileLayer;
  m_tileLayer = NULL;
  delete m_stileLayer;
  m_stileLayer = NULL;
  delete m_objectLayer;
  m_objectLayer = NULL;
  delete [] m_blockFlag;
  m_blockFlag = NULL;
}
