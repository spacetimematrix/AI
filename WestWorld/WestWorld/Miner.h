#ifndef MINER_H
#define MINER_H
//------------------------------------------------------------------------
//
//  Name:   Miner.h
//
//  Desc:   A class defining a goldminer.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "State.h"


//the amount of gold a miner must have before he feels comfortable
//舒适等级
const int ComfortLevel			= 5;

//the amount of nuggets a miner can carry 
//最多拿多少金块
const int MaxNuggets			= 3;

//above this value a miner is thirsty 
//口渴程度 
const int ThirstLevel			= 5;

//above this value a miner is sleep 
//疲劳阈值
const int TirednessThreshold	= 5;



class Miner :public BaseGameEntity
{
private:
	AI::State* m_pCurrentState;

	location_type m_Location;

	//how many nuggets the miner has in this pockets
	int m_iGoldCarried;

	int m_iMoneyInBank;

	//the higher the value , the thirstier the mine
	int m_iThirst;

	//the higher the value, the more tired the miner
	int m_iFatigue;
public:
	Miner(int id);
	virtual ~Miner() {};

	//this must be implementd
	void Update();

	//this method change the current state to the new state, It first
	//calls the Exit() method of the current state, the assigns the
	//new state to m_pCurrentState and finally calls the Enter()
	//method of the new state
	void ChangeState(AI::State* new_state);

	location_type Location() const
	{
		return m_Location;
	}

	void ChangeLocation(const location_type loc)
	{
		m_Location = loc;
	}

	int GoldCarried()const
	{
		return m_iGoldCarried;
	}

	void SetGoldCarried(const int val)
	{
		m_iGoldCarried = val;
	}

	void AddToGoldCarried(const int val);

	bool PocketsFull()
	{
		return m_iGoldCarried >= MaxNuggets;
	}

	bool Fatigued()const;

	void DecreaseFatigue()
	{
		m_iFatigue -= 1;
	}

	void IncreaseFatigue()
	{
		m_iFatigue += 1;
	}

	int Wealth()const 
	{
		return m_iMoneyInBank;
	}

	void SetWealth(const int val)
	{
		m_iMoneyInBank = val;
	}

	void AddToWealth(const int val);

	bool Thirsty()const;
	void BuyAndDrinkAWhiskey()
	{
		m_iThirst = 0;
		m_iMoneyInBank -= 2;
	}
};
#endif
