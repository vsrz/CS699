#ifndef SCOREGENERATOR_H
#define SCOREGENERATOR_H

#pragma once

#include <string>

class ScoreGenerator
{
public:
	ScoreGenerator(int unserved, int served, int tips, int revenue);
	ScoreGenerator(void);

	// High score validator
	std::string getScoreString();
	
	// Scoring values
	int getTotalCustomers();
	int getUnservedCustomers();
	int getServedCustomers();
	int getTips();
	int getRevenue();

	void addUnserved(int value = 1);
	void addServed(int value = 1);
	void addTips(int value = 0);
	void addRevenue(int value = 0);


private:
	int mUnserved;
	int mServed;
	int mTips;
	int mRevenue;

	void updateVerification();
	std::string mVerificationHash;
};

#endif
