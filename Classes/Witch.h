#pragma once
#include <iostream>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Witch : public CCNode
{
public:
	virtual bool init();
	void start();
	void  jump();
	void drop();
	void slowDrop();
	void setVelocity(float);
	void reset();
	void pause();
	void playAnimation();
	CCSprite* getSprite();
	Rect getBoundingBox();  
	CREATE_FUNC(Witch);
	CCSprite* mWitch;

	bool mIsJump;
private :
	Witch(void);
	~Witch(void);
	  
	
	
};