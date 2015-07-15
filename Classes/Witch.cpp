#include "SimpleAudioEngine.h" 
#include "Witch.h"
#include "Tex.h"
#include "SE.h"
using namespace CocosDenshion;

Witch::Witch()
{
}

Witch::~Witch()
{ 
}

bool Witch::init()
{ 
	mWitch = CCSprite::createWithSpriteFrameName(Tex::Player_0);
	this->addChild(mWitch);
	CCLOG("Witch Width:%f", mWitch->getContentSize().width);
	mWitch->setPosition(0, 0);
	

	PhysicsBody *body = PhysicsBody::create();
	body->setTag(1);
	this->setPhysicsBody(body);
	body->addShape(PhysicsShapeBox::create(Size(mWitch->getContentSize().width, mWitch->getContentSize().height)));
	
	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setGravityEnable(false); 
	
	return true;
}

void Witch::drop()
{
	CCLog("Drop");
	setVelocity(-800);
}
void Witch::slowDrop()
{
	mIsJump = false;
	setVelocity(-200);
}
void Witch::jump()
{ 
   setVelocity(1000);
	mIsJump = true;
	mWitch->stopActionByTag(1);
	mWitch->setRotation(0);
  
	auto callback = CallFunc::create([&](){slowDrop(); });
	CCActionInterval*   action = CCRotateBy::create(0.3f, 360);
	 
	CCSequence* sqn = CCSequence::create(action, callback, NULL);
	sqn->setTag(1);
	mWitch->runAction(sqn);

	SimpleAudioEngine::sharedEngine()->playEffect(SE::Jump);
}

void Witch::setVelocity(float value)
{
   this->getPhysicsBody()->setVelocity(Vect(0, value));
}

CCSprite* Witch::getSprite()
{
	return mWitch;
}

Rect Witch::getBoundingBox()
{
	Rect rect = this->mWitch->boundingBox();
	Point pos = this->convertToWorldSpace(rect.origin);
	return Rect(pos.x, pos.y, rect.size.width, rect.size.height*0.2f);
}

void Witch::start()
{
}
void Witch::reset()
{
	setVelocity(0);
	mWitch->stopAllActions();
	playAnimation();
}
void Witch::pause()
{
	setVelocity(0);
}

void Witch::playAnimation()
{
	CCAnimation* animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(Tex::Player_0));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(Tex::Player_1));
	CCAnimate* animate = CCAnimate::create(animation);//帧动画  

	mWitch->runAction(CCRepeatForever::create(animate));

}