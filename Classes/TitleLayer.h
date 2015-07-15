#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;


class TitleLayer : public cocos2d::Layer
{
public:

	TitleLayer(void);

	~TitleLayer(void);

	CREATE_FUNC(TitleLayer);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void start();
	void reset();
	void callBack();
	 
private: 

	Sprite* mTitle;
	Sprite* mWitch;
	MenuItemImage* mStart;
};