#include "GameLayer.h"
#include "SimpleAudioEngine.h" 
#include "GameData.h"
#include "Tex.h"
#include "ME.h"
#include "SE.h"


using namespace CocosDenshion;
GameLayer* GameLayer::mInstance = NULL;

GameLayer* GameLayer::getInstance()
{
	if (mInstance == NULL)
	{
		mInstance = new GameLayer();
		mInstance->init();
	}
	return mInstance;
}

void GameLayer::delInstance()
{
	CC_SAFE_DELETE(mInstance);
}

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{

}



bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	} 
	registerTouch(); 
	 
	

	mGameBGLayer = GameBGLayer::create();
	this->addChild(mGameBGLayer);
	mFloorLayer = FloorLayer::create();
	this->addChild(mFloorLayer); 
	mHudLayer = HudLayer::create();
	this->addChild(mHudLayer);
	mResultLayer = ResultLayer::create();
	this->addChild(mResultLayer);

	mWitch = Witch::create();
	this->addChild(mWitch);
	mWitch->setPosition(200, 300);

	mTapStart = CCSprite::createWithSpriteFrameName(Tex::tapstart);
	this->addChild(mTapStart);
	mTapStart->setPosition(400, 240);
	mGameOver = Sprite::createWithSpriteFrameName(Tex::gameover);
	this->addChild(mGameOver);
	mGameOver->setPosition(400, 240);
	
	auto cache = CCSpriteFrameCache::sharedSpriteFrameCache();


	auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(Tex::Snow);
	auto mEmitter = ParticleSystemQuad::createWithTotalParticles(200);
	mEmitter->setTextureWithRect(frame->getTexture(), frame->getRect());
	mEmitter->setDuration(-1);
	mEmitter->setPosition(ccp(1100, 600));
	mEmitter->setPosVar(ccp(700, 0));
	mEmitter->setGravity(ccp(-400, -200));
	mEmitter->setStartColorVar(Color4F(0, 0, 0, 0));
	mEmitter->setStartColor(Color4F(1, 1, 1, 1));
	mEmitter->setEndColor(Color4F(1, 1, 1, 1));
	mEmitter->setStartSize(30);
	mEmitter->setStartSizeVar(10);
	mEmitter->setEmissionRate(50);
	mEmitter->setLife(4);
	mEmitter->setSpeedVar(100);
	this->addChild(mEmitter);

	return true;
}

void GameLayer::onEnter()
{
	CCLayer::onEnter();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(ME::Game, true);//开始播放背景音乐，true表示循环  
	//SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);//设置音量0.0-1.0 
	
	CCLog("GameLayeronEnter;");
	reset();
}

void GameLayer::onExit()
{
	CCLayer::onExit(); 
}

 
void GameLayer::registerTouch()
{
	CCLOG("Register touch");
	auto dispatcher = Director::getInstance()->getEventDispatcher();
 
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	listener->setSwallowTouches(true);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	this->setTouchEnabled(true);
}

bool GameLayer::onTouchBegan(Touch *touch, Event *unused_event)
{   
	if (mIsGameOver == true)
		return true;
	start();
	mWitch->drop();
	return true;
}
void GameLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	 
}
void GameLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	 
}

void GameLayer::start()
{
	if (mIsStart == true)
		return;
	
	mIsStart =true;
	mTapStart->setVisible(false);
	mFloorLayer->start();
	mGameBGLayer->start();
	mWitch->start();
	
// 	auto _schedule = Director::getInstance()->getScheduler();
// 	_schedule->schedule([](float tm){log("%f", tm); }, this, 1.0f, !this->isRunning(), "gameupdate");
}
void GameLayer::reset()
{
	mIsStart = false;
	mIsGameOver = false;
	mFloorLayer->reset();
	mGameBGLayer->reset();
	mWitch->reset();
	mResultLayer->hide();
	mIsGameOver = false;
	mTapStart->setVisible(true);
	mGameOver->setVisible(false);

	GameData::getInstance()->setScore(0);
	mHudLayer->setScore(0);
	
	mResultLayer->hide(); 
	mWitch->setPosition(200, 300); 
	this->schedule(schedule_selector(GameLayer::collideUpdate), 0.01f);
	this->schedule(schedule_selector(GameLayer::gameUpdate), 0.01f);
 
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(ME::Game, true);
}

void GameLayer::collideUpdate(float time)
{
	Vector<Cloud*> clouds = mFloorLayer->getClouds();
	 

	for (int i = 0; i < clouds.size(); i++)
	{
		Cloud*  cloud = clouds.at(i);
		if ((cloud->getBoundingBox().intersectsRect(mWitch->getBoundingBox())))
		{
			mWitch->jump();
			cloud->playAnime();
			GameData::getInstance()->setScore(GameData::getInstance()->getScore() + cloud->getScore());
			mHudLayer->setScore(GameData::getInstance()->getScore());
			break;
		}
	}
}

void GameLayer::gameUpdate(float dt)
{
	 
	if (mWitch->getPosition().y < 0)
	{
		gameOver(); 
		this->unschedule(schedule_selector(GameLayer::gameUpdate));
	}
}

void GameLayer::gameOver()
{
	//CCDirector::sharedDirector()->pause();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->playEffect(SE::GameOver);
	mIsGameOver = true;
	mFloorLayer->pause();
	mGameBGLayer->pause();
	mGameOver->setVisible(true);
	mGameOver->setPosition(400, 720);

	auto move= MoveTo::create(1.0f,ccp(400,240));
	auto delay = DelayTime::create(3);
 
	auto callback = CallFunc::create([&]()
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(ME::Result,true);
		mResultLayer->show(); 
		mResultLayer->showResult();
		mWitch->pause();
	});
	auto sequence = CCSequence::create(EaseBounceOut::create(move), delay, callback,NULL);
	mGameOver->runAction(sequence);
}