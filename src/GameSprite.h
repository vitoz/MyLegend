#ifndef __TILE_H
#define __TILE_H
#include <string>
#include "cocos2d.h"

using std::string;

class GameSprite : public cocos2d::CCSprite
{
public:
  GameSprite(const string path, const cocos2d::CCPoint &pos);
  ~GameSprite();
  bool loadTexture();
  void cleanup();

private:
  string m_path;
  cocos2d::CCPoint m_pos;
};

#endif
