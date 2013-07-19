#ifndef __MAPLAYER_H
#define __MAPLAYER_H
#include <string>
#include "cocos2d.h"

class TileLayer;

typedef struct BlockFlag_st
{
  bool moveable:1;
  bool door:1;
}BlockFlag_t;

class MapLayer : public cocos2d::CCLayer
{
public:
  ~MapLayer();
  bool load(const char * path);
  void moveCallback(CCObject *pSender);
  void update(cocos2d::CCTime dt);
  void cleanup();

private:
  int m_width;
  int m_height;
  BlockFlag_t *m_blockFlag;
  TileLayer *m_objectLayer;
  TileLayer *m_tileLayer;
  TileLayer *m_stileLayer;

  bool loadMapFile(const char *path);

  //////////////////////////////////////////////////////////////////////////
  ///static
  //////////////////////////////////////////////////////////////////////////
public:
  static void *backDealTilesData(void *p);

};

#endif
