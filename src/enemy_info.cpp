#include "stdafx.h"

namespace wten {

using namespace utility;

EnemyInfo::EnemyInfo(const boost::shared_ptr<std::string> uncertainty_name, const boost::shared_ptr<std::string> name,
	MONSTER_TYPE type, unsigned int lv, unsigned int hp_base, unsigned int hp_bonus, int ac,
	unsigned int atk_base, unsigned int atk_count, unsigned int atk_bonus,
	unsigned int resist, const std::vector<Action::ACTION_TYPE>& resist_actions,
	unsigned int exp, unsigned int tg_base, unsigned int drop_base,
	const boost::shared_ptr<ItemInfo> drop_item) 
:
	uncertainty_name(uncertainty_name), name(name), type(type), lv(lv), hp_base(hp_base), hp_bonus(hp_bonus), ac(ac),
	atk_base(atk_base), atk_count(atk_count), atk_bonus(atk_bonus), resist(resist), resist_actions(resist_actions),
	exp(exp), tg_base(tg_base), drop_base(drop_base), drop_item(drop_item)
{
	BOOST_ASSERT(uncertainty_name);
	BOOST_ASSERT(!uncertainty_name->empty());
	BOOST_ASSERT(name);
	BOOST_ASSERT(!name->empty());
	BOOST_ASSERT(lv > 0);
	BOOST_ASSERT(hp_base > 0);
	BOOST_ASSERT(atk_base > 0);
	BOOST_ASSERT(atk_count > 0);
	BOOST_ASSERT(resist <= 256);
	BOOST_ASSERT(!drop_item || drop_base > 0);
	BOOST_ASSERT(drop_base <= 256);
}


EnemyInfo::~EnemyInfo() {
}

const boost::shared_ptr<std::string> EnemyInfo::GetUncertaintyName() const {
	return uncertainty_name;
}

const boost::shared_ptr<std::string> EnemyInfo::GetName() const {
	return name;
}

MONSTER_TYPE EnemyInfo::GetType() const {
	return type;
}

unsigned int EnemyInfo::GetLv() const {
	return type;
}

unsigned int EnemyInfo::CalcMaxHP() const {
	return dice(hp_base, lv, hp_bonus);
}

int EnemyInfo::GetAC() const {
	return ac;
}

unsigned int EnemyInfo::GetAtkCount() const {
	return atk_count;
}

unsigned int EnemyInfo::CalcAtkDamage(unsigned int hit_count) const {
	return dice(atk_base, hit_count, atk_bonus);
}

bool EnemyInfo::CheckResist() const {
	return DxLibWrapper::GetRand(255) >= resist;
}

bool EnemyInfo::IsResitType(Action::ACTION_TYPE type) const {
	std::vector<Action::ACTION_TYPE>::const_iterator it = std::find(resist_actions.begin(), resist_actions.end(), type);
	return (it != resist_actions.end());
}

unsigned int EnemyInfo::GetExp() const {
	return exp;
}

unsigned int EnemyInfo::CalcTg(unsigned int thief_skill) const {
	return dice(tg_base, thief_skill);
}

boost::optional<const boost::shared_ptr<ItemInfo> > EnemyInfo::CalcDrop(unsigned int thief_skill) const {
	for(unsigned int i = 0; i < thief_skill; i++) {
		if(DxLibWrapper::GetRand(255) >= drop_base) {
			return drop_item;
		}
	}
	return boost::none;
}

} // wten
