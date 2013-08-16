#ifndef __MONSTER__H
#define __MONSTER__H

#include "Util.h"
#include "cocos2d.h"
#include <map>
#include <string>

class Role : public cocos2d::CCSprite
{
  typedef cocos2d::CCPoint CCPoint;
  typedef std::map<int, TextureInfo> NoToTextureInfo;
  
  enum Act
  {
    STAND,
    MOVE,
    ATTACK,
    SKILL,
    ACTION_COUNT,
  };

  enum Direction
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

  struct ActionInfo
  {
    int textureNo;
    int textureCount;
    float lastTime;
  };

public:
  Role(const char *roleInfoPath);
  ~Role();
  bool moveWithOffset(const CCPoint &offset);
  bool moveWithPosition(const CCPoint &position);
  void doSkill(int id);
  void attack();
  void setStandPosition(const CCPoint &basePos);

private:
  bool m_isBusy;
  CCPoint m_position;
  CCPoint m_destination;
  int m_direction;
  int m_curAction;
  
  //DisplayInfo
  std::string m_textureBasePath;
  int m_textureBaseNo;
  ActionInfo m_actionInfos[ACTION_COUNT];
  NoToTextureInfo m_noToTextureInfo;
  
  //property
  int m_attackDamage;
  int m_abilityPower;
  int m_adDefence;
  int m_apDefence;
  int m_suckBloodRate;
  int m_critRate;
  int m_cirtDamage;
  int m_attackSpeed;
  int m_moveSpeed;
  int m_decreaseCD;

  void doAction(int action, float lastTime, bool repeat);
  void update(float delta);
  void checkMove(float dt);
  void checkAction(float dt);
  void setDirection(const CCPoint &offset);
};

#endif