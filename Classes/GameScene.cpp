#include "GameScene.h"
#include "SimpleAudioEngine.h" 
#include "ME.h"
#include "SE.h"
#include "Tex.h"
#include "GameData.h"
using namespace CocosDenshion; 

USING_NS_CC;

 
 
GameScene::GameScene()
{
 
}

GameScene::~GameScene()
{
	CCLOG("GameSceneDelete");
	
}


bool GameScene::init()
{
	if (!Scene::initWithPhysics())
	{

		return false;
	}
	 
	this->getPhysicsWorld()->setGravity(Vect(0, -300));
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	 
	mGameLayer = GameLayer::getInstance();
	this->addChild(mGameLayer);
	mGameLayer->setPhyWorld(this->getPhysicsWorld());


	return true;
}
 
void GameScene::onEnter()
{
	CCLog("GameSceneonEnter;"); 
	CCScene::onEnter();
	 
//	this->schedule(schedule_selector(GameScene::collideUpdate), 0.01f);
//	auto _schedule = Director::getInstance()->getScheduler();
//	_schedule->schedule([](float tm){log("%f", tm); }, this, 1.0f, !this->isRunning(), "xiaota");
 
}
void GameScene::onExit()
{
	CCScene::onExit(); 
	CCLOG("GameSceneExit");
	this->removeChild(mGameLayer);
	GameLayer::delInstance();
}



 
