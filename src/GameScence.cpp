#include "GameScence.h"

void GameScence::onKeyPressEvent(int key)
{
  CCPoint pos = getPosition();

  switch(key)
  {
  case 37:
    pos.x -= 5;
    break;
  case 38:
    pos.y += 5;
    break;
  case 39:
    pos.x += 5;
    break;
  case 40:
    pos.y -= 5;
    break;
  }
  setPosition(pos);
}

void GameScence::onKeyReleaseEvent(int key)
{

}

//////////////////////////////////////////////////////////////////////////
///static
//////////////////////////////////////////////////////////////////////////
GameScence *GameScence::m_current = NULL;

GameScence *GameScence::current()
{
  return m_current;
}

void GameScence::replaceCurrentScence( GameScence *scence )
{
  assert(m_current != NULL);
  assert(scence != NULL);
  m_current = scence;
  CCDirector::sharedDirector()->replaceScene(scence);
}

void GameScence::replaceCurrentScenceWithDestory( GameScence *scence )
{
  m_current->removeAllChildren();
  delete m_current;
  replaceCurrentScence(scence);
}

GameScence * GameScence::create( int type )
{
  return new GameScence;
}

GameScence * GameScence::create( const char *path )
{
  return new GameScence;
}

void GameScence::firstSetCurrentScence( GameScence *scence )
{
  assert(scence != NULL);
  m_current = scence;
  CCDirector::sharedDirector()->runWithScene(scence);
}
