#include "AppDelegate.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "SimpleAudioEngine.h" 
#include "SE.h"
#include "ME.h"

USING_NS_CC;

using namespace  CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLView::create("My Game");
		director->setOpenGLView(glview);
	}

	glview->setDesignResolutionSize(800, 480, ResolutionPolicy::SHOW_ALL);

	setResourceSearchResolution();
	preLoadResource();

	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);


	// create a scene. it's an autorelease object
//	auto scene = GameScene::create();
	auto scene = TitleScene::create();

	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	 SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	 SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
void AppDelegate::setResourceSearchResolution(){
	std::vector<std::string> paths;
	paths.push_back("fonts");
	paths.push_back("images");
	paths.push_back("music");
	paths.push_back("sound");
	FileUtils::getInstance()->setSearchResolutionsOrder(paths);
}
void AppDelegate::preLoadResource()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("gamescene.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("gameobject.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("menuobject.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("titlescene.plist");

	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(ME::Game);
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(ME::Title);
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(ME::Result);
	SimpleAudioEngine::sharedEngine()->preloadEffect(SE::Death);
}