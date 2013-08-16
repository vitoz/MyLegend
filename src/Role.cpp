#include "Role.h"
#include "VFile.h"
#include "PlayingScene.h"
#include "TextureCache.h"

USING_NS_CC;

Role::Role(const char *roleInfoPath)
  :m_isBusy(false),
  m_position(0, 0),
  m_destination(0, 0),
  m_curAction(STAND),
  m_direction(DOWN),
  m_textureBaseNo(0)
{
  CCTexture2D *ptexture = new CCTexture2D();
  ptexture->autorelease();
  initWithTexture(ptexture);
  scheduleUpdate();
  setAnchorPoint(CCPointZero);
  setPosition(CCPointZero);

  //local TextureBasePath = "D:\project\cocos2dx\Debug.win32\data\equpment\cloth";
  if(Util::lua()->DoFile(roleInfoPath) == 0)
  {
    m_textureBaseNo = Util::lua()->GetGlobal("TextureBaseNo").GetInteger();
    m_actionInfos[STAND].textureNo = Util::lua()->GetGlobal("StandTextureNo").GetInteger();
    m_actionInfos[STAND].textureCount = Util::lua()->GetGlobal("StandTextureCount").GetInteger();
    m_actionInfos[STAND].lastTime = 0.5;
    m_actionInfos[MOVE].textureNo = Util::lua()->GetGlobal("MoveTextureNo").GetInteger();
    m_actionInfos[MOVE].textureCount = Util::lua()->GetGlobal("MoveTextureCount").GetInteger();
    m_actionInfos[MOVE].lastTime = 0.5;
    m_actionInfos[ATTACK].textureNo = Util::lua()->GetGlobal("AttackTextureNo").GetInteger();
    m_actionInfos[ATTACK].textureCount = Util::lua()->GetGlobal("AttackTextureCount").GetInteger();
    m_actionInfos[ATTACK].lastTime = Util::lua()->GetGlobal("AttackSpeed").GetFloat();
    m_actionInfos[SKILL].textureNo = Util::lua()->GetGlobal("SkillTextureNo").ToInteger();
    m_actionInfos[SKILL].textureCount = Util::lua()->GetGlobal("SkillTextureCount").ToInteger();
    m_actionInfos[SKILL].lastTime = Util::lua()->GetGlobal("SkillSpeed").GetFloat();
    m_moveSpeed = Util::lua()->GetGlobal("MoveSpeed").GetInteger();
    m_textureBasePath = Util::lua()->GetGlobal("TextureBasePath").GetString();
  }
}

Role::~Role()
{

}

bool Role::moveWithOffset( const CCPoint &offset )
{
  m_curAction = MOVE;
  setDirection(offset);
  m_destination = m_position + offset;
  return true;
}

bool Role::moveWithPosition( const CCPoint &position )
{
  m_destination = position;
  return true;
}

void Role::doSkill( int id )
{

}

void Role::attack()
{

}

void Role::setStandPosition( const CCPoint &basePos )
{

}

void Role::update( float delta )
{
  checkMove(delta);
  checkAction(delta);
}

void Role::checkMove( float dt )
{
  static double sinValue, cosValue, disValue = 0;
  static CCPoint lastTarPos;
  if(m_position != m_destination)
  {
    CCPoint diff(0, 0);
    CCPoint offset(0, 0);

    diff = m_position - m_destination;
    float moveDistance = dt * m_moveSpeed;

    if(disValue == 0 || lastTarPos != m_destination)
    {
      lastTarPos = m_destination;
      disValue = sqrt(diff.x * diff.x + diff.y * diff.y);
      cosValue = diff.y / disValue;
      sinValue = diff.x / disValue;
    }

    if(disValue < moveDistance)
    {
      m_curAction = STAND;
      disValue = 0;
      offset = diff;
    }
    else
    {
      disValue -= moveDistance;
      offset.x = moveDistance * sinValue;
      offset.y = moveDistance * cosValue;
    }

    m_position = m_position - offset;
    PlayingScene *pScence = static_cast<PlayingScene *>(GameScene::current());
    pScence->moveMap(offset);
  }
}

void Role::doAction( int action, float lastTime, bool repeat )
{

}

void Role::checkAction( float dt )
{
  static int lastAction = STAND;
  static float pastTime = 0;

  //¶¯×÷ÇÐ»»
  if(lastAction != m_curAction)
  {
    lastAction = m_curAction;
    pastTime = 0;
  }

  float stopTime = 0.5f;
  if(pastTime >= stopTime)
  {
    pastTime = 0;
  }
  int textureRefNo = m_direction * 8 \
    + m_actionInfos[m_curAction].textureNo \
    + (pastTime / stopTime * m_actionInfos[m_curAction].textureCount);
  int textureAbsNo = m_textureBaseNo + textureRefNo;

  TextureInfo *pTexOffset = &m_noToTextureInfo[textureRefNo];
  if(pTexOffset->pTexture == NULL)
  {
    char path[MAX_PATH];
    sprintf(path, "%s\\%06d.bmp", m_textureBasePath.c_str() , textureAbsNo);
    pTexOffset->pTexture = TextureCache::get(path);
    pTexOffset->path = path;
    VFile file;
    sprintf(path, "%s\\Placements\\%06d.txt", m_textureBasePath.c_str(), textureAbsNo);
    file.open(path, "r");
    char tmp[VFILE_LINE_MAX];
    file.readLine(tmp);
    sscanf(tmp, "%d\n", &pTexOffset->x);
    file.readLine(tmp);
    sscanf(tmp, "%d\n", &pTexOffset->y);
    file.close();
  }

  if(pTexOffset->pTexture != NULL)
  {
    setTexture(pTexOffset->pTexture);
    CCPoint pos = m_position;
    pos.x += pTexOffset->x;
    pos.y += pTexOffset->y;
    setPosition(pos);
    CCRect rect = CCRectZero;
    rect.size = pTexOffset->pTexture->getContentSize();
    setTextureRect(rect);
  }
  pastTime += dt;
}

void Role::setDirection( const cocos2d::CCPoint &offset )
{
  int corX = offset.x;
  int corY = offset.y;

  double degree = atan2(corY, corX) * 180 / 3.14159;

  if((degree <= -157.5 && degree > -180) || (degree > 157.5 && degree < 180))
    m_direction =  LEFT;
  if(degree <= 157.5 && degree > 112.5)
    m_direction = UPLEFT;
  if(degree <= 112.5 && degree > 67.5)
    m_direction = UP;
  if(degree <= 67.5 && degree > 22.5)
    m_direction = UPRIGHT;
  if(degree <= 22.5 && degree > -22.5)
    m_direction = RIGHT;
  if(degree <= -22.5 && degree > -67.5)
    m_direction = DOWNRIGHT;
  if(degree <= -67.5 && degree > -112.5)
    m_direction = DOWN;
  if(degree <= -112.5 && degree > -157.5)
    m_direction = DOWNLEFT;
}
