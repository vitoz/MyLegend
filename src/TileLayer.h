#ifndef __TILELAYER_H
#define __TILELAYER_H
#include <string>
#include "cocos2d.h"

class TileSprite;

using std::string;

class TileLayer : public cocos2d::CCLayer
{
public:
  TileLayer(int width, int height);
  void setTile(int x, int y, const string path);
  void clearTile(int x, int y);
  void loadTile(int x, int y);
  
private:
  int m_width;
  int m_height;
  TileSprite **m_pTileSprites;
};

#endif
