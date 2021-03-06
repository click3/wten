#include "stdafx.h"

namespace wten { namespace actions {

SpellBase::SpellBase(unsigned int id, TARGET_TYPE target_type, ACTION_TYPE action_type, SPELL_JOB use_job, unsigned int lv,
	boost::shared_ptr<const std::wstring> name, boost::shared_ptr<const std::wstring> identity_name,
	boost::shared_ptr<const std::wstring> description)
:
	Action(id, target_type, action_type), name(name), identity_name(identity_name), use_job(use_job), lv(lv), description(description)
{
	BOOST_ASSERT(lv > 0);
	BOOST_ASSERT(lv < 8);
	BOOST_ASSERT(name);
	BOOST_ASSERT(!name->empty());
	BOOST_ASSERT(identity_name);
	BOOST_ASSERT(!identity_name->empty());
	BOOST_ASSERT(description);
	BOOST_ASSERT(!description->empty());
}

SpellBase::~SpellBase() {
}

SpellBase::SPELL_JOB SpellBase::GetUseJob() const {
	return use_job;
}

unsigned int SpellBase::GetLv() const {
	return lv;
}

boost::shared_ptr<const std::wstring> SpellBase::GetIdentityName() const {
	return identity_name;
}

boost::shared_ptr<const std::wstring> SpellBase::GetName() const {
	return name;
}

boost::shared_ptr<const std::wstring> SpellBase::GetDescription() const {
	return description;
}

boost::optional<boost::shared_ptr<Error> > SpellBase::EnemyAction(boost::shared_ptr<EnemyData> enemy, boost::shared_ptr<PTData> pt, unsigned int target_index) const {
	// TODO MP消費とか
	return EnemySpell(enemy, pt, target_index);
}
boost::optional<boost::shared_ptr<Error> > SpellBase::CharAction(boost::shared_ptr<CharData> character, boost::shared_ptr<EnemyPTData> pt, unsigned int target_index) const {
	// TODO MP消費とか
	return CharSpell(character, pt, target_index);
}

} // actions

} // wten
