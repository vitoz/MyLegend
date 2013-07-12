#ifndef __TILE_H
#define __TILE_H
#include <string>
#include "cocos2d.h"

using std::string;

class TileSprite : public cocos2d::CCSprite
{
public:
  TileSprite(const string tilePath);
  void loadTexture();
  void cleanup();

private:
  string m_tilePath;
};


#endif
