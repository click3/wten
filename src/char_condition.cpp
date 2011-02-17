#include "stdafx.h"

namespace wten {

CharCondition::CharCondition() :
	condition(CONDITION_OK), poison(false), silence(false), battle_ac_bonus(0), ac_bonus(0)
{
}

CharCondition::~CharCondition() {
}

CharCondition::CONDITION CharCondition::GetCondition() {
	return condition;
}

bool CharCondition::IsOk() {
	return (condition == CONDITION_OK);
}

bool CharCondition::IsSleep() {
	return (condition == CONDITION_SLEEP);
}

bool CharCondition::IsFear() {
	return (condition == CONDITION_FEAR);
}

bool CharCondition::IsParalyzed() {
	return (condition == CONDITION_PARALYZED);
}

bool CharCondition::IsStoned() {
	return (condition == CONDITION_STONED);
}

bool CharCondition::IsDead() {
	return (condition == CONDITION_DEAD);
}

bool CharCondition::IsAshed() {
	return (condition == CONDITION_ASHED);
}

bool CharCondition::IsLost() {
	return (condition == CONDITION_LOST);
}

bool CharCondition::SetSleep() {
	if(!IsOk()) {
		return false;
	}
	condition = CONDITION_SLEEP;
	return true;
}

bool CharCondition::SetFear() {
	if(!IsOk()) {
		return false;
	}
	condition = CONDITION_FEAR;
	return true;
}

bool CharCondition::SetParalyze() {
	if(GetCondition() >= CONDITION_PARALYZED) {
		return false;
	}
	condition = CONDITION_PARALYZED;
	return true;
}

bool CharCondition::SetStone() {
	if(GetCondition() >= CONDITION_STONED) {
		return false;
	}
	condition = CONDITION_STONED;
	return true;
}

bool CharCondition::SetDead() {
	if(GetCondition() >= CONDITION_DEAD) {
		return false;
	}
	condition = CONDITION_DEAD;
	return true;
}

bool CharCondition::SetAshed() {
	if(!IsDead()) {
		return false;
	}
	condition = CONDITION_ASHED;
	return true;
}

bool CharCondition::SetLost() {
	if(!IsAshed()) {
		return false;
	}
	condition = CONDITION_LOST;
	return true;
}

bool CharCondition::RecoverySleep() {
	if(!IsSleep()) {
		return false;
	}
	condition = CONDITION_OK;
	return true;
}

bool CharCondition::RecoveryFear() {
	if(!IsFear()) {
		return false;
	}
	condition = CONDITION_OK;
	return true;
}

bool CharCondition::RecoveryParalyze() {
	if(!IsParalyzed()) {
		return false;
	}
	condition = CONDITION_OK;
	return true;
}

bool CharCondition::RecoveryStone() {
	if(!IsStoned()) {
		return false;
	}
	condition = CONDITION_OK;
	return true;
}

bool CharCondition::RecoveryDead() {
	if(!IsDead()) {
		return false;
	}
	condition = CONDITION_OK;
	return true;
}

bool CharCondition::RecoveryAshed() {
	if(!IsAshed()) {
		return false;
	}
	condition = CONDITION_OK;
	return true;
}

bool CharCondition::RecoveryLost() {
	if(!IsLost()) {
		return false;
	}
	condition = CONDITION_OK;
	return true;
}

bool CharCondition::IsPoison() {
	return poison;
}

bool CharCondition::SetPoison() {
	if(IsPoison()) {
		return false;
	}
	poison = true;
	return true;
}

bool CharCondition::RecoveryPoison() {
	if(!IsPoison()) {
		return false;
	}
	poison = false;
	return true;
}

bool CharCondition::IsSilence() {
	return silence;
}

bool CharCondition::SetSilence() {
	if(IsSilence()) {
		return false;
	}
	silence = true;
	return true;
}

bool CharCondition::RecoverySilence() {
	if(!IsSilence()) {
		return false;
	}
	silence = false;
	return true;
}

bool CharCondition::IsAction() {
	return (GetCondition() < CONDITION_FEAR);
}

bool CharCondition::IsAlive() {
	return (GetCondition() < CONDITION_PARALYZED);
}

int CharCondition::GetACBonus() {
	return battle_ac_bonus + ac_bonus;
}

void CharCondition::SetBattleACBonus(int bonus) {
	battle_ac_bonus = bonus;
}

void CharCondition::AddBattleACBonus(int bonus) {
	battle_ac_bonus += bonus;
}

bool CharCondition::ResetBattleACBonus() {
	if(battle_ac_bonus == 0) {
		return false;
	}
	battle_ac_bonus = 0;
	return true;
}

void CharCondition::SetACBonus(int bonus) {
	ac_bonus = bonus;
}

void CharCondition::AddACBonus(int bonus) {
	ac_bonus += bonus;
}

bool CharCondition::ResetACBonus() {
	if(ac_bonus == 0) {
		return false;
	}
	ac_bonus = 0;
	return true;
}

void CharCondition::BattleEnd() {
	RecoverySilence();
	RecoverySleep();
	RecoveryFear();
	ResetBattleACBonus();
}

void CharCondition::FloorChange() {
	BattleEnd();
}

void CharCondition::DungeonOut() {
	BattleEnd();
	RecoveryPoison();
	ResetACBonus();
}

} // wten
