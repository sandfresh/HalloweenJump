#pragma once

#include "cocos2d.h"
#include "GameLayer.h"


class GameScene : public cocos2d::Scene
{
public:

	GameScene(void);

	~GameScene(void);

	CREATE_FUNC(GameScene);

	virtual bool init();
	virtual void onEnter(); 
	virtual void onExit();
	 
	GameLayer *mGameLayer;//把GameLayer暴露给GameScene 


	int mScore;
};


