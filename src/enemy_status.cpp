#include "stdafx.h"

namespace wten {

EnemyStatus::EnemyStatus(boost::shared_ptr<const EnemyInfo> info) :
	info(info), name(info->GetUncertaintyName()), hp(info->CalcMaxHP())
{
	BOOST_ASSERT(info);
	BOOST_ASSERT(name);
	BOOST_ASSERT(!name->empty());
	BOOST_ASSERT(hp > 0);
}

EnemyStatus::~EnemyStatus() {
}

boost::shared_ptr<const std::string> EnemyStatus::GetName() const {
	BOOST_ASSERT(name);
	BOOST_ASSERT(!name->empty());
	return name;
}

unsigned int EnemyStatus::GetLv() const {
	BOOST_ASSERT(info);
	return info->GetLv();
}
unsigned int EnemyStatus::GetMaxHP() const {
	return hp;
}

int EnemyStatus::GetAC() const {
	BOOST_ASSERT(info);
	return info->GetAC();
}

unsigned int EnemyStatus::GetAtkCount() const {
	BOOST_ASSERT(info);
	return info->GetAtkCount();
}

unsigned int EnemyStatus::CalcAtkDamage(unsigned int hit_count) const {
	BOOST_ASSERT(info);
	return info->CalcAtkDamage(hit_count);
}

bool EnemyStatus::CheckResist() const {
	BOOST_ASSERT(info);
	return info->CheckResist();
}

bool EnemyStatus::IsResistType(Action::ACTION_TYPE type) const {
	BOOST_ASSERT(info);
	return info->IsResistType(type);
}

unsigned int EnemyStatus::GetExp() const {
	BOOST_ASSERT(info);
	return info->GetExp();
}

unsigned int EnemyStatus::CalcTg(unsigned int thief_skill) const {
	BOOST_ASSERT(info);
	return info->CalcTg(thief_skill);
}

boost::optional<boost::shared_ptr<const ItemInfo> > EnemyStatus::CalcDrop(unsigned int thief_skill) const {
	BOOST_ASSERT(info);
	return info->CalcDrop(thief_skill);
}

} // wten
