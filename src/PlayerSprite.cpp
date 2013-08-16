#include "PlayerSprite.h"
#include <stdio.h>
#include <math.h>
#include "Util.h"
#include "TextureCache.h"
#include "PlayingScene.h"
#include "VFile.h"

using std::string;
USING_NS_CC;

const char *CLOTHPIC_NULL_PATH = "D:\\project\\cocos2dx\\Debug.win32\\data\\equpment\\cloth\\000000.bmp";
const char *CLOTHPIC_ROOT_PATH = "D:\\project\\cocos2dx\\Debug.win32\\data\\equpment\\cloth";

struct PlayerActFrameInfo 
{
  int frameCount;
  int textureID;
};

static const struct PlayerActFrameInfo actFrameInfo[] = {
  {4, 0},
  {6, 64},
  {6, 128},
  {6, 200},
  {6, 264},
  {8, 328},
  {6, 392},
  {3, 0},
  {4, 0},
};

PlayerSprite::PlayerSprite()
  :m_pos(0, 0)
  ,m_tarPos(0, 0)
  ,m_moveSpeed(400)
  ,m_isDoing(false)
  ,m_direction(UP)
  ,m_act(STAND)
  ,m_basePos(0, 0)
{
  scheduleUpdate();
  CCTexture2D *tex =  new CCTexture2D();
  tex->autorelease();
  initWithTexture(tex);
  setAnchorPoint(CCPoint(0, 0));
  setPosition(m_basePos);
}

PlayerSprite::~PlayerSprite()
{
   TextureCache::release(CLOTHPIC_NULL_PATH);
  for(int i = 0; i < 600; i++)
  {
    TextureCache::release(m_clothTextureWithOffsets[i].path);
  }
}

void PlayerSprite::checkAct( float dt )
{
  static int lastAct = STAND;
  static float pastTime = 0;

  //¶¯×÷ÇÐ»»
  if(lastAct != m_act)
  {
    lastAct = m_act;
    pastTime = 0;
  }

  float stopTime = 0.5f;
  if(pastTime >= stopTime)
  {
    pastTime = 0;
  }
  int textureRefNo = m_direction * 8 + actFrameInfo[m_act].textureID + (pastTime / stopTime * actFrameInfo[m_act].frameCount);
  int textureAbsNo = 20 * 600 + textureRefNo;

  TextureInfo *pTexOffset = &m_clothTextureWithOffsets[textureRefNo];
  if(pTexOffset->pTexture == NULL)
  {
    char path[MAX_PATH];
    sprintf(path, "%s\\%06d.bmp", CLOTHPIC_ROOT_PATH, textureAbsNo);
    pTexOffset->pTexture = TextureCache::get(path);
    pTexOffset->path = string(path);
    VFile file;
    sprintf(path, "%s\\Placements\\%06d.txt", CLOTHPIC_ROOT_PATH, textureAbsNo);
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
      CCPoint pos = m_pos;
      pos.x += pTexOffset->x;
      pos.y += pTexOffset->y;
      setPosition(pos);
      CCRect rect = CCRectZero;
      rect.size = pTexOffset->pTexture->getContentSize();
      setTextureRect(rect);
  }
  pastTime += dt;
}

void PlayerSprite::move( cocos2d::CCPoint offset )
{
  if(!m_isDoing)
  {
    m_tarPos = m_pos + offset;
    PlayingScene *pScence = static_cast<PlayingScene *>(GameScene::current());
    pScence->setMoveTag(m_tarPos);

    setDirection(offset);
    m_act = RUN;
  }
}

void PlayerSprite::doSkill( int id )
{

}

void PlayerSprite::attack()
{

}

void PlayerSprite::update( float delta )
{
  checkMove(delta);
  checkAct(delta);
}

void PlayerSprite::checkMove(float dt)
{
  static double sinValue, cosValue, disValue = 0;
  static CCPoint lastTarPos;
  if(m_pos != m_tarPos)
  {
    CCPoint diff(0, 0);
    CCPoint offset(0, 0);

    diff = m_pos - m_tarPos;
    float moveDistance = dt * m_moveSpeed;

    if(disValue == 0 || lastTarPos != m_tarPos)
    {
      lastTarPos = m_tarPos;
      disValue = sqrt(diff.x * diff.x + diff.y * diff.y);
      cosValue = diff.y / disValue;
      sinValue = diff.x / disValue;
    }

    if(disValue < moveDistance)
    {
      m_act = STAND;
      disValue = 0;
      offset = diff;
    }
    else
    {
      disValue -= moveDistance;
      offset.x = moveDistance * sinValue;
      offset.y = moveDistance * cosValue;
    }

    m_pos = m_pos - offset;
    PlayingScene *pScence = static_cast<PlayingScene *>(GameScene::current());
    pScence->moveMap(offset);
  }
}

void PlayerSprite::setDirection(const CCPoint &offset)
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

void PlayerSprite::setBasePos(const cocos2d::CCPoint &basePos )
{
  m_basePos = basePos;
}
