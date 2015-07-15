#pragma once
#include "cocos2d.h"
#include "Cloud.h"
USING_NS_CC;


class FloorLayer : public cocos2d::Layer
{
public:

	FloorLayer(void);

	~FloorLayer(void);

	CREATE_FUNC(FloorLayer);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	void scrollCloud(float);

	void start();
	void reset();
	void pause();
	Vector<Cloud*> getClouds();
	  
private:
	Node *mObjectNode1;
	Node *mObjectNode2;
	Vector<Cloud*> mClouds;
};
