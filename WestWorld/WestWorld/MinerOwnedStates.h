#ifndef MINER_OWNED_STATES_H
#define MINER_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   MinerOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Miner class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include "State.h"
//------------------------------------------------------------------------
//
//  In this state the miner will walk to a goldmine and pick up a nugget
//  of gold. If the miner already has a nugget of gold he'll change state
//  to VisitBankAndDepositGold. If he gets thirsty he'll change state
//  to QuenchThirst
//------------------------------------------------------------------------
class EnterMinerAndDigForNugget:public AI::State
{
private:
	EnterMinerAndDigForNugget(){}

	EnterMinerAndDigForNugget(const EnterMinerAndDigForNugget&);
	EnterMinerAndDigForNugget& operator=(const EnterMinerAndDigForNugget&);
public:
	//this is a singleton
	static EnterMinerAndDigForNugget* Instance();

	virtual void Enter(Miner*);

	virtual void Execute(Miner*);

	virtual void Exit(Miner*);
};

//------------------------------------------------------------------------
//
//  Entity will go to a bank and deposit any nuggets he is carrying. If the 
//  miner is subsequently wealthy enough he'll walk home, otherwise he'll
//  keep going to get more gold
//------------------------------------------------------------------------
class VisitBankAndDepositGold :public AI::State
{
private:
	VisitBankAndDepositGold() {};

	//copy ctor and assignment should be private
	VisitBankAndDepositGold(const VisitBankAndDepositGold&);
	VisitBankAndDepositGold& operator=(const VisitBankAndDepositGold&);

public:
	//this is a singleton
	static VisitBankAndDepositGold* Instance();

	virtual void Enter(Miner*);

	virtual void Execute(Miner*);

	virtual void Exit(Miner*);
};

class GoHomeAndSleepTilRested: public AI::State
{
private:
	GoHomeAndSleepTilRested(){}

	//copy ctor and assignment should be private
	GoHomeAndSleepTilRested(const GoHomeAndSleepTilRested&);
	GoHomeAndSleepTilRested& operator=(const GoHomeAndSleepTilRested&);

public:
	//this is a singleton
	static GoHomeAndSleepTilRested* Instance();
	
	virtual void Enter(Miner*);

	virtual void Execute(Miner*);

	virtual void Exit(Miner*);
};

class QuenchThirst:public AI::State
{
private:
	QuenchThirst(){}

	//copy ctor and assignment should be private
	QuenchThirst(const QuenchThirst&);
	QuenchThirst& operator=(const QuenchThirst&);

public:
	//this is a singleton
	static QuenchThirst* Instance();

	virtual void Enter(Miner* miner);

	virtual void Execute(Miner* miner);

	virtual void Exit(Miner* miner);
};

#endif // MINER_OWNED_STATES_H