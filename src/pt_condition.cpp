#include "stdafx.h"

namespace wten {

PTCondition::PTCondition() :
	light_full(false), light(0), identifies(false), spell_disable(false)
{
}

PTCondition::~PTCondition() {
}

bool PTCondition::IsLight() {
	return light_full || light > 0;
}

bool PTCondition::AddLight(unsigned int value) {
	if(light_full) {
		return false;
	}
	light += value;
	if(light > 100){
		SetLightFull();
	}
	return true;
}

bool PTCondition::SetLightFull() {
	if(light_full) {
		return false;
	}
	light_full = true;
	light = 0;
	return true;
}

bool PTCondition::DecLight(unsigned int value) {
	if(light_full) {
		return false;
	}
	if(value < light) {
		light -= value;
	} else {
		light = 0;
	}
	return true;
}

bool PTCondition::ResetLight() {
	if(light == 0 && !light_full) {
		return false;
	}
	light = 0;
	light_full = false;
	return true;
}

bool PTCondition::IsIdentifies() {
	return identifies;
}

bool PTCondition::SetIdentifies() {
	if(identifies) {
		return false;
	}
	identifies = true;
	return true;
}

bool PTCondition::ResetIdentifies() {
	if(!identifies) {
		return false;
	}
	identifies = false;
	return true;
}

bool PTCondition::IsSpellDisable() {
	return spell_disable;
}

bool PTCondition::DisableSpell() {
	if(spell_disable) {
		return false;
	}
	spell_disable = true;
	return true;
}

bool PTCondition::EnableSpell() {
	if(!spell_disable) {
		return false;
	}
	spell_disable = false;
	return true;
}

void PTCondition::BattleEnd() {
	//none
}

void PTCondition::FloorChange() {
	EnableSpell();
}

void PTCondition::DungeonOut() {
	ResetLight();
	ResetIdentifies();
	EnableSpell();
}



} // wten
