#ifndef __PLAYINGSCENE_H
#define __PLAYINGSCENE_H

#include "GameScene.h"

class MapLayer;

class PlayingScene : public GameScene
{
public:
  bool load(const char *path);
  void update(cocos2d::CCTime dt);
  
private:
  MapLayer *m_pMapLayer;
  void onKeyPressEvent(int key);
  void onKeyReleaseEvent(int key);
};


#endif