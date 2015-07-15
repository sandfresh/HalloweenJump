#include "Cloud.h"
#include "Tex.h"

Cloud::Cloud()
{

}

Cloud::~Cloud()
{

}

bool Cloud::init()
{
	CCAnimation* animation = CCAnimation::create(); 
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(Tex::MainFloor3_2));
	
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "cloud3");

	CCAnimate* animate = CCAnimate::create(animation);
	CCSprite *sprite = CCSprite::createWithSpriteFrameName(Tex::MainFloor3_1);
	this->addChild(sprite);

	sprite->setPosition(ccp(100, 200));
	mClouds.pushBack(sprite);
	/**********************************************************************/
	animation = CCAnimation::create(); 
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(Tex::MainFloor2_2));
	
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "cloud2");

	animate = CCAnimate::create(animation);
	sprite = CCSprite::createWithSpriteFrameName(Tex::MainFloor2_1);
	this->addChild(sprite);

	sprite->setPosition(ccp(100, 200));

	mClouds.pushBack(sprite);
	/**********************************************************************/

	animation = CCAnimation::create(); 

	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(Tex::MainFloor1_2));
	
	
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "cloud1");

	animate = CCAnimate::create(animation);
	sprite = CCSprite::createWithSpriteFrameName(Tex::MainFloor1_1);
	this->addChild(sprite);

	sprite->setPosition(ccp(100, 200));

	mClouds.pushBack(sprite);
	/**********************************************************************/

	for (int i = 0; i < mClouds.size(); i++)
	{
		mClouds.at(i)->setAnchorPoint(ccp(0, 0));
		mClouds.at(i)->setPosition(ccp(0, 0));
		mClouds.at(i)->setVisible(false);
	}

	mIndex = 0;
	return true;

}

void Cloud::setCloud(int index)
{
	mIndex = index;
	for (int i = 0; i < mClouds.size(); i++)
	{
		mClouds.at(i)->setVisible(false);
	}
	mSprite = mClouds.at(index);
	mSprite->setVisible(true);
}

CCSprite* Cloud::getSprite()
{
	return this->mSprite;
}


Rect Cloud::getBoundingBox()
{
	Rect rect = this->mSprite->boundingBox();
	Point pos = this->convertToWorldSpace(rect.origin);
	return Rect(pos.x, pos.y + rect.size.height*0.3f, rect.size.width, rect.size.height*0.3f);
}
void Cloud::playAnime()
{

	CCAnimation *animation;
	switch (mIndex)
	{
	case 0:
		animation = CCAnimationCache::sharedAnimationCache()->animationByName("cloud3");
		animation->setLoops(1);
		animation->setRestoreOriginalFrame(true);
		animation->setDelayPerUnit(0.15f);
		mSprite->runAction(CCAnimate::create(animation));
		break;
	case 1:
		animation = CCAnimationCache::sharedAnimationCache()->animationByName("cloud2");
		animation->setLoops(1);
		animation->setRestoreOriginalFrame(true);
		animation->setDelayPerUnit(0.15f);
		mSprite->runAction(CCAnimate::create(animation)); 
		break;
	case 2:
		animation = CCAnimationCache::sharedAnimationCache()->animationByName("cloud1");
		animation->setRestoreOriginalFrame(true);
		animation->setDelayPerUnit(0.15f);
		animation->setLoops(1);
		mSprite->runAction(CCAnimate::create(animation)); 
		break;
	}
	 

	CCActionInterval*   action = CCMoveBy::create(0.1f,ccp(0,-20));
	CCActionInterval*   action2 = CCMoveBy::create(0.1f, ccp(0, 20));

	CCSequence* sqn = CCSequence::create(action, action2,NULL);
	
	mSprite->runAction(sqn);
}

int Cloud::getScore()
{
	return (mIndex +1)* 1000;
}