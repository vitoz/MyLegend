#ifndef __GameScene_H
#define __GameScene_H

#include "cocos2d.h"

class GameScene : public cocos2d::CCScene
{
  enum 
  {
    LOGO = 0,
    MENU,
  };

public:
  virtual bool init();
  virtual void onKeyPressEvent(int key);
  virtual void onKeyReleaseEvent(int key);

protected:
  virtual void update(cocos2d::CCTime dt);

  //////////////////////////////////////////////////////////////////////////
  ///static
  //////////////////////////////////////////////////////////////////////////
private:
  static GameScene *m_current;

public:
  static GameScene *current();
  static void firstSetCurrentScence(GameScene *scene);
  static void replaceCurrentScence(GameScene *scene);
  static void replaceCurrentScenceWithDestory(GameScene *scence);
  static GameScene *create(GameScene * pScene);
  static GameScene *create(int type);
  static GameScene *create(const char *path);
};

#endif