#include "stdafx.h"

namespace wten {

using namespace utility;

namespace {

typedef boost::tuple<unsigned int, boost::shared_ptr<const actions::SpellBase> > SPELL_PAIR;

struct SpellFiltered {
public:
	SpellFiltered(unsigned int threshold) : threshold(threshold) { }
	bool operator ()(const SPELL_PAIR& spell) {
		return spell.get<0>() <= threshold;
	}
private:
	const unsigned int threshold;
};

struct SpellTransformed {
public:
	SpellTransformed() { }
	typedef boost::shared_ptr<const actions::SpellBase> result_type;
	boost::shared_ptr<const actions::SpellBase> operator ()(const SPELL_PAIR& spell) const {
		return spell.get<1>();
	}
};

} // anonymous

Job::Job(unsigned int id, boost::shared_ptr<const std::string> name,
	unsigned int hp_base, unsigned int hp_count_bonus,
	unsigned int str, unsigned int iq, unsigned int pie,
	unsigned int vit, unsigned int agi, unsigned int luk,
	const std::vector<SPELL_PAIR>& spells,
	const std::vector<unsigned int>& exp_list)
:
	id(id), name(name), hp_base(hp_base), hp_count_bonus(hp_count_bonus),
	str(str), iq(iq), pie(pie), vit(vit), agi(agi), luk(luk),
	spells(spells), exp_list(exp_list)
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

	unsigned int prev_exp = 0;
	BOOST_FOREACH(unsigned int exp, this->exp_list) {
		BOOST_ASSERT(prev_exp <= exp);
		prev_exp = exp;
	}
}

Job::~Job() {
}

unsigned int Job::GetId() const {
	return id;
}

boost::shared_ptr<const std::string> Job::GetName() const {
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
	BOOST_FOREACH(unsigned int total, exp_list) {
		if(total < exp) {
			return lv;
		}
		lv++;
	}
	BOOST_ASSERT(false);
	return lv;
}

unsigned int Job::CalcExp(unsigned int level) const {
	BOOST_ASSERT(level > 0);
	BOOST_ASSERT(exp_list.size() >= level);
	return exp_list[level - 1];
}

} // wten
