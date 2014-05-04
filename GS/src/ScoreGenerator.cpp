
#include "ScoreGenerator.h"
#include "md5_wrapper.h"

ScoreGenerator::ScoreGenerator(int unserved, int served, int tips, int revenue)
{
	mUnserved = unserved;
	mServed = served;
	mTips = tips;
	mRevenue = revenue;
}

ScoreGenerator::ScoreGenerator(void)
{
	mUnserved = mServed = mTips = mRevenue = 0;
}

void ScoreGenerator::updateVerification()
{
	md5wrapper m;
	std::string s;
	std::string h;

	s = mUnserved;
	s += "," + mServed;
	s += "," + mTips;
	s += "," + mRevenue;
	s += ",";

	h = s;
	for (int i = 0; i < 537; i++)
	{
		h = m.getHashFromString(h);
	}

	mVerificationHash = h;

}

int ScoreGenerator::getUnservedCustomers()
{
	return mUnserved;
}

int ScoreGenerator::getServedCustomers()
{
	return mServed;
}

int ScoreGenerator::getTips()
{
	return mTips;
}

int ScoreGenerator::getRevenue()
{
	return mRevenue;
}



int ScoreGenerator::getTotalCustomers()
{
	return mServed + mUnserved;

}


std::string ScoreGenerator::getScoreString()
{
	std::string s;

	s = mUnserved;
	s += "," + mServed;
	s += "," + mTips;
	s += "," + mRevenue;
	s += "," + mVerificationHash;

	return s;
}

void ScoreGenerator::addUnserved(int value)
{
	mUnserved += value;
}

void ScoreGenerator::addServed(int value)
{
	mServed += value;
}

void ScoreGenerator::addTips(int value)
{
	mTips += value;
}

void ScoreGenerator::addRevenue(int value)
{
	mRevenue += value;
}
