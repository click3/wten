#include "stdafx.h"

namespace wten {

using namespace utility;

ItemInfo::ItemInfo(boost::shared_ptr<const std::string> uncertainty_name, boost::shared_ptr<const std::string> name,
	boost::shared_ptr<const std::string> description, unsigned int sale_price, unsigned int price,
	ITEM_TYPE item_type, unsigned int atk_base, unsigned int atk_count, unsigned int atk_bonus,
	unsigned int hit, unsigned int hit_count, int ac, unsigned int broken_probability)
:
	uncertainty_name(uncertainty_name), name(name),description(description), sale_price(sale_price), price(price),
	item_type(item_type), atk_base(atk_base), atk_count(atk_count), atk_bonus(atk_bonus),
	hit(hit), hit_count(hit_count), ac(ac), broken_probability(broken_probability)
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

} // wten
