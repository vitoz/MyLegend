#ifndef __PLAYERSPRITE_H
#define __PLAYERSPRITE_H

#include <string>
#include "util.h"
#include "cocos2d.h"

class PlayerSprite : public cocos2d::CCSprite
{
  enum PlayerAct
  {
    STAND,
    WALK,
    RUN,
    NORMAL_ATTACK,
    FULLHAND_ATTACK,
    FORCE_ATTACK,
    MAGIC,
    HURT,
    DIE,
    COUNT,
  };

  enum PlayerDirection
  {
    UP,
    UPRIGHT,
    RIGHT,
    DOWNRIGHT,
    DOWN,
    DOWNLEFT,
    LEFT,
    UPLEFT,
  };

public:
  PlayerSprite();
  ~PlayerSprite();
  void move(cocos2d::CCPoint offset);
  void doSkill(int id);
  void attack();
  void setBasePos(const cocos2d::CCPoint &basePos);

private:
  cocos2d::CCPoint m_basePos;
  bool m_isDoing;
  cocos2d::CCPoint m_pos;
  cocos2d::CCPoint m_tarPos;
  int m_direction;
  int m_act;
  TextureInfo m_clothTextureWithOffsets[600];
  
  //property
  int m_ad;
  int m_ap;
  int m_adDef;
  int m_apDef;
  int m_suckBlood;
  int m_critRate;
  int m_cirtDamage;
  int m_attackSpeed;
  int m_moveSpeed;
  int m_decreaseCD;

  void update(float delta);
  void checkMove(float dt);
  void checkAct(float dt);
  void setDirection(const cocos2d::CCPoint &offset);
};

#endif