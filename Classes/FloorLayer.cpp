#include "FloorLayer.h"

#include "Tex.h" 
#include "GLUtil.h"


FloorLayer::FloorLayer()
{

}

FloorLayer::~FloorLayer()
{ 
}

bool FloorLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	mObjectNode1 = CCNode::create();
	mObjectNode2 = CCNode::create();
	this->addChild(mObjectNode1);
	this->addChild(mObjectNode2);
	mObjectNode1->setAnchorPoint(ccp(0, 0));
	mObjectNode2->setAnchorPoint(ccp(0, 0));
	mObjectNode1->setPosition(0,0);
	mObjectNode2->setPosition(0,0);

	for (int i = 0; i < 2; i++)
	{
		Cloud* cloud = Cloud::create();
		mObjectNode1->addChild(cloud);
		cloud->setAnchorPoint(ccp(0, 0));
		cloud->setPosition(100 + 400 * i, 50);
		cloud->setCloud(0);
		cloud->setTag(0);
		mClouds.pushBack(cloud);

		cloud = Cloud::create();
		mObjectNode2->addChild(cloud);
		cloud->setAnchorPoint(ccp(0, 0));
		cloud->setPosition(100 + 400 * i, GLUtil::random(0, 140));
		cloud->setCloud(GLUtil::random(0, 2));
		cloud->setTag(1);
		mClouds.pushBack(cloud);
	}

	return true;
}

void FloorLayer::onEnter()
{ 
	CCLayer::onEnter();
	Size size = Director::getInstance()->getVisibleSize();
	Point pos = Point(size.width / 2, size.height / 2);
 
	reset();
	
}

void FloorLayer::onExit()
{
	CCLayer::onExit(); 
}

void FloorLayer::scrollCloud(float time)
{
	mObjectNode1->setPosition(mObjectNode1->getPositionX() - 6, 0);
	mObjectNode2->setPosition(mObjectNode2->getPositionX() - 6, 0);
	if (mObjectNode1->getPositionX() < -800)
	{
		mObjectNode1->setPosition(800, 0);
		for (int i = 0; i < mClouds.size(); i++)
		{
			if (mClouds.at(i)->getTag() == 0)
			{
				mClouds.at(i)->setCloud(GLUtil::random(0, 2));
				mClouds.at(i)->setPosition(mClouds.at(i)->getPositionX(), GLUtil::random(0, 120));
			} 
		}
	}

	if (mObjectNode2->getPositionX() < -800)
	{
		mObjectNode2->setPosition(800, 0);
		for (int i = 0; i < mClouds.size(); i++)
		{
			if (mClouds.at(i)->getTag() == 1)
			{
				mClouds.at(i)->setCloud(GLUtil::random(0, 2));
				mClouds.at(i)->setPosition(mClouds.at(i)->getPositionX(), GLUtil::random(0, 120));
			}
		}
	}
}

Vector<Cloud*> FloorLayer::getClouds()
{
	return mClouds;
}

void FloorLayer::start()
{
	this->schedule(schedule_selector(FloorLayer::scrollCloud), 0.01f);
}

void FloorLayer::reset()
{
	mObjectNode1->setPosition(100, 0);
	mObjectNode2->setPosition(900, 0);

	for (int i = 0; i < mClouds.size(); i++)
	{
		if (mClouds.at(i)->getTag() == 0)
		{
			mClouds.at(i)->setCloud(0); 
		}
	}
}

void FloorLayer::pause()
{
	this->unschedule(schedule_selector(FloorLayer::scrollCloud));
}

 