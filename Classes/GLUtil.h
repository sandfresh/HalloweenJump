#pragma once


#include <iostream> 

using namespace std;


class GLUtil
{
public:
	static int random(int min ,int max);

private :
	static void setRandom();

	static bool mIsSetRadomSeed;
};
