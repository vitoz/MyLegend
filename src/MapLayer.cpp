#include "stdafx.h"
#include "MapLayer.h"
#include "Util.h"
#include "TileLayer.h"

using namespace cocos2d;

bool MapLayer::init(const std::string path)
{
  TileLayer *player = new TileLayer(100, 100);
  for(int i = 0; i < 10; i++)
    for(int j = 0; j < 10; j++)
    {
      player->setTile(i, j, "d:/a.bmp");
      player->loadTile(i, j);
    }
  this->addChild(player);

  CCMenuItem *down = CCMenuItemFont::create("down", this, menu_selector(MapLayer::moveCallback));
  CCMenuItem *up = CCMenuItemFont::create("up", this, menu_selector(MapLayer::moveCallback));
  CCMenuItem *left = CCMenuItemFont::create("left", this, menu_selector(MapLayer::moveCallback));
  CCMenuItem *right = CCMenuItemFont::create("right", this, menu_selector(MapLayer::moveCallback));
  CCMenu *pMenu = CCMenu::create(down, up, left, right, NULL);
  pMenu->alignItemsHorizontallyWithPadding(50);
  this->addChild(pMenu);

  return false;
}

void MapLayer::moveCallback(CCObject *pSender)
{
  CCPoint pos;
  pos = getPosition();
  pos.x ++;
  setPosition(pos);
}
