#include "stdafx.h"

namespace wten {

using namespace utility;
using namespace boost::assign;

namespace {

boost::shared_ptr<SpellList> instance;

struct target_types_ : boost::spirit::qi::symbols<char, Action::TARGET_TYPE> {
	target_types_() {
		add
			("THIS",		Action::TARGET_TYPE_THIS)
			("FRIEND_UNIT",	Action::TARGET_TYPE_FRIEND_UNIT)
			("FRIEND_FRONT",	Action::TARGET_TYPE_FRIEND_FRONT)
			("FRIEND_BACK",	Action::TARGET_TYPE_FRIEND_BACK)
			("FRIEND_ALL",	Action::TARGET_TYPE_FRIEND_ALL)
			("FRIEND_NO_SELECT",	Action::TARGET_TYPE_FRIEND_NO_SELECT)
			("ENEMY_UNIT",	Action::TARGET_TYPE_ENEMY_UNIT)
			("ENEMY_AREA",	Action::TARGET_TYPE_ENEMY_AREA)
			("ENEMY_FRONT",	Action::TARGET_TYPE_ENEMY_FRONT)
			("ENEMY_BACK",	Action::TARGET_TYPE_ENEMY_BACK)
			("ENEMY_ALL",		Action::TARGET_TYPE_ENEMY_ALL)
			("ENEMY_NO_SELECT",	Action::TARGET_TYPE_ENEMY_NO_SELECT)
		;
	}
} target_types_impl;

struct action_types_ : boost::spirit::qi::symbols<char, Action::ACTION_TYPE> {
	action_types_() {
		add
			("NORMAL",	Action::ACTION_TYPE_NORMAL)
			("FIRE",	Action::ACTION_TYPE_FIRE)
			("ICE",	Action::ACTION_TYPE_ICE)
			("POISON",	Action::ACTION_TYPE_POISON)
			("DRAIN",	Action::ACTION_TYPE_DRAIN)
			("STONE",	Action::ACTION_TYPE_STONE)
			("SPELL",	Action::ACTION_TYPE_SPELL)
			("SPECIAL",	Action::ACTION_TYPE_SPECIAL)
		;
	}
} action_types_impl;

struct spell_jobs_ : boost::spirit::qi::symbols<char, actions::SpellBase::SPELL_JOB> {
	spell_jobs_() {
		add
			("MAGE",	actions::SpellBase::SPELL_JOB_MAGE)
			("PRIEST",	actions::SpellBase::SPELL_JOB_PRIEST)
		;
	}
} spell_jobs_impl;

boost::shared_ptr<const actions::SpellBase> CreateSpell(
	unsigned int id, Action::TARGET_TYPE target_type, Action::ACTION_TYPE action_type,
	actions::SpellBase::SPELL_JOB use_job, unsigned int lv, boost::shared_ptr<const std::wstring> description)
{
	return boost::shared_ptr<const actions::SpellBase>(new actions::DummySpell(id, target_type, action_type, use_job, lv, description));
}

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
template <typename Iterator>
struct SpellListCSVParser : ListCSVParserBase<Iterator, boost::shared_ptr<const actions::SpellBase> > {
	SpellListCSVParser() {
		namespace qi = boost::spirit::qi;
		using qi::char_;
		using qi::uint_;

		quoted_target_types = '"' >> target_types_impl >> '"';
		target_types = target_types_impl | quoted_target_types;
		quoted_action_types = '"' >> action_types_impl >> '"';
		action_types = action_types_impl | quoted_action_types;
		quoted_spell_jobs = '"' >> spell_jobs_impl >> '"';
		spell_jobs = spell_jobs_impl | quoted_spell_jobs;
		data_line = (uint_ >> ',' >> target_types >> ',' >> action_types >> ',' >> spell_jobs >> ',' >> uint_ >> ',' >> string >> -char_('\n'))
			[qi::_val = boost::phoenix::bind(&CreateSpell, qi::_1, qi::_2, qi::_3, qi::_4, qi::_5, qi::_6)];
		Initialize(data_line);
	}

	boost::spirit::qi::rule<Iterator, Action::TARGET_TYPE()> quoted_target_types;
	boost::spirit::qi::rule<Iterator, Action::TARGET_TYPE()> target_types;
	boost::spirit::qi::rule<Iterator, Action::ACTION_TYPE()> quoted_action_types;
	boost::spirit::qi::rule<Iterator, Action::ACTION_TYPE()> action_types;
	boost::spirit::qi::rule<Iterator, actions::SpellBase::SPELL_JOB()> quoted_spell_jobs;
	boost::spirit::qi::rule<Iterator, actions::SpellBase::SPELL_JOB()> spell_jobs;
	boost::spirit::qi::rule<Iterator, boost::shared_ptr<const actions::SpellBase>()> data_line;
};
#pragma warning(pop)
#pragma pack(pop)

std::vector<boost::shared_ptr<const actions::SpellBase> > ReadSpell(const std::string &path) {
	typedef std::vector<char>::const_iterator Iterator;
	typedef SpellListCSVParser<Iterator> Parser;

	std::vector<char> data;
	boost::optional<boost::shared_ptr<Error> > error = FileRead(path, &data);
	BOOST_ASSERT(!error);
	Iterator first = data.begin();
	const Iterator last = data.end();

	Parser rule;
	std::vector<boost::shared_ptr<const actions::SpellBase> > result;
	const bool parse_result = boost::spirit::qi::parse(first, last, rule, result);
	BOOST_ASSERT(parse_result);
	BOOST_ASSERT(first == last);
	return result;
}

} // anonymous

SpellList::SpellList(const std::vector<boost::shared_ptr<const actions::SpellBase> >& list) :
	list(list)
{
	BOOST_FOREACH(boost::shared_ptr<const actions::SpellBase> spell, this->list) {
		BOOST_ASSERT(spell);
	}
}

SpellList::~SpellList() {
}

//static
boost::shared_ptr<SpellList> SpellList::GetCurrentInstance(void) {
	if(!instance) {
		// TODO ‚¨‚¢‚¾‚µ
		const char *path = "data/action/spell_list.csv";
		std::vector<boost::shared_ptr<const actions::SpellBase> > list = ReadSpell(path);
		instance.reset(new SpellList(list));
		BOOST_ASSERT(instance);
	}
	return instance;
}

std::vector<boost::shared_ptr<const actions::SpellBase> > SpellList::GetList(void) const {
	return list;
}

std::vector<boost::shared_ptr<const actions::SpellBase> >::const_iterator SpellList::Begin(void) const {
	return list.begin();
}

std::vector<boost::shared_ptr<const actions::SpellBase> >::const_iterator SpellList::End(void) const {
	return list.end();
}

} // wten
