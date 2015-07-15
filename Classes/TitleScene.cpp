#include "GameScene.h"
#include "SimpleAudioEngine.h" 
#include "ME.h"
#include "SE.h"
#include "Tex.h"
#include "GameData.h"
#include "TitleScene.h"
#include "TitleLayer.h"

using namespace CocosDenshion;

USING_NS_CC;



TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{
}

bool TitleScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto titleLayer = TitleLayer::create();
	this->addChild(titleLayer);


	return true;

}

void TitleScene::onEnter()
{
	CCScene::onEnter();

}

void TitleScene::onExit()
{
	CCScene::onExit();
}