#ifndef BATTLE_H
#define BATTLE_H

#include "../Castle-Defense/Defs.h"
#include "../Castle/Castle.h"
#include "../EnemyLists/EnemyLists.h"
#include "../Castle-Defense/Enemy.h"
#include "../GUI/GUI.h"

class Battle
{
private:
	Castle castle;
	EnemyLists lists;
	GUI* gui;
	Enemy* pendingKills[MAX_KILLS_PER_STEP];
	int pendingKillCount;




	Enemy** ForDraw;
	int drawCapacity;
	int IndexForDraw;
	int currentTime;

	void ChangeToActive(int timeStep);
	void MoveActive();  
	void ApplyPendingKills();
	void PickRandomKills();
	void Kill();
	void fillForDraw();
	void DrawEnemies();
	void printinfo();

public:
	Battle();
	~Battle();

	bool Init(const char* fileName);
	// One time step. Returns true while enemies are still inactive or active.
	bool BattleSimulation();
	void Run();

	Castle* GetCastle();
	int getEnemyCount() const;
	int getKilled() const;
	int getActive() const;
};

#endif
