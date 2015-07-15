#include "GameBGLayer.h"
 
#include "Tex.h" 
 

GameBGLayer::GameBGLayer()
{

}

GameBGLayer::~GameBGLayer()
{

}

bool GameBGLayer::init()
{
	if (!Layer::init())
	{
		return true;
	} 
	
	mMainback1 = Sprite::createWithSpriteFrameName(Tex::MainBack1);
	this->addChild(mMainback1);
	mMainback2_1 = Sprite::createWithSpriteFrameName(Tex::MainBack2_1);
	this->addChild(mMainback2_1);
	mMainback2_2 = Sprite::createWithSpriteFrameName(Tex::MainBack2_2);
	this->addChild(mMainback2_2);
	mMainback3_1 = Sprite::createWithSpriteFrameName(Tex::MainBack3_1);
	this->addChild(mMainback3_1);
	mMainback3_2 = Sprite::createWithSpriteFrameName(Tex::MainBack3_2);
	this->addChild(mMainback3_2); 

	mMainback2_1->getTexture()->setAliasTexParameters();
	mMainback2_2->getTexture()->setAliasTexParameters();
	  
	return true;
}

void GameBGLayer::onEnter()
{
	CCLog("BGayer onEnter;"); 
    CCLayer::onEnter();
	Size size = Director::getInstance()->getVisibleSize();
	Point pos = Point(size.width / 2, size.height / 2);
	mMainback1->setPosition(pos);  
}

void GameBGLayer::onExit()
{
	CCLayer::onExit();
}
void GameBGLayer::scrollBG(float dt)
{
	mMainback2_1->setPositionX(mMainback2_1->getPositionX() - 1);
	mMainback2_2->setPositionX(mMainback2_2->getPositionX() - 1);
	mMainback3_1->setPositionX(mMainback3_1->getPositionX() - 4);
	mMainback3_2->setPositionX(mMainback3_2->getPositionX() - 4);
	if (mMainback2_1->getPositionX() <= -800)
	{
		mMainback2_1->setPositionX(800);
	}

	if (mMainback2_2->getPositionX() <= -800)
	{
		mMainback2_2->setPositionX(800);
	}
	if (mMainback3_1->getPositionX() <= -800)
	{
		mMainback3_1->setPositionX(800);
	}
	if (mMainback3_2->getPositionX() <= -800)
	{
		mMainback3_2->setPositionX(800);
	}
}

void GameBGLayer::start()
{
	this->schedule(schedule_selector(GameBGLayer::scrollBG), 0.01f);
}

void GameBGLayer::reset()
{
	mMainback2_1->setAnchorPoint(ccp(0, 0));
	mMainback2_2->setAnchorPoint(ccp(0, 0));
	mMainback3_1->setAnchorPoint(ccp(0, 0));
	mMainback3_2->setAnchorPoint(ccp(0, 0));

	mMainback2_1->setPosition(0, 0);
	mMainback2_2->setPosition(800, 0);
	mMainback3_1->setPosition(0, 0);
	mMainback3_2->setPosition(800, 0);
}

void GameBGLayer::pause()
{
	this->unschedule(schedule_selector(GameBGLayer::scrollBG));
}