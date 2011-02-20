#include "stdafx.h"

namespace wten {

using namespace utility;
using namespace boost::assign;


boost::optional<boost::shared_ptr<Error> > CharData::InitializeStatus(void) {
	BOOST_ASSERT(status);
	hp = status->GetHP();
	mage_mp = status->GetMageMP();
	priest_mp = status->GetPriestMP();
	return boost::none;
}

CharData::CharData(boost::shared_ptr<CharStatus> status, boost::shared_ptr<CharCondition> condition) :
	status(status), condition(condition)
{
	BOOST_ASSERT(status);
	BOOST_ASSERT(condition);
	boost::optional<boost::shared_ptr<Error> > error = InitializeStatus();
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

CharData::~CharData() {
}

boost::shared_ptr<const CharStatus> CharData::GetStatus(void) const {
	return status;
}

boost::shared_ptr<const CharCondition> CharData::GetCondition(void) const {
	return condition;
}

boost::shared_ptr<CharStatus> CharData::GetStatus(void) {
	return status;
}

boost::shared_ptr<CharCondition> CharData::GetCondition(void) {
	return condition;
}

unsigned int CharData::GetHP(void) const {
	return hp;
}

unsigned int CharData::GetStr(void) const {
	return str;
}

unsigned int CharData::GetIQ(void) const {
	return iq;
}

unsigned int CharData::GetPie(void) const {
	return pie;
}

unsigned int CharData::GetVit(void) const {
	return vit;
}

unsigned int CharData::GetAgi(void) const {
	return agi;
}

unsigned int CharData::GetLuk(void) const {
	return luk;
}

std::vector<unsigned int> CharData::GetMageMP(void) const {
	return mage_mp;
}

std::vector<unsigned int> CharData::GetPriestMP(void) const {
	return priest_mp;
}

int CharData::GetAC(void) const {
	return ac;
}

unsigned int CharData::GetThiefSkill(void) const {
	return thief_skill;
}

void CharData::DecHp(unsigned int value) {
	hp -= value;
	// TODO ó‘Ô•Ï‰»‚Æ‚©Ž€–Sˆ—‚Æ‚©
}

void CharData::AddStr(unsigned int value) {
	str += value;
}

void CharData::AddIQ(unsigned int value) {
	iq =+ value;
}

void CharData::AddPie(unsigned int value) {
	pie =+ value;
}

void CharData::AddVit(unsigned int value) {
	vit =+ value;
}

void CharData::AddAgi(unsigned int value) {
	agi =+ value;
}

void CharData::AddLuk(unsigned int value) {
	luk =+ value;
}

void CharData::DecMageMP(unsigned int lv) {
	BOOST_ASSERT(lv > 0);
	BOOST_ASSERT(lv < 8);
	BOOST_ASSERT(mage_mp[lv-1] > 0);
	mage_mp[lv-1]--;
}

void CharData::DecPriestMP(unsigned int lv) {
	BOOST_ASSERT(lv > 0);
	BOOST_ASSERT(lv < 8);
	BOOST_ASSERT(priest_mp[lv-1] > 0);
	priest_mp[lv-1]--;
}

void CharData::AddAC(unsigned int value) {
	ac += value;
}

void CharData::AddThiefSkill(unsigned int value) {
	thief_skill += value;
}

boost::optional<boost::shared_ptr<Error> > CharData::ReloadStatus(void) {
	BOOST_ASSERT(status);
	str = status->GetStr();
	iq  = status->GetIQ();
	pie = status->GetPie();
	vit = status->GetVit();
	agi = status->GetAgi();
	luk = status->GetLuk();
	ac = 10;
	thief_skill =0;

	boost::shared_ptr<CharData> this_ptr = shared_from_this();
	BOOST_ASSERT(this_ptr);
	BOOST_FOREACH(boost::shared_ptr<Item> item, status->GetItemList()) {
		BOOST_ASSERT(item);
		if(item->IsEquip()) {
			OPT_ERROR(item->EquipStatus(this_ptr));
		}
		OPT_ERROR(item->PossessionStatus(this_ptr));
	}

	thief_skill += status->GetJob()->CalcThiefSkill(status->GetLv(), agi);
	return boost::none;
}


} // wten
