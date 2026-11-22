#include "FileLoader.h"
#include "../Castle-Defense/Fighter.h"
#include "../Castle-Defense/Healer.h"
#include "../Castle-Defense/Defs.h"
#include <iostream>
#include <fstream>
using namespace std;

bool FileLoader::Load(const char* fileName, Castle& castle, EnemyLists& lists)
{
    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << "Error: Cannot open input file \""
             << fileName << "\"." << endl;
        return false;
    }

    int towerHealth, maxTargets, towerPower;

    if (!(file >> towerHealth >> maxTargets >> towerPower))
    {
        cout << "Error: First line must contain TH N TP." << endl;
        file.close();
        return false;
    }

    if (towerHealth <= 0 || maxTargets < 0 || towerPower < 0)
    {
        cout << "Error: Invalid tower values." << endl;
        file.close();
        return false;
    }

    castle.Init(towerHealth, maxTargets, towerPower);

    int totalEnemies = 0;
    int healerCount = 0;
    int id;
    bool foundEnd = false;

    while (file >> id)
    {
        if (id == -1)
        {
            foundEnd = true;
            break;
        }

        int type, arrivalTime, power, reloadPeriod;
        double health;
        char regionLetter;

        if (!(file >> type >> arrivalTime >> health
                  >> power >> reloadPeriod >> regionLetter))
        {
            cout << "Error: Invalid enemy row." << endl;
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

        if (arrivalTime < 0 || health <= 0 ||
            power < 0 || reloadPeriod < 0)
        {
            cout << "Error: Invalid enemy values." << endl;
            file.close();
            return false;
        }

        Enemy* created = NULL;

        if (type == FIGHTER)
            created = new Fighter(id, region, arrivalTime,
                                  health, power, reloadPeriod);
        else if (type == HEALER)
        {
            created = new Healer(id, region, arrivalTime,
                                 health, power, reloadPeriod);
            healerCount++;
        }
        else
        {
            cout << "Error: Phase 1 accepts only types 1 and 2." << endl;
            file.close();
            return false;
        }

        lists.AddInactive(created);
        totalEnemies++;
    }

    file.close();

    if (!foundEnd)
    {
        cout << "Error: Input file must end with -1." << endl;
        return false;
    }

    if (totalEnemies == 0)
    {
        cout << "Error: No enemies found." << endl;
        return false;
    }

    if (healerCount * 100 > totalEnemies * HEALER_PERCENT_MAX)
    {
        cout << "Error: Healers exceed the allowed percentage." << endl;
        return false;
    }

    return true;
}
