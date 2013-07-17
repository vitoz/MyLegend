#include "PlayingScene.h"
#include "MapLayer.h"

USING_NS_CC;

bool PlayingScene::load( const char *path )
{
  m_pMapLayer = new MapLayer();
  m_pMapLayer->load("D:\\project\\cocos2dx\\Debug.win32\\data\\map\\3.map");
  addChild(m_pMapLayer);
  return true;
}

void PlayingScene::update( cocos2d::CCTime dt )
{
  GameScene::update(dt);

  m_pMapLayer->update(dt);
}

void PlayingScene::onKeyPressEvent( int key )
{
  CCPoint pos = m_pMapLayer->getPosition();

  switch(key)
  {
  case 37:
    pos.x -= 15;
    break;
  case 38:
    pos.y += 15;
    break;
  case 39:
    pos.x += 15;
    break;
  case 40:
    pos.y -= 15;
    break;
  }
  m_pMapLayer->setPosition(pos);
}

void PlayingScene::onKeyReleaseEvent( int key )
{

}
