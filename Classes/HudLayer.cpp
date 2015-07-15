#include "HudLayer.h"
#include "Tex.h"

HudLayer::HudLayer()
{
}
HudLayer::~HudLayer()
{
}

bool HudLayer::init()
{

	if (!Layer::init())
	{
		return false;
	}
  
	auto scoreframe = CCSprite::createWithSpriteFrameName(Tex::scroeframe);
	this->addChild(scoreframe);
	scoreframe->setAnchorPoint(ccp(0, 0));
	scoreframe->setPosition(800 - 10-scoreframe->getContentSize().width, 470 - scoreframe->getContentSize().height);

	mScoreText = Label::createWithSystemFont("0", "Arial", 40); 
	scoreframe->addChild(mScoreText); 
   mScoreText->setAnchorPoint(ccp(1, 0));
   mScoreText->setPosition(180,10);  

	return true;
}


void HudLayer::onEnter()
{
	Layer::onEnter();
}

void HudLayer::onExit()
{
	Layer::onExit();
} 
 
void HudLayer::setScore(int score)
{  
   string s = StringUtils::toString(score);
   mScoreText->setString(s);
}

 
 