#include "FileLoader.h"
#include <iostream>
#include <fstream>
#include "Fighter.h"
#include "Healer.h"
#include "Defs.h"
using namespace std;

bool FileLoader::Load(const char* fileName, Castle& castle, EnemyLists& lists)
{
    fstream file;
    file.open(fileName, ios::in);

    if (!file.is_open())
    {
        cout << "Error: Cannot open input file." << endl;
        return false;
    }

    int towerHealth, maxTargets, towerPower;
    if (!(file >> towerHealth >> maxTargets >> towerPower))
    {
        cout << "Error: Invalid file header." << endl;
        file.close();
        return false;
    }

    castle.Init(towerHealth, maxTargets, towerPower);

    int id, type, arrivalTime, power, reloadPeriod;
    double health;
    char regionLetter;
    int totalEnemies = 0, healerCount = 0;
    bool foundEnd = false;

    while (file >> id)
    {
        if (id == -1)
        {
            foundEnd = true;
            break;
        }

        if (!(file >> type >> arrivalTime >> health >> power >> reloadPeriod >> regionLetter))
        {
            cout << "Error: Invalid enemy information." << endl;
            file.close();
            return false;
        }

        RegionType region;
        if (regionLetter == 'A' || regionLetter == 'a')
            region = REGION_A;
        else if (regionLetter == 'B' || regionLetter == 'b')
            region = REGION_B;
        else if (regionLetter == 'C' || regionLetter == 'c')
            region = REGION_C;
        else if (regionLetter == 'D' || regionLetter == 'd')
            region = REGION_D;
        else
        {
            cout << "Error: Region must be A, B, C or D." << endl;
            file.close();
            return false;
        }

        if (arrivalTime < 0 || health <= 0 || power < 0 || reloadPeriod < 0)
        {
            cout << "Error: Invalid enemy values." << endl;
            file.close();
            return false;
        }

        Enemy* newEnemy = NULL;

        if (type == FIGHTER)
            newEnemy = new Fighter(id, region, arrivalTime, health, power, reloadPeriod);
        else if (type == HEALER)
        {
            newEnemy = new Healer(id, region, arrivalTime, health, power, reloadPeriod);
            healerCount++;
        }
        else
        {
            cout << "Error: Phase 1 accepts only Fighter and Healer enemies." << endl;
            file.close();
            return false;
        }

        lists.AddInactive(newEnemy);
        totalEnemies++;
    }

    file.close();

    if (!foundEnd)
    {
        cout << "Error: The file must end with -1." << endl;
        return false;
    }

    if (totalEnemies == 0)
    {
        cout << "Error: The file contains no enemies." << endl;
        return false;
    }

    if (healerCount * 100 > totalEnemies * HEALER_PERCENT_MAX)
    {
        cout << "Error: Healers cannot exceed 20 percent of all enemies." << endl;
        return false;
    }

    return true;
}
