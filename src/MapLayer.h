#ifndef __MAPLAYER_H
#define __MAPLAYER_H
#include <string>
#include "cocos2d.h"

class MapLayer : public cocos2d::CCLayer
{
public:
  bool init(std::string path);
  void MapLayer::moveCallback(CCObject *pSender);

private:
  int m_width;
  int m_height;

};

#endif
