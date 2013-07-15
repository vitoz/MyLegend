#ifndef __TILELAYER_H
#define __TILELAYER_H
#include <string>
#include "cocos2d.h"

using std::string;

class TileSprite;

class TileLayer : public cocos2d::CCLayer
{
public:
  TileLayer(int width, int height);
  void setTile(int x, int y, const string path);
  TileSprite *getTile(int x, int y);
  void clearTile(int x, int y);
  void removeTile(int x, int y);
  void loadTile(int x, int y);
  
private:
  int m_width;
  int m_height;
  TileSprite **m_pTileSprites;
};

#endif
