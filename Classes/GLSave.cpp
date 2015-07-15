#include "GLSave.h"


void GLSave::saveInt(string key,int value)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey(key.c_str(), value);
}

int GLSave::getInt(string key)
{
	int ret = CCUserDefault::sharedUserDefault()->getIntegerForKey(key.c_str(),0);
	return  ret;
}