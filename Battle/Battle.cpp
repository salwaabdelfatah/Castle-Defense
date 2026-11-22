#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "Battle.h"
#include "../Loader/FileLoader.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

Battle::Battle()
{
	gui = NULL;
	ForDraw = NULL;
	drawCapacity = 0;
	IndexForDraw = 0;
	currentTime = 0;

	pendingKillCount = 0;

	for (int i = 0; i < MAX_KILLS_PER_STEP; i++)
		pendingKills[i] = NULL;
}

Battle::~Battle()
{
	
	delete[] ForDraw;
	ForDraw = NULL;

	delete gui;
	gui = NULL;
}

bool Battle::Init(const char* fileName)
{
	FileLoader loader;
	if (!loader.Load(fileName, castle, lists))
		return false;

	drawCapacity = lists.TotalCount();
	if (drawCapacity > 0)
	{
		ForDraw = new Enemy*[drawCapacity];
		for (int i = 0; i < drawCapacity; i++)
			ForDraw[i] = NULL;
	}

	gui = new GUI;
	srand((unsigned int)time(NULL));

	cout << "Loaded " << lists.TotalCount() << " enemies." << endl;
	return true;
}

void Battle::Run()
{
	if (gui == NULL)
	{
		cout << "Error: Call Init before Run." << endl;
		return;
	}

	while (BattleSimulation())
		;

	cout << "Simulation finished." << endl;
}

void Battle::PickRandomKills()
{
	int activeCount = lists.TotalActive();

	if (activeCount == 0)
		return;

	int tries = 0;

	while (pendingKillCount < MAX_KILLS_PER_STEP &&
		tries < activeCount * 8)
	{
		tries++;

		Enemy* selected = lists.GetActiveAt(rand() % activeCount);

		if (selected == NULL)
			continue;

		bool alreadyPicked = false;

		for (int i = 0; i < pendingKillCount; i++)
		{
			if (pendingKills[i] == selected)
				alreadyPicked = true;
		}

		if (!alreadyPicked)
		{
			selected->SetKillTime(currentTime);
			pendingKills[pendingKillCount] = selected;
			pendingKillCount++;
		}
	}
}
// One Phase 1 step: activate arrivals, draw them, randomly kill at most 4,
// then print the status bar and wait for a click.

bool Battle::BattleSimulation()
{
	// 1. Activate enemies arriving at this time step.
	ChangeToActive(currentTime);

	// 2. Move enemies that were already active.
	// Newly arriving enemies should remain at 60 m.
	MoveActive();

	// 3. Display enemies before killing anyone.
	DrawEnemies();
	printinfo();

	// 4. Wait for the user.
	Point click;
	gui->GetPointClicked(click);

	// 5. Kill up to 4 previously arrived enemies.
	Kill();

	currentTime++;

	return !lists.AllFinished();
}


void Battle::MoveActive()
{
	for (int r = 0; r < 4; r++)
	{
		Node<Enemy*>* n = lists.GetActiveHead((RegionType)r);

		while (n != NULL)
		{
			Enemy* e = n->getData();

			if (e != NULL && e->GetArrivalTime() < currentTime)
				e->Move(currentTime);

			n = n->getNext();
		}
	}
}
void Battle::ChangeToActive(int timeStep)
{
	// Inactive queue is sorted by arrival time.
	// ActivateArrivals moves every enemy with arrival <= timeStep
	// into the active list of its region.
	lists.ActivateArrivals(timeStep);
}

void Battle::Kill()
{
	int activeCount = lists.TotalActive();
	if (activeCount <= 0)
		return;

	int numberToPick = activeCount;
	if (numberToPick > MAX_KILLS_PER_STEP)
		numberToPick = MAX_KILLS_PER_STEP;

	// Collect first. MoveToKilled changes the active lists, so indexes
	// must not be used after a removal.
	Enemy* picked[MAX_KILLS_PER_STEP];
	int pickedCount = 0;
	int tries = 0;

	while (pickedCount < numberToPick && tries < activeCount * 8)
	{
		tries++;
		Enemy* selected = lists.GetActiveAt(rand() % activeCount);
		if (selected == NULL)
			continue;

		bool already = false;
		for (int i = 0; i < pickedCount; i++)
		{
			if (picked[i] == selected)
				already = true;
		}
		if (!already)
			picked[pickedCount++] = selected;
	}

	for (int i = 0; pickedCount < numberToPick && i < activeCount; i++)
	{
		Enemy* selected = lists.GetActiveAt(i);
		if (selected == NULL)
			continue;

		bool already = false;
		for (int j = 0; j < pickedCount; j++)
		{
			if (picked[j] == selected)
				already = true;
		}
		if (!already)
			picked[pickedCount++] = selected;
	}

	for (int i = 0; i < pickedCount; i++)
	{
		picked[i]->SetKillTime(currentTime);
		lists.MoveToKilled(picked[i]);
	}
}

void Battle::fillForDraw()
{
	IndexForDraw = 0;
	if (ForDraw == NULL)
		return;

	for (int i = 0; i < drawCapacity; i++)
		ForDraw[i] = NULL;

	// Active enemies from all four region lists, pointers only.
	IndexForDraw = lists.FillDrawArray(ForDraw, drawCapacity);
}

void Battle::DrawEnemies()
{
	ChangeToActive(currentTime);
	fillForDraw();
	gui->DrawBattle(ForDraw, IndexForDraw);
}

void Battle::printinfo()
{
	char line[512];
	int used = sprintf(line, "Time %d", currentTime);

	for (int i = 0; i < 4; i++)
	{
		RegionType region = (RegionType)i;
		used += sprintf(line + used, "   %c HP=%.0f Act=%d Kil=%d",
			'A' + i,
			castle.GetTower(region).GetHealth(),
			lists.ActiveCount(region),
			lists.KilledCount(region));
	}

	gui->PrintMessage(line);
	cout << line << endl;
}

Castle* Battle::GetCastle()
{
	return &castle;
}

int Battle::getEnemyCount() const
{
	return lists.TotalCount();
}

int Battle::getKilled() const
{
	return lists.TotalKilled();
}

int Battle::getActive() const
{
	return lists.TotalActive();
}
