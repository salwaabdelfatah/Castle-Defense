#include "Healer.h"
Healer::Healer(int _id, RegionType _region, int _arrivaltime, double _health, int _power, int _reloadedperiod)
	: Enemy(_id, HEALER, _region, _arrivaltime, _health, _power, _reloadedperiod)
{
}

Healer::~Healer()
{
}

void Healer::Move(int _time) {
	MoveOneStep(_time);
}

double Healer::Act(int _time)
{
	// Phase 2: heal enemies within 2 meters
	if (!CanAct(_time))
		return 0.0;
	ScheduleNextAction(_time);
	return HealAmount();
}
double Healer::HealAmount() // Healing Amount = Power / Distance 
{
	return (double)Power / Distance;
}
bool Healer::CanHeal(Enemy* _target) {

	if (_target->GetHealth() <= 0 || _target->GetState() == KILLED) //healer cannot heal killed enemies
		return false;
	if (_target->GetRegion() != Region)//can only heal the enemies on its region
		return false;
	//check if the distance between the healer and the enemy is < = 2
	int Distance_Gap = _target->GetDistance() - Distance;
	if (Distance_Gap < 0)// within 2 meters (forward or backward)
		Distance_Gap = -Distance_Gap;

	bool Healing_Approval = Distance_Gap <= 2;

	return Healing_Approval;

}
void Healer::ApplyHeal(Enemy* _target, double _amount)
{
	double New_Health = _target->GetHealth() + _amount;
	// the healing amount + enemy current health should be below or equal the original health
	_target->SetHealth(New_Health > _target->GetOriginalHealth() ? _target->GetOriginalHealth() : New_Health);
}