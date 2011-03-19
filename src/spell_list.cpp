#include "stdafx.h"

namespace wten {

using namespace utility;
using namespace boost::assign;

namespace {

boost::shared_ptr<SpellList> instance;

struct target_types_ : boost::spirit::qi::symbols<wchar_t, Action::TARGET_TYPE> {
	target_types_() {
		add
			(L"THIS",			Action::TARGET_TYPE_THIS)
			(L"FRIEND_UNIT",		Action::TARGET_TYPE_FRIEND_UNIT)
			(L"FRIEND_FRONT",		Action::TARGET_TYPE_FRIEND_FRONT)
			(L"FRIEND_BACK",		Action::TARGET_TYPE_FRIEND_BACK)
			(L"FRIEND_ALL",		Action::TARGET_TYPE_FRIEND_ALL)
			(L"FRIEND_NO_SELECT",	Action::TARGET_TYPE_FRIEND_NO_SELECT)
			(L"ENEMY_UNIT",		Action::TARGET_TYPE_ENEMY_UNIT)
			(L"ENEMY_AREA",		Action::TARGET_TYPE_ENEMY_AREA)
			(L"ENEMY_FRONT",		Action::TARGET_TYPE_ENEMY_FRONT)
			(L"ENEMY_BACK",		Action::TARGET_TYPE_ENEMY_BACK)
			(L"ENEMY_ALL",		Action::TARGET_TYPE_ENEMY_ALL)
			(L"ENEMY_NO_SELECT",		Action::TARGET_TYPE_ENEMY_NO_SELECT)
		;
	}
} target_types_impl;

struct action_types_ : boost::spirit::qi::symbols<wchar_t, Action::ACTION_TYPE> {
	action_types_() {
		add
			(L"NORMAL",	Action::ACTION_TYPE_NORMAL)
			(L"FIRE",	Action::ACTION_TYPE_FIRE)
			(L"ICE",	Action::ACTION_TYPE_ICE)
			(L"POISON",	Action::ACTION_TYPE_POISON)
			(L"DRAIN",	Action::ACTION_TYPE_DRAIN)
			(L"STONE",	Action::ACTION_TYPE_STONE)
			(L"SPELL",	Action::ACTION_TYPE_SPELL)
			(L"SPECIAL",	Action::ACTION_TYPE_SPECIAL)
		;
	}
} action_types_impl;

struct spell_jobs_ : boost::spirit::qi::symbols<wchar_t, actions::SpellBase::SPELL_JOB> {
	spell_jobs_() {
		add
			(L"MAGE",	actions::SpellBase::SPELL_JOB_MAGE)
			(L"PRIEST",	actions::SpellBase::SPELL_JOB_PRIEST)
		;
	}
} spell_jobs_impl;

boost::shared_ptr<const actions::SpellBase> CreateSpell(
	unsigned int id, Action::TARGET_TYPE target_type, Action::ACTION_TYPE action_type, actions::SpellBase::SPELL_JOB use_job, unsigned int lv,
	const boost::shared_ptr<const std::wstring> &name, const boost::shared_ptr<const std::wstring> &identity_name, boost::shared_ptr<const std::wstring> description)
{
	return boost::shared_ptr<const actions::SpellBase>(new actions::DummySpell(id, target_type, action_type, use_job, lv, name, identity_name, description));
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
		using qi::eol;

		quoted_target_types = '"' >> target_types_impl >> '"';
		target_types = target_types_impl | quoted_target_types;
		quoted_action_types = '"' >> action_types_impl >> '"';
		action_types = action_types_impl | quoted_action_types;
		quoted_spell_jobs = '"' >> spell_jobs_impl >> '"';
		spell_jobs = spell_jobs_impl | quoted_spell_jobs;
		data_line = (
			uint_ >> ',' >> target_types >> ',' >> action_types >> ',' >> spell_jobs >> ',' >> uint_ >> ',' >>
			string >> ',' >> string >> ',' >> string >> -eol)
			[qi::_val = boost::phoenix::bind(&CreateSpell, qi::_1, qi::_2, qi::_3, qi::_4, qi::_5, qi::_6, qi::_7, qi::_8)];
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

std::vector<boost::shared_ptr<const actions::SpellBase> > ReadSpell(const std::wstring &path) {
	typedef std::vector<wchar_t>::const_iterator Iterator;
	typedef SpellListCSVParser<Iterator> Parser;

	std::vector<wchar_t> data;
	boost::optional<boost::shared_ptr<Error> > error = UTF8FileRead(path, &data);
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
		const wchar_t *path = L"data/action/spell_list.csv";
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
