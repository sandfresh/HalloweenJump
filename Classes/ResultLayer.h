#pragma once
#include "cocos2d.h"
 
USING_NS_CC;


class ResultLayer : public cocos2d::Layer
{
public:

	ResultLayer(void);

	~ResultLayer(void);

	CREATE_FUNC(ResultLayer);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void start();
	void reset();
	void show();
	void hide();
	void callback(); 
	void showResult();
	 
private:
	ParticleSystemQuad* mEmitter;
	CCMenu* mMenu;
	Vector<Label*> mScoreText;
	 
};