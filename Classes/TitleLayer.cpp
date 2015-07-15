
#include "SimpleAudioEngine.h" 
#include "ME.h"
#include "SE.h"
#include "Tex.h"
#include "TitleScene.h"
#include "TitleLayer.h"
#include "GLUtil.h"
#include "GameScene.h"

using namespace CocosDenshion;


TitleLayer::TitleLayer()
{
}
TitleLayer::~TitleLayer()
{
}

bool TitleLayer::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto bg = CCSprite::createWithSpriteFrameName(Tex::title_Bg);
	this->addChild(bg);
	bg->setAnchorPoint(ccp(0, 0));
	bg->setPosition(0, 0);


	mWitch = CCSprite::createWithSpriteFrameName(Tex::title_Witch);
	this->addChild(mWitch);
	mWitch->setAnchorPoint(ccp(0, 0));
	mWitch->setPosition(10, 0);
	 
	mTitle = CCSprite::createWithSpriteFrameName(Tex::tilte_Title);
	this->addChild(mTitle);
	mTitle->setPosition(600, 350);

	auto cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	auto mStart = MenuItemImage::create();
	mStart->setNormalSpriteFrame(cache->spriteFrameByName(Tex::title_Start));
	mStart->setCallback([&](Ref* ref)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(SE::Click);

		CCDirector::sharedDirector()->replaceScene(GameScene::create());
	});
	mStart->setPosition(500, 100);

	auto menu = CCMenu::create(mStart, NULL);
	this->addChild(menu);
	menu->setPosition(0, 0);

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(ME::Title, true);

	return true;
}


void TitleLayer::onEnter()
{
	Layer::onEnter();

	mWitch->setPosition(-mWitch->getContentSize().width, 0);
	mWitch->stopAllActions();

	auto witchAction = Sequence::create(
		MoveTo::create(0, ccp(-mWitch->getContentSize().width, 0)),
		MoveTo::create(2, ccp(10, 0)),
		CallFuncN::create([&](Node* sender){}), NULL);

	mWitch->runAction(witchAction);

	ActionInterval* delayAaction;
	  
	delayAaction = Sequence::create(DelayTime::create(2),
		CallFunc::create(this,callfunc_selector(TitleLayer::callBack)), NULL);
	auto node = Node::create();
	this->addChild(node);
	node->runAction(RepeatForever::create(delayAaction));

}

void TitleLayer::onExit()
{
	Layer::onExit();
}
void TitleLayer::callBack()
{
	auto scaleAction = Sequence::create(
		ScaleTo::create(0, 1, 1),
		ScaleTo::create(0.2f, 2, 2),
		EaseBounceOut::create(ScaleTo::create(0.2f, 1, 1)),
		CallFuncN::create([&](Node* sender)
	{
	}), NULL);

	auto flipAction = Sequence::create(
		ScaleTo::create(0, 1, 1),
		ScaleTo::create(0.1f, 0, 1),
		ScaleTo::create(0.1f, 1, 1),
		CallFuncN::create([&](Node* sender)
	{
	}), NULL);
	if (GLUtil::random(0, 100)<30)
		mTitle->runAction(Repeat::create(flipAction,2));
	else
		mTitle->runAction(scaleAction);
	 
	
}

