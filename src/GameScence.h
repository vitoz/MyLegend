#ifndef __GAMESCENCE_H
#define __GAMESCENCE_H

#include "cocos2d.h"
#include "IKeyEvent.h"

USING_NS_CC;

class GameScence : public CCScene
{
  enum 
  {
    LOGO = 0,
    MENU,
  };

public:
  virtual void onKeyPressEvent(int key);
  virtual void onKeyReleaseEvent(int key);

  //////////////////////////////////////////////////////////////////////////
  ///static
  //////////////////////////////////////////////////////////////////////////
private:
  static GameScence *m_current;

public:
  static GameScence *current();
  static void firstSetCurrentScence(GameScence *scence);
  static void replaceCurrentScence(GameScence *scence);
  static void replaceCurrentScenceWithDestory(GameScence *scence);
  static GameScence *create(int type);
  static GameScence *create(const char *path);
};

#endif