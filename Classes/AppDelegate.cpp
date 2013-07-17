#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "MapLayer.h"
#include "GameScene.h"
#include "PlayingScene.h"
#include "TileLayer.h"

const int KEY_PRESS = 256;
const int KEY_RELEASE = 257;

using namespace CocosDenshion;

USING_NS_CC;  

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
  SimpleAudioEngine::end();
}

void Win32KeyHook( UINT message,WPARAM wParam, LPARAM lParam )
{
  CCLog("Win32KeyHook message %d wParam %d lParam %d", message, wParam, lParam);

  GameScene *pScence = GameScene::current();
  if(pScence == NULL)
  {
    return;
  }

  if(message == KEY_PRESS)
  {
    pScence->onKeyPressEvent(static_cast<int>(wParam));
  }
  else if(message == KEY_RELEASE)
  {
    pScence->onKeyReleaseEvent(static_cast<int>(wParam));
  }
}

bool AppDelegate::applicationDidFinishLaunching()
{
  // initialize director
  CCDirector *pDirector = CCDirector::sharedDirector();
  pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

  // set Win32 Key Hook
  CCEGLView::sharedOpenGLView()->setAccelerometerKeyHook(Win32KeyHook);

  // turn on display FPS
  pDirector->setDisplayStats(true);

  // set FPS. the default value is 1.0/60 if you don't call this
  pDirector->setAnimationInterval(1.0 / 30);

  PlayingScene *pScence = static_cast<PlayingScene *>(GameScene::create("a.bmp"));
  pScence->load(NULL);

  GameScene::firstSetCurrentScence(pScence);
  //pDirector->runWithScene(GameScene::current());


  // register lua engine
  //CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
  //CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

  // #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  //     CCString* pstrFileContent = CCString::createWithContentsOfFile("hello.lua");
  //     if (pstrFileContent)
  //     {
  //         pEngine->executeString(pstrFileContent->getCString());
  //     }
  // #else
  //     std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("hello.lua");
  //     pEngine->addSearchPath(path.substr(0, path.find_last_of("/")).c_str());
  //     pEngine->executeScriptFile(path.c_str());
  // #endif
  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
  CCDirector::sharedDirector()->stopAnimation();

  SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
  CCDirector::sharedDirector()->startAnimation();

  SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
