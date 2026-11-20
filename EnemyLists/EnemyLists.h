#pragma once
#include "../Castle-Defense/Enemy.h"
#include "../Queue.h"
#include "../doubleLinkedList.h"
#include "../Node.h"
#include "../Defs.h"
class EnemyLists
{
    Queue<Enemy*>            inactive;      // all regions, sorted by arrival time
    doubleLinkedList<Enemy*> active[4];     // one list per region (frozen enemies stay here too)
    doubleLinkedList<Enemy*> killed;        // all regions, in the order they were killed
    int killedCount[4];                     // killed enemies per region (status bar, O(1))
    int totalCount;                         // number of enemies added so far

    // The lists own the enemies, so copying is forbidden (would double-delete).
    EnemyLists(const EnemyLists&);
    EnemyLists& operator=(const EnemyLists&);

public:
    EnemyLists();
    ~EnemyLists();   // deletes every enemy exactly once

    //Phase 1
    void AddInactive(Enemy* e);                         // used by the file loader
    void ActivateArrivals(int now);                     // inactive queue -> active list of its region
    bool MoveToKilled(Enemy* e);                        // active list -> killed list

    Node<Enemy*>* GetActiveHead(RegionType region) const;   // to traverse one region
    Enemy* GetActiveAt(int index) const;             // i-th active enemy over all regions (random pick)
    int           FillDrawArray(Enemy* arr[], int capacity) const;  // for GUI::DrawEnemies, returns the count

    int  ActiveCount(RegionType region) const;
    int  TotalActive() const;
    int  KilledCount(RegionType region) const;
    int  TotalKilled() const;
    int  TotalCount() const;
    bool AllFinished() const;                           // nothing inactive and nothing active

    //Phase 2
    // Moves every active enemy of "from" to "to" and re-targets the inactive
    // enemies that were going to arrive in "from" (used when a tower is destroyed).
    void TransferRegion(RegionType from, RegionType to);
    int  InactiveCount() const;                         // alive enemies = active + inactive
    Node<Enemy*>* GetKilledHead() const;                // to write the output file
};