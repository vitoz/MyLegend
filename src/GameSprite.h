#ifndef __TILE_H
#define __TILE_H
#include <string>
#include "cocos2d.h"

using std::string;

class GameSprite : public cocos2d::CCSprite
{
public:
  GameSprite(const string path, const cocos2d::CCPoint &pos);
  bool loadTexture();
  void loadData();
  void cleanup();

private:
  int m_width;
  int m_height;
  unsigned char *m_rawData;
  string m_path;
  cocos2d::CCPoint m_pos;
};

#endif
