#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Cloud : public CCNode
{
public:
	Cloud(void);
	~Cloud(void);
	CREATE_FUNC(Cloud);
	virtual bool init();
	void setCloud(int);
	void playAnime();
	int getScore();
	CCSprite* getSprite(); 
	Rect getBoundingBox();


private:
	int mIndex;
	Sprite* mSprite; 
	Vector<Sprite*> mClouds;
};
