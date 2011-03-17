#include "stdafx.h"

namespace wten {

using namespace utility;

namespace {

typedef boost::tuple<unsigned int, boost::shared_ptr<const actions::SpellBase> > SPELL_PAIR;

#pragma warning(push)
#pragma warning(disable: 4512)
struct SpellFiltered {
public:
	SpellFiltered(unsigned int threshold) : threshold(threshold) { }
	bool operator ()(const SPELL_PAIR& spell) {
		return spell.get<0>() <= threshold;
	}
private:
	const unsigned int threshold;
};
#pragma warning(pop)

struct SpellTransformed {
public:
	SpellTransformed() { }
	typedef boost::shared_ptr<const actions::SpellBase> result_type;
	boost::shared_ptr<const actions::SpellBase> operator ()(const SPELL_PAIR& spell) const {
		return spell.get<1>();
	}
};

} // anonymous

Job::Job(unsigned int id, boost::shared_ptr<const std::wstring> name,
	unsigned int hp_base, unsigned int hp_count_bonus,
	unsigned int str, unsigned int iq, unsigned int pie,
	unsigned int vit, unsigned int agi, unsigned int luk,
	unsigned int thief_skill, unsigned int exp_base,
	const std::vector<SPELL_PAIR>& spells)
:
	id(id), name(name), hp_base(hp_base), hp_count_bonus(hp_count_bonus),
	str(str), iq(iq), pie(pie), vit(vit), agi(agi), luk(luk),
	thief_skill(thief_skill), exp_base(exp_base), spells(spells)
{
	BOOST_ASSERT(id > 0);
	BOOST_ASSERT(name);
	BOOST_ASSERT(!name->empty());
	BOOST_ASSERT(hp_base > 0);
	BOOST_ASSERT(str > 0);
	BOOST_ASSERT(iq > 0);
	BOOST_ASSERT(pie > 0);
	BOOST_ASSERT(vit > 0);
	BOOST_ASSERT(agi > 0);
	BOOST_ASSERT(luk > 0);
	BOOST_ASSERT(exp_base > 0);

	unsigned int prev_lv = 0;
	unsigned int prev_spell_lv = 0;
	BOOST_FOREACH(SPELL_PAIR spell, this->spells) {
		unsigned int lv;
		boost::shared_ptr<const actions::SpellBase> spell_info;
		boost::tie(lv, spell_info) = spell;

		BOOST_ASSERT(prev_lv <= lv);
		prev_lv = lv;

		BOOST_ASSERT(spell_info);
		BOOST_ASSERT(prev_spell_lv <= spell_info->GetLv());
		prev_spell_lv = spell_info->GetLv();
	}
}

Job::~Job() {
}

unsigned int Job::GetId() const {
	return id;
}

boost::shared_ptr<const std::wstring> Job::GetName() const {
	return name;
}

unsigned int Job::CalcMaxHP(unsigned int lv, unsigned int current_hp) const {
	return std::max(current_hp + 1, Dice(hp_base, lv + hp_count_bonus));
}

unsigned int Job::GetStr() const {
	return str;
}

unsigned int Job::GetIQ() const {
	return iq;
}

unsigned int Job::GetPie() const {
	return pie;
}

unsigned int Job::GetVit() const {
	return vit;
}

unsigned int Job::GetAgi() const {
	return agi;
}

unsigned int Job::GetLuk() const {
	return luk;
}

unsigned int Job::CalcThiefSkill(unsigned lv, unsigned int current_agi) const {
	return thief_skill + (lv / 5 + current_agi) / 10;
}

std::vector<boost::shared_ptr<const actions::SpellBase> > Job::GetSpell(unsigned int lv, unsigned int current_iq) const {
	const unsigned int threshold = lv + current_iq / 5;
	std::vector<boost::shared_ptr<const actions::SpellBase> > result;
	boost::copy(
		spells | boost::adaptors::filtered(SpellFiltered(threshold)) |
		boost::adaptors::transformed(SpellTransformed()),
		std::back_inserter(result));
	return result;
}

unsigned int Job::CalcLv(unsigned int exp) const {
	unsigned int lv = 0;
	unsigned int necessary = exp_base;
	unsigned int up = static_cast<unsigned int>(necessary * 0.75);
	while(exp >= necessary) {
		lv++;
		necessary += up;
		if(lv < 30) {
			up = static_cast<unsigned int>(necessary * 0.75);
		}
	}
	return lv;
}

unsigned int Job::CalcExp(unsigned int level) const {
	BOOST_ASSERT(level > 0);
	unsigned int i = 1;
	unsigned int necessary = exp_base;
	unsigned int up = static_cast<unsigned int>(necessary * 0.75);
	while(i < level) {
		i++;
		necessary += up;
		if(i < 30) {
			up = static_cast<unsigned int>(necessary * 0.75);
		}
	}
	return necessary;
}

} // wten
