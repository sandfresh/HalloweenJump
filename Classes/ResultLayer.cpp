#include "SimpleAudioEngine.h" 
#include "ResultLayer.h"
#include "GameLayer.h"
#include "Tex.h"
#include "SE.h"
#include "TitleScene.h"
#include "GameData.h"
using namespace CocosDenshion;
ResultLayer::ResultLayer()
{
}
ResultLayer::~ResultLayer()
{
}

bool ResultLayer::init()
{

	if (!Layer::init())
	{
		return false;
	}
	this->setZOrder(50);
	auto bg = Sprite::createWithSpriteFrameName(Tex::resultBG);
	this->addChild(bg);
	bg->setPosition(400, 240);
	auto cache = CCSpriteFrameCache::sharedSpriteFrameCache();

	auto resultTitle = CCSprite::createWithSpriteFrameName(Tex::resutTitle);
	this->addChild(resultTitle);
	resultTitle->setPosition(ccp(400, 400));
	auto resultFrame = CCSprite::createWithSpriteFrameName(Tex::resutlFrame);
	this->addChild(resultFrame);
	resultFrame->setPosition(ccp(400,240));

	for (int i = 0; i < 3; i++)
	{
		auto label = Label::createWithSystemFont("0", "Arial", 40 );
		resultFrame->addChild(label);
		label->setAnchorPoint(ccp(0.5f,0.5f));
	 
		label->setHorizontalAlignment(TextHAlignment::CENTER);
		label->setVerticalAlignment(TextVAlignment::CENTER);
		label->setPosition(resultFrame->getContentSize().width/2,100-40*i);
		mScoreText.pushBack(label);

		label = Label::createWithSystemFont(StringUtils::toString((i + 1)) + ".", "Arial", 40);
		resultFrame->addChild(label);
		label->setAnchorPoint(ccp(0.5f, 0.5f));

		label->setHorizontalAlignment(TextHAlignment::CENTER);
		label->setVerticalAlignment(TextVAlignment::CENTER);
		label->setPosition(20, 100 - 40 * i); 
	}

	auto itemRetry = MenuItemImage::create();  
	itemRetry->setNormalSpriteFrame(cache->spriteFrameByName(Tex::retry)); 
	itemRetry->setSelectedSpriteFrame(cache->spriteFrameByName(Tex::retry));
	itemRetry->setCallback([&](Ref* ref)
	{ 
		SimpleAudioEngine::sharedEngine()->playEffect(SE::Click);
		GameLayer::getInstance()->reset();
		
	});
	itemRetry->setPosition(200, 100);

	auto itemToTitle= MenuItemImage::create();
	itemToTitle->setNormalSpriteFrame(cache->spriteFrameByName(Tex::toTotle));
	itemToTitle->setCallback([&](Ref* ref)
	{
		SimpleAudioEngine::sharedEngine()->playEffect(SE::Click); 
	 
		CCDirector::sharedDirector()->replaceScene(TitleScene::create());
	});
	itemToTitle->setPosition(600, 100);

	   
	auto menu = CCMenu::create(itemRetry,itemToTitle,NULL);
	this->addChild(menu);
	menu->setPosition(0, 0);
	 
	auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(Tex::Star);
	mEmitter = ParticleSystemQuad::createWithTotalParticles(200);
	mEmitter->setTextureWithRect(frame->getTexture(), frame->getRect());
	mEmitter->setDuration(-1);
	mEmitter->setPosition(ccp(400,600));
	mEmitter->setPosVar(ccp(0, 0));
	mEmitter->setGravity(ccp(0, -200));
	mEmitter->setAngle(0);
	mEmitter->setAngleVar(90);
	mEmitter->setStartColorVar(Color4F(1, 1, 1, 1));
	mEmitter->setStartColor(Color4F(1, 1, 1, 1));
	mEmitter->setEndColor(Color4F(1, 1, 1, 1));
	mEmitter->setEndColorVar(Color4F(1, 1, 1, 1));
	mEmitter->setStartSize(50);
	mEmitter->setStartSizeVar(10);
	mEmitter->setEmissionRate(0);
	mEmitter->setLife(4);
	mEmitter->setSpeedVar(200);

	this->addChild(mEmitter);

	return true; 
}

void ResultLayer::onEnter()
{
	Layer::onEnter();
}

void ResultLayer::onExit()
{
	Layer::onExit();
}

void ResultLayer::hide()
{
	this->setVisible(false);
	mEmitter->setEmissionRate(0);
}
void ResultLayer::show()
{
	this->setVisible(true);

}

void ResultLayer::callback()
{
	this->setVisible(false);
}

void ResultLayer::showResult()
{

	if (GameData::getInstance()->rankHighest())
		mEmitter->setEmissionRate(50);

	vector<int> scores (GameData::getInstance()->getScores());
	for (int i = 0; i < mScoreText.size(); i++)
	{
		mScoreText.at(i)->setString(StringUtils::toString(scores.at(i)));
	}
}