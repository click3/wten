#include "stdafx.h"

namespace wten {

using namespace utility;
using namespace boost::assign;

namespace {

#pragma warning(push)
#pragma warning(disable: 4512)
template<class T>
struct FindResist {
	FindResist(const T key) : key(key) { }
	bool operator ()(const boost::tuple<T, unsigned int> data) const {
		return (data.get<0>() == key);
	}
	const T key;
};
#pragma warning(pop)

} // anonymous

ItemInfo::ItemInfo(unsigned int id, boost::shared_ptr<const std::string> uncertainty_name, boost::shared_ptr<const std::string> name,
	boost::shared_ptr<const std::string> description, unsigned int sale_price, unsigned int price,
	ITEM_TYPE item_type, unsigned int atk_base, unsigned int atk_count, unsigned int atk_bonus,
	unsigned int hit, unsigned int hit_count, int ac, unsigned int broken_probability,
	const std::vector<boost::shared_ptr<const Job> >& equip_possible, const std::vector<boost::tuple<Action::ACTION_TYPE, unsigned int> >& element_resist,
	const std::vector<boost::tuple<EnemyInfo::MONSTER_TYPE, unsigned int> >& monster_resist, const std::vector<boost::tuple<CharCondition::CONDITION, unsigned int> >& condition_resist)
:
	id(id), uncertainty_name(uncertainty_name), name(name),description(description), sale_price(sale_price), price(price),
	item_type(item_type), atk_base(atk_base), atk_count(atk_count), atk_bonus(atk_bonus), hit(hit), hit_count(hit_count),
	ac(ac), broken_probability(broken_probability), equip_possible(equip_possible), element_resist(element_resist),
	monster_resist(monster_resist), condition_resist(condition_resist)
{
	BOOST_ASSERT(uncertainty_name);
	BOOST_ASSERT(!uncertainty_name->empty());
	BOOST_ASSERT(name);
	BOOST_ASSERT(!name->empty());
	BOOST_ASSERT(description);
	BOOST_ASSERT(!description->empty());
	BOOST_ASSERT(sale_price > 0);
	BOOST_ASSERT(price > sale_price);
	BOOST_ASSERT(atk_base > 0);
	BOOST_ASSERT(atk_count > 0);
	BOOST_ASSERT(atk_bonus > 0);
	BOOST_ASSERT(broken_probability <= 256);
}

ItemInfo::~ItemInfo() {
}

unsigned int ItemInfo::GetID(void) const {
	return id;
}

boost::shared_ptr<const std::string> ItemInfo::GetUncertaintyName() const {
	return uncertainty_name;
}

boost::shared_ptr<const std::string> ItemInfo::GetName() const {
	return name;
}

boost::shared_ptr<const std::string> ItemInfo::GetDescription() const {
	return description;
}

unsigned int ItemInfo::GetSalePrice() const {
	return sale_price;
}

unsigned int ItemInfo::GetPrice() const {
	return price;
}

ItemInfo::ITEM_TYPE ItemInfo::GetItemType() const {
	return item_type;
}

std::vector<unsigned int> ItemInfo::CalcAtkDamage(unsigned int hit_count) const {
	BOOST_ASSERT(hit_count > 0);
	std::vector<unsigned int> result;
	for(unsigned int i = 0; i < hit_count; i++) {
		result.push_back(Dice(atk_base, atk_count, atk_bonus));
	}
	return result;
}

unsigned int ItemInfo::GetHit() const {
	return hit;
}

unsigned int ItemInfo::GetHitCount() const {
	return hit_count;
}

int ItemInfo::GetAC() const {
	return ac;
}

unsigned int ItemInfo::GetBrokenProbability() const {
	return broken_probability;
}

bool ItemInfo::IsEquipPossible(boost::shared_ptr<const Job> job) const {
	std::vector<boost::shared_ptr<const Job> >::const_iterator it = std::find(equip_possible.begin(), equip_possible.end(), job);
	if(it == equip_possible.end()) {
		return false;
	}
	BOOST_ASSERT(*it == job);
	return true;
}

unsigned int ItemInfo::GetElementResist(Action::ACTION_TYPE element) const {
	std::vector<boost::tuple<Action::ACTION_TYPE, unsigned int> >::const_iterator it = std::find_if(element_resist.begin(), element_resist.end(), FindResist<Action::ACTION_TYPE>(element));
	if(it == element_resist.end()) {
		return 100;
	}
	return it->get<1>();
}

unsigned int ItemInfo::GetMonsterResist(EnemyInfo::MONSTER_TYPE monster) const {
	std::vector<boost::tuple<EnemyInfo::MONSTER_TYPE, unsigned int> >::const_iterator it = std::find_if(monster_resist.begin(), monster_resist.end(), FindResist<EnemyInfo::MONSTER_TYPE>(monster));
	if(it == monster_resist.end()) {
		return 100;
	}
	return it->get<1>();
}

unsigned int ItemInfo::GetConditionResist(CharCondition::CONDITION condition) const {
	std::vector<boost::tuple<CharCondition::CONDITION, unsigned int> >::const_iterator it = std::find_if(condition_resist.begin(), condition_resist.end(), FindResist<CharCondition::CONDITION>(condition));
	if(it == condition_resist.end()) {
		return 100;
	}
	return it->get<1>();
}

} // wten
