
#include "ScoreGenerator.h"
#include "md5_wrapper.h"
#include "GlobalConfig.h"

ScoreGenerator::ScoreGenerator(int unserved, int served, int tips, int revenue)
{
	mUnserved = unserved;
	mServed = served;
	mTips = tips;
	mRevenue = revenue;
}

ScoreGenerator::ScoreGenerator(void)
{
	resetScores();
}

void ScoreGenerator::resetScores()
{
	mUnserved = mServed = mTips = mRevenue = 0;

}
void ScoreGenerator::updateVerification()
{
	md5wrapper m;
	std::string s;
	std::string h;

	s = std::to_string(mUnserved);
	s += "," + std::to_string(mServed);
	s += "," + std::to_string(mTips);
	s += "," + std::to_string(mRevenue);
	s += ",";

	h = s;
	for (int i = 0; i < GlobalConfig::get().SCORE_HASH_KEY; i++)
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
	updateVerification();
	s = std::to_string(mUnserved);
	s += "," + std::to_string(mServed);
	s += "," + std::to_string(mTips);
	s += "," + std::to_string(mRevenue);
	s += "," + mVerificationHash;
	s += "\n";

	return s;
}

std::string ScoreGenerator::getFinalScoreString()
{
	std::string s;

	s = "You made a total of $";
	s += std::to_string(mRevenue + mTips);
	s += " by serving ";
	s += std::to_string(mServed);
	s += " customers. ";
	s += std::to_string(mUnserved);
	s += " left unhappy.";

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
