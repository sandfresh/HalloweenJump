#include "GLUtil.h"
#include   "time.h"
#include "cocos2d.h"
USING_NS_CC;

bool GLUtil::mIsSetRadomSeed = false;

void GLUtil::setRandom()
{
	mIsSetRadomSeed = true;
	srand((unsigned)time(0));
}

int GLUtil::random(int min,int max)
{
	if (mIsSetRadomSeed == false)
		setRandom();
	int retValue = (rand() % ((max+1) - min)) + min;
	return retValue;
}