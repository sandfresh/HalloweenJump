#pragma once


#include <iostream> 
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class GameData
{
public: 
	static GameData* getInstance();

	void setScore(int);
	int getScore();
	bool rankHighest();
	vector<int> getScores();
	
private:
	GameData();
	~GameData();
	static  GameData* mInstance;
	int mScore ;
	vector<int> mScores;
	
};