#include "MinerOwnedStates.h"
#include "State.h"
#include "Miner.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

//define this to output to a file
#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//--------------------------------------methods for EnterMineAndDigForNugget
EnterMinerAndDigForNugget* EnterMinerAndDigForNugget::Instance()
{
	static EnterMinerAndDigForNugget instance;

	return &instance;
}

void EnterMinerAndDigForNugget::Enter(Miner* pMiner)
{
	//if the miner is not already located at the goldmine, he must
	//change location to the gold mine
	if (pMiner->Location() != goldmine)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ":" 
			<< "Walin' to the goldmine";

		pMiner->ChangeLocation(goldmine);
	}
}

void EnterMinerAndDigForNugget::Execute(Miner* pMiner)
{
	//the mine digs gor gold until he is carrying in excess of MaxNuggets.
	//If he gets thirsty during his digging he packs up work for a while and
	//change state to go to the saloon for a whiskey.
	pMiner->AddToGoldCarried(1);
	pMiner->IncreaseFatigue();
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ":" << "Pickin' up a nugget";

	//if enough gold mined, go and put it in the bank
	if (pMiner->PocketsFull())
	{
		pMiner->ChangeState(VisitBankAndDepositGold::Instance());
	}

	if (pMiner->Thirsty())
	{
		pMiner->ChangeState(QuenchThirst::Instance());
	}
}

void EnterMinerAndDigForNugget::Exit(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ":"
		<< "an'm leavin' the goldmine with mah pockets fulll o' sweet gold";
}

//----------------------------------------methods for VisitBankAndDepositGold

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
	static VisitBankAndDepositGold instance;
	return &instance;
}

void VisitBankAndDepositGold::Enter(Miner* pMiner)
{
	//on entry the miner makes sure he is located at the bank
	if (pMiner->Location() != bank)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		pMiner->ChangeLocation(bank);
	}
}

void VisitBankAndDepositGold::Execute(Miner* pMiner)
{
	//deposit the gold
	pMiner->AddToWealth(pMiner->GoldCarried());
	pMiner->SetGoldCarried(0);
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ":"
		<< "Depositing gold.Total savings now:" << pMiner->Wealth();

	//wealth enough to have a well earned rest?
	if (pMiner->Wealth() >= ComfortLevel)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
			<< "WooHoo! Rich enough for now. Back home to mah li'lle lady";
		pMiner->ChangeState(GoHomeAndSleepTilRested::Instance());
	}
	//otherwise get more gold
	else
	{
		pMiner->ChangeState(EnterMinerAndDigForNugget::Instance());
	}
}

void VisitBankAndDepositGold::Exit(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Leavin' the bank";
}

//----------------------------------------methods for GoHomeAndSleepTilRested
GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
	static GoHomeAndSleepTilRested instance;

	return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner)
{
	if (pMiner->Location() != shack)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Walkin' home";

		pMiner->ChangeLocation(shack);
	}
}

void GoHomeAndSleepTilRested::Execute(Miner* pMiner)
{
	//if miner is not fatigued start to dig for nuggets again.
	if (!pMiner->Fatigued())
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
			<< "What a God darn fantastic nap! Time to find more gold";

		pMiner->ChangeState(EnterMinerAndDigForNugget::Instance());
	}
	else
	{
		//sleep
		pMiner->DecreaseFatigue();
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "ZZZZ...";
	}
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Leaving the house";
}

//------------------------------------------------methods for QuenchThirst
QuenchThirst* QuenchThirst::Instance()
{
	static QuenchThirst instance;
	return &instance;
}

void QuenchThirst::Enter(Miner* pMiner)
{
	if (pMiner->Location() != saloon)
	{
		pMiner->ChangeLocation(saloon);
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
			<< "Boy, ah sure is thusty! Walking to the saloon";
	}
}

void QuenchThirst::Execute(Miner* pMiner)
{
	if (pMiner->Thirsty())
	{
		pMiner->BuyAndDrinkAWhiskey();
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
			<< "That's mighty fine sippin liquer";
		
		pMiner->ChangeState(EnterMinerAndDigForNugget::Instance());
	}
	else
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\nERROR!\nERROR!\nERROR!";
	}
}

void QuenchThirst::Exit(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
		<< "Leaving the saloon, feelin' good";
}