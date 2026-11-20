#include "EnemyLists.h"

EnemyLists::EnemyLists() : totalCount(0)
{
    for (int i = 0; i < 4; i++)
        killedCount[i] = 0;
}

// The lists only free their own nodes, never the enemies they point to.
// So this destructor deletes every Enemy once. Each enemy sits in exactly
// one list, therefore nothing is deleted twice.
EnemyLists::~EnemyLists()
{
    // Inactive: the queue cannot be traversed, so empty it.
    Enemy* e;
    while (inactive.Dequeue(e))
        delete e;

    // Active: delete the enemies, the list frees its nodes afterwards.
    for (int r = 0; r < 4; r++)
    {
        /*for (Node<Enemy*>* n = active[r].GetHead(); n; n = n->getNext())
            delete n->getData();*/
        Node<Enemy*>* n = active[r].GetHead();

        while (n != nullptr)
        {
            delete n->getData();
            n = n->getNext();
        }
    }

    // Killed
    for (Node<Enemy*>* n = killed.GetHead(); n; n = n->getNext())
        delete n->getData();
}

// Adds a newly loaded enemy. The input file is sorted by arrival time,
// so the queue stays sorted by arrival time.
void EnemyLists::AddInactive(Enemy* e)
{
    if (!e)
        return;

    inactive.Enqueue(e);
    totalCount++;
}

// Moves every enemy whose arrival time has come from the inactive queue
// to the active list of its region. Stops at the first enemy that has not
// arrived yet (everything behind it arrives later).
                                    //5
void EnemyLists::ActivateArrivals(int now)
{
    Enemy* e;
    //                                      4       <=  5   -> T
    while (inactive.Front(e) && e->GetArrivalTime() <= now)
    {
        inactive.Dequeue(e);
        e->SetState(ACTIVE);
        active[e->GetRegion()].insertEnd(e);
    }
}

// Moves a killed enemy from the active list of its region to the killed list.
// The Enemy object is NOT deleted. Returns false if the enemy is not active.
bool EnemyLists::MoveToKilled(Enemy* e)
{
    if (!e)
        return false;

    int r = e->GetRegion();
    Node<Enemy*>* node = active[r].Find(e);
    if (!node)
        return false;

    active[r].removeNode(node);
    e->SetState(KILLED);
    killed.insertEnd(e);
    killedCount[r]++;
    return true;
}

// First node of the active list of a region (use getNext() to walk it).
// When removing while walking, read getNext() BEFORE calling MoveToKilled.
Node<Enemy*>* EnemyLists::GetActiveHead(RegionType region) const
{
    return active[region].GetHead();
}

// The index-th active enemy counting over regions A, B, C, D.
// Returns nullptr if the index is out of range.
Enemy* EnemyLists::GetActiveAt(int index) const
{
    if (index < 0)
        return nullptr;

    for (int r = 0; r < 4; r++)
    {
        int c = active[r].Count();
        if (index < c)
        {
            Enemy* e = nullptr;
            active[r].GetAt(index, e);
            return e;
        }
        index -= c;
    }
    return nullptr;
}

// Copies the pointers of all active enemies (all regions) into arr, for the
// GUI. No enemy is copied or reallocated. Returns how many were written.
int EnemyLists::FillDrawArray(Enemy* arr[], int capacity) const
{
    int k = 0;
    for (int r = 0; r < 4; r++)
    {
        for (Node<Enemy*>* n = active[r].GetHead(); n && k < capacity; n = n->getNext())
            arr[k++] = n->getData();
    }
    return k;
}

int EnemyLists::ActiveCount(RegionType region) const
{
    return active[region].Count();
}

int EnemyLists::TotalActive() const
{
    int sum = 0;
    for (int r = 0; r < 4; r++)
        sum += active[r].Count();
    return sum;
}

int EnemyLists::KilledCount(RegionType region) const
{
    return killedCount[region];
}

int EnemyLists::TotalKilled() const
{
    return killed.Count();
}

int EnemyLists::TotalCount() const
{
    return totalCount;
}

// True when no enemy is waiting to arrive and no enemy is still active.
bool EnemyLists::AllFinished() const
{
    return inactive.IsEmpty() && TotalActive() == 0;
}

// ======================================================================
// Phase 2

// Used when the tower of region "from" is destroyed.
// - Active enemies of "from" are moved to the active list of "to".
// - Enemies that have not arrived yet and were going to "from" get their
//   region changed to "to" (the queue is rotated once, so its order stays).
// Health, distance and all other properties are kept; no enemy is recreated.
// "to" is chosen by the caller (normally NextRegion(from), skipping towers
// that are already destroyed).
void EnemyLists::TransferRegion(RegionType from, RegionType to)
{
    if (from == to)
        return;

    Enemy* e;
    while (active[from].removeFirst(e))
    {
        e->SetRegion(to);
        active[to].insertEnd(e);
    }

    int n = inactive.Count();
    for (int i = 0; i < n; i++)
    {
        inactive.Dequeue(e);
        if (e->GetRegion() == from)
            e->SetRegion(to);
        inactive.Enqueue(e);
    }
}

// Phase2 Enemies still waiting to arrive (alive = active + inactive).
int EnemyLists::InactiveCount() const
{
    return inactive.Count();
}

// Phase2 First node of the killed list, in kill order (for the output file).
Node<Enemy*>* EnemyLists::GetKilledHead() const
{
    return killed.GetHead();
}