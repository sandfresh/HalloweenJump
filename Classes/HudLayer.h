#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;


class HudLayer : public cocos2d::Layer
{
public:

	HudLayer(void);

	~HudLayer(void);

	CREATE_FUNC(HudLayer);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit(); 

	void start();
	void reset();  

	void setScore(int); 
private: 
	 
	Label* mScoreText;
};