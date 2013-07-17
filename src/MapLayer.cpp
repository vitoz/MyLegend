#include "MapLayer.h"

#include <stdio.h>

#include "Util.h"
#include "TileLayer.h"
#include "VFile.h"

USING_NS_CC;

const char *MAP_PIC_PATH = "D:\\project\\cocos2dx\\Debug.win32\\data\\map\\pic";

bool MapLayer::load(const char * path)
{
  //   TileLayer *player = new TileLayer(100, 100);
  //   for(int i = 0; i < 16; i++)
  //     for(int j = 0; j < 32; j++)
  //     {
  //       player->setTile(i, j, "d:/a.bmp");
  //       player->loadTile(i, j);
  //     }
  //     this->addChild(player);
  //     return false;

  WCHAR aaa[255];
  GetModuleFileName(NULL, aaa, 255);
  CCLOG("path:%s\n", aaa);

  if(loadMapFile(path))
  {
    for(int i = 0; i <10; i++)
    {
      for(int j = 0; j < 10; j++)
      {
        m_tileLayer->loadTile(i, j);
        m_stileLayer->loadTile(i, j);
        m_objectLayer->loadTile(i, j);
      }
    }

    addChild(m_tileLayer);
    addChild(m_stileLayer);
    addChild(m_objectLayer);

    Util::backDealing(this, MapLayer::backDealTilesData);
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
  CHECK_NEW_MEMORY(pMapData);

  file.read(pMapData, file.size());
  width = pMapData[0]+(pMapData[1]<<8);
  height = pMapData[2]+(pMapData[3]<<8);

  m_blockFlag = new BlockFlag_t[width * height];
  CHECK_NEW_MEMORY(m_blockFlag);
  m_tileLayer = new TileLayer(width, height);
  CHECK_NEW_MEMORY(m_tileLayer);
  m_stileLayer = new TileLayer(width, height);
  CHECK_NEW_MEMORY(m_stileLayer);
  m_objectLayer = new TileLayer(width, height);
  CHECK_NEW_MEMORY(m_objectLayer);

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

    char path[512];
    int x, y;
    x = i / height;
    y = i % height;

    if(tileNo >= 0)
    {
      sprintf(path, "%s\\tiles\\%06d.bmp", MAP_PIC_PATH, tileNo);
      m_tileLayer->setTile(x, y, path);
    }

    if(stileNo >= 0)
    {
      sprintf(path, "%s\\stiles\\%06d.bmp", MAP_PIC_PATH, stileNo);
      m_stileLayer->setTile(x, y, path);
    }

    if(objectNo >= 0)
    {
      sprintf(path, "%s\\object%d\\%06d.bmp", MAP_PIC_PATH, objectClassNo, objectNo);
      m_objectLayer->setTile(x, y, path);
    }
  }

  //ÐÞÕýTile
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
  int y = pos.y /32;

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
      if(i < x1 || i > x2 || y < y1 || y > y2)
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

void * MapLayer::backDealTilesData(void *p)
{
  MapLayer *pMapLayer = static_cast<MapLayer *>(p);
  while(1)
  {
    Sleep(200);
    CCPoint pos = pMapLayer->getPosition();
    int x = pos.x / 48;
    int y = pos.y /32;

    x = -x;
    y = -y;

    int x1, x2, y1, y2;

    x1 = x - 20;
    x2 = x + 20;
    y1 = y - 20;
    y2 = y + 20;

    CHECK_ZERO(x1);
    CHECK_ZERO(y1);

    for(int i = x1; i < x2; i++)
    {
      for(int j = y1; j < y2; j++)
      {
        pMapLayer->m_tileLayer->loadTileData(i, j);
        pMapLayer->m_stileLayer->loadTileData(i, j);
        pMapLayer->m_objectLayer->loadTileData(i, j);
      }
    }
  }
  return NULL;
}
