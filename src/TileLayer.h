#ifndef __TILELAYER_H
#define __TILELAYER_H
#include <string>
#include "cocos2d.h"

class GameSprite;

class TileLayer : public cocos2d::CCLayer
{
public:
  TileLayer(int width, int height, const std::string rootPath);
  ~TileLayer();
  void setTile(int x, int y, int no);
  GameSprite *getTile(int x, int y);
  void clearTile(int x, int y);
  void removeTile(int x, int y);
  void loadTile(int x, int y);
  void loadTileData(int x, int y);
  void cleanup();
  
protected:
  std::string m_rootPath;

private:
  int *m_tilesNo;
  int m_width;
  int m_height;
  GameSprite **m_pTileSprites;
};

#endif
