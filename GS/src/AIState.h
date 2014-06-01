#ifndef AISTATE_H
#define AISTATE_H

#include "Glob.h"
#include "Player.h"
#include "RegisterQueue.h"
#include "ChairEntity.h"
#include <SFML/System/Time.hpp>
#pragma once


class AIState
{
public:
	AIState();
	~AIState();
	void setPlayer(Player* player);
	void setWorld(World* world);

	void update(sf::Time dt);
private:
	Player* mPlayer;
	World* mWorld;
	sf::Time mLastUpdate;

	void initalize();
	struct Snapshot
	{
		int OpenWaitingChairs;
		int OpenWashChairs;
		int OpenCutChairs;
		int OpenColorChairs;
		int RegQueueLength;
		Customer* WaitingLowestPatience;
		Customer* WashLowestPatience;
		Customer* CutLowestPatience;
		Customer* ColorLowestPatience;
		float RegQueueLowestHeart;

	} mGameState;

	enum AIStack
	{
		WaitingRoomServiceLeastHappy,
		WaitingRoomServiceHaircut,
		WaitingRoomServiceWash,
		WaitingRoomServiceColor,
		WaitingRoomServiceFastest,
		WaitingRoomNextCustomer,
		CutServiceCustomer,
		CutTransferCustomer,
		ColorServiceCustomer,
		WashServiceCustomer,
		WashTransferCustomer,
		RegisterServiceQueue,
	};

	enum SalonService
	{
		Waiting,
		Wash,
		Cut,
		Color,
		Register,
	};

	Customer* getLowestHeart(SalonService service);
};

#endif
