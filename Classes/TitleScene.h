#pragma once

#include "cocos2d.h"
#include "GameLayer.h"
#include "GameBGLayer.h"
#include "FloorLayer.h"
#include "HudLayer.h"

class TitleScene : public cocos2d::Scene
{
public:

	TitleScene(void);

	~TitleScene(void);

	CREATE_FUNC(TitleScene);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit(); 
};