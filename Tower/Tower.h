#pragma once
#include "../Castle-Defense/Defs.h"
class Tower
{
private:
    int id;
    RegionType region;
    double health;
    double power;
    int maxTargets;
    double iceAccumulated;
    int frozenFrom;
    int frozenUntil;
    double damageTaken;
public:
    static const double FREEZE_THRESHOLD;
    Tower();
    void Init(int _id, RegionType region, double _health, int _maxTargets, double _power);

    int GetID() const;
	double GetHealth() const; //how much health the tower has left
	double GetPower() const;  // returns the tower's firing power
	int GetMaxTargets() const; //how many targets can the tower attack at once
    RegionType GetRegion() const; // which region the tower is in
    double GetDamageTaken() const;     // total damage received (for the output file)
    double GetIceAccumulated() const;

    // ---- State queries ----
    bool IsDestroyed() const;              // health <= 0
    bool IsFrozen(int currentTime) const;          // true if frozen at time step "now"

    // Lowers health (never below 0) and records the damage that was actually taken.
    void TakeDamage(double damage);

    #pragma region Phase 2
    // ----  in Phase 2 
    // Adds ice. Returns true when the threshold is reached (the ice counter is reset).
    bool AddIce(double amount);


    void Freeze(int fromStep, int steps);
    #pragma endregion

    

};
