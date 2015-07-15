#pragma once

#include "cocos2d.h" 

USING_NS_CC;


class GameBGLayer : public cocos2d::Layer
{
public:

	GameBGLayer(void);

	~GameBGLayer(void);

	CREATE_FUNC(GameBGLayer);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	void  scrollBG(float);

	void start();
	void reset();
	void pause();

	Sprite* mMainback1;
	Sprite* mMainback2_1;
	Sprite* mMainback2_2;
	Sprite* mMainback3_1;
	Sprite* mMainback3_2;

};

