#pragma once

#include "cocos2d.h"  
#include "Witch.h"
#include "GameBGLayer.h"
#include "FloorLayer.h"
#include "HudLayer.h"
#include "ResultLayer.h"
#include "GameData.h"

USING_NS_CC;


class GameLayer : public cocos2d::Layer
{
public:

	GameLayer(void);

	~GameLayer(void);

	static GameLayer* getInstance();
	static GameLayer* mInstance;
	static void delInstance();
	void setPhyWorld(PhysicsWorld* world){ this->mWorld = world; }
	CREATE_FUNC(GameLayer);

	bool init();
	void onEnter();
    void onExit();
 
	void registerTouch(); 
    bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	void collideUpdate(float);
	void start();
	void reset();
	void gameUpdate(float);
	void gameOver();
	Witch *mWitch; 
	PhysicsWorld *mWorld;

	Sprite *mTapStart;
	Sprite *mGameOver;

	GameBGLayer *mGameBGLayer;
	FloorLayer *mFloorLayer;
	HudLayer *mHudLayer;
	ResultLayer *mResultLayer;

	bool mIsGameOver;
	bool mIsStart;

	private:
};

