#include "stdafx.h"

namespace wten {

CharCondition::CharCondition() :
	condition(CONDITION_OK), poison(false), silence(false), battle_ac_bonus(0), ac_bonus(0), parry(false)
{
}

CharCondition::~CharCondition() {
}

boost::shared_ptr<std::wstring> CharCondition::ToString(void) const {
	wchar_t *result;
	switch(condition) {
#define ADD_CONDITION(name) case CONDITION_##name: result = L#name; break
		ADD_CONDITION(OK);
		ADD_CONDITION(POISON);
		ADD_CONDITION(SILENCE);
		ADD_CONDITION(SLEEP);
		ADD_CONDITION(FEAR);
		ADD_CONDITION(PARALYZED);
		ADD_CONDITION(STONED);
		ADD_CONDITION(DEAD);
		ADD_CONDITION(ASHED);
		ADD_CONDITION(LOST);
		default:
			BOOST_ASSERT(false);
			result = L"Unknown";
			break;
	}
	return boost::shared_ptr<std::wstring>(new std::wstring(result));
}

CharCondition::CONDITION CharCondition::GetCondition() const {
	return condition;
}

bool CharCondition::IsOk() const {
	return (condition == CONDITION_OK);
}

bool CharCondition::IsSleep() const {
	return (condition == CONDITION_SLEEP);
}

bool CharCondition::IsFear() const {
	return (condition == CONDITION_FEAR);
}

bool CharCondition::IsParalyzed() const {
	return (condition == CONDITION_PARALYZED);
}

bool CharCondition::IsStoned() const {
	return (condition == CONDITION_STONED);
}

bool CharCondition::IsDead() const {
	return (condition == CONDITION_DEAD);
}

bool CharCondition::IsAshed() const {
	return (condition == CONDITION_ASHED);
}

bool CharCondition::IsLost() const {
	return (condition == CONDITION_LOST);
}

bool CharCondition::SetSleep() {
	if(GetCondition() >= CONDITION_SLEEP) {
		return false;
	}
	condition = CONDITION_SLEEP;
	return true;
}

bool CharCondition::SetFear() {
	if(GetCondition() >= CONDITION_SLEEP) {
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
	condition = (IsSilence() ? CONDITION_SILENCE : (IsPoison() ? CONDITION_POISON : CONDITION_OK));
	return true;
}

bool CharCondition::RecoveryFear() {
	if(!IsFear()) {
		return false;
	}
	condition = (IsSilence() ? CONDITION_SILENCE : (IsPoison() ? CONDITION_POISON : CONDITION_OK));
	return true;
}

bool CharCondition::RecoveryParalyze() {
	if(!IsParalyzed()) {
		return false;
	}
	condition = (IsSilence() ? CONDITION_SILENCE : (IsPoison() ? CONDITION_POISON : CONDITION_OK));
	return true;
}

bool CharCondition::RecoveryStone() {
	if(!IsStoned()) {
		return false;
	}
	condition = (IsSilence() ? CONDITION_SILENCE : (IsPoison() ? CONDITION_POISON : CONDITION_OK));
	return true;
}

bool CharCondition::RecoveryDead() {
	if(!IsDead()) {
		return false;
	}
	RecoveryPoison();
	RecoverySilence();
	condition = CONDITION_OK;
	return true;
}

bool CharCondition::RecoveryAshed() {
	if(!IsAshed()) {
		return false;
	}
	RecoveryPoison();
	RecoverySilence();
	condition = CONDITION_OK;
	return true;
}

bool CharCondition::RecoveryLost() {
	if(!IsLost()) {
		return false;
	}
	RecoveryPoison();
	RecoverySilence();
	condition = CONDITION_OK;
	return true;
}

bool CharCondition::IsPoison() const {
	return poison;
}

bool CharCondition::SetPoison() {
	if(IsPoison()) {
		return false;
	}
	poison = true;
	if(IsOk()) {
		condition = CONDITION_POISON;
	}
	return true;
}

bool CharCondition::RecoveryPoison() {
	if(!IsPoison()) {
		return false;
	}
	poison = false;
	if(GetCondition() == CONDITION_POISON) {
		condition = CONDITION_OK;
	}
	return true;
}

bool CharCondition::IsSilence() const {
	return silence;
}

bool CharCondition::SetSilence() {
	if(IsSilence()) {
		return false;
	}
	if(GetCondition() <= CONDITION_POISON) {
		condition = CONDITION_SILENCE;
	}
	silence = true;
	return true;
}

bool CharCondition::RecoverySilence() {
	if(!IsSilence()) {
		return false;
	}
	silence = false;
	if(GetCondition() == CONDITION_SILENCE) {
		condition = (IsPoison() ? CONDITION_POISON : CONDITION_OK);
	}
	return true;
}

bool CharCondition::IsAction() const {
	return (GetCondition() < CONDITION_FEAR);
}

bool CharCondition::IsAlive() const {
	return (GetCondition() < CONDITION_PARALYZED);
}

int CharCondition::GetACBonus() const {
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

bool CharCondition::IsParry() const {
	return parry;
}

void CharCondition::SetParry() {
	BOOST_ASSERT(!parry);
	parry = true;
}

void CharCondition::TurnEnd() {
	parry = false;
}

void CharCondition::BattleEnd() {
	TurnEnd();
	RecoverySilence();
	RecoverySleep();
	RecoveryFear();
	ResetBattleACBonus();
}

void CharCondition::FloorChange() {
	BattleEnd();
}

void CharCondition::DungeonOut() {
	FloorChange();
	RecoveryPoison();
	ResetACBonus();
}

} // wten
