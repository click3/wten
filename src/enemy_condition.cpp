#include "stdafx.h"

namespace wten {

EnemyCondition::EnemyCondition() :
	condition(CONDITION_OK), poison(false), silence(false), ac_bonus(0), parry(false)
{
}

EnemyCondition::~EnemyCondition() {
}

EnemyCondition::CONDITION EnemyCondition::GetCondition() {
	return condition;
}

bool EnemyCondition::IsOk() {
	if(GetCondition() == CONDITION_OK) {
		return true;
	}
	return false;
}

bool EnemyCondition::IsSleep() {
	if(GetCondition() == CONDITION_SLEEP) {
		return true;
	}
	return false;
}

bool EnemyCondition::IsDead() {
	if(GetCondition() == CONDITION_DEAD) {
		return true;
	}
	return false;
}

bool EnemyCondition::SetSleep() {
	if(!IsOk()) {
		return false;
	}
	condition = CONDITION_SLEEP;
	return true;
}

bool EnemyCondition::SetDead() {
	if(!IsDead()) {
		return false;
	}
	condition = CONDITION_DEAD;
	return true;
}

bool EnemyCondition::RecoverySleep() {
	if(!IsSleep()) {
		return false;
	}
	condition = CONDITION_OK;
	return true;
}

bool EnemyCondition::RecoveryDead() {
	if(!IsDead()) {
		return false;
	}
	condition = CONDITION_OK;
	return true;
}

bool EnemyCondition::IsPoison() {
	return poison;
}

bool EnemyCondition::SetPoison() {
	if(poison) {
		return false;
	}
	poison = true;
	return true;
}

bool EnemyCondition::RecoveryPoison() {
	if(!poison) {
		return false;
	}
	poison = false;
	return true;
}

bool EnemyCondition::IsSilence() {
	return silence;
}

bool EnemyCondition::SetSilence() {
	if(silence) {
		return false;
	}
	silence = true;
	return true;
}

bool EnemyCondition::RecoverySilence() {
	if(!silence) {
		return false;
	}
	silence = false;
	return true;
}

bool EnemyCondition::IsAction() {
	return (GetCondition() < CONDITION_SLEEP);
}

bool EnemyCondition::IsAlive() {
	return (GetCondition() < CONDITION_DEAD);
}

int EnemyCondition::GetACBonus() {
	return ac_bonus;
}

void EnemyCondition::SetACBonus(int bonus) {
	ac_bonus = bonus;
}

void EnemyCondition::AddACBonus(int bonus) {
	ac_bonus += bonus;
}

bool EnemyCondition::ResetACBonus() {
	if(ac_bonus == 0) {
		return false;
	}
	ac_bonus = 0;
	return true;
}

bool EnemyCondition::IsParry() {
	return parry;
}

void EnemyCondition::SetParry() {
	parry = true;
}

void EnemyCondition::TurnEnd() {
	parry = false;
}

} // wten

