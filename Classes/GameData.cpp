#include "GameData.h"
#include "GLSave.h"
#include "Save.h"

GameData*  GameData::mInstance = NULL;

GameData* GameData::getInstance()
{
	if (mInstance == NULL)
	{
		mInstance = new GameData();
	}
	return mInstance;
}

GameData::GameData()
{
	mScore = 0;
	for (int i = 0; i < 3; i++)
	{
		mScores.push_back(GLSave::getInt(Save::Score + StringUtils::toString(i)));
	}
}
GameData::~GameData()
{
}

void GameData::setScore(int value)
{
	mScore = value;
}

int GameData::getScore()
{
	return mScore;
}

vector<int> GameData::getScores()
{
	return mScores;
}

bool GameData::rankHighest()
{
	
	std::sort(mScores.begin(), mScores.end(), std::greater<int>());
	int highest = mScores.at(0);
	for (int i = 0; i < mScores.size(); i++)
	{
		if (mScores.at(i) == mScore)
			return false;
	}
	mScores.push_back(mScore);
	std::sort(mScores.begin(), mScores.end(), std::greater<int>());
	mScores.pop_back();

	for (int i = 0; i < mScores.size(); i++)
	{
		GLSave::saveInt(Save::Score + StringUtils::toString(i), mScores.at(i));
	}
	 
	if ( mScore>highest)
		return true;
	else
		return false;
}
