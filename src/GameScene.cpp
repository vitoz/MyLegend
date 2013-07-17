#include "GameScene.h"

#include "PlayingScene.h"
  
USING_NS_CC;

bool GameScene::init()
{
  if(!CCScene::init())
  {
    return false;
  }
  schedule(schedule_selector(GameScene::update));
  return true;
}

void GameScene::onKeyPressEvent(int key)
{
  
}

void GameScene::onKeyReleaseEvent(int key)
{

}

//////////////////////////////////////////////////////////////////////////
///static
//////////////////////////////////////////////////////////////////////////
GameScene *GameScene::m_current = NULL;

GameScene *GameScene::current()
{
  return m_current;
}

void GameScene::replaceCurrentScence( GameScene *scence )
{
  assert(m_current != NULL);
  assert(scence != NULL);
  m_current = scence;
  CCDirector::sharedDirector()->replaceScene(scence);
}

void GameScene::replaceCurrentScenceWithDestory( GameScene *scence )
{
  m_current->removeAllChildren();
  delete m_current;
  replaceCurrentScence(scence);
}

GameScene * GameScene::create(GameScene *pScene)
{
  if (pScene && pScene->init())
  {
    pScene->autorelease();
    return pScene;
  }
  else
  {
    CC_SAFE_DELETE(pScene);
    return NULL;
  }
}

GameScene * GameScene::create( int type )
{
  return NULL;
}

GameScene * GameScene::create( const char *path )
{
  GameScene *pScene = new PlayingScene();
  return create(pScene);
}

void GameScene::firstSetCurrentScence( GameScene *scence )
{
  assert(scence != NULL);
  m_current = scence;
  CCDirector::sharedDirector()->runWithScene(scence);
}

void GameScene::update(CCTime dt)
{

}
