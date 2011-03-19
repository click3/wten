#include "stdafx.h"

namespace wten { namespace actions {

DummySpell::DummySpell(unsigned int id, TARGET_TYPE target_type, ACTION_TYPE action_type, SPELL_JOB use_job, unsigned int lv,
	boost::shared_ptr<const std::wstring> name, boost::shared_ptr<const std::wstring> identity_name,
	boost::shared_ptr<const std::wstring> description)
:
	SpellBase(id, target_type, action_type, use_job, lv, name, identity_name, description)
{
}

DummySpell::~DummySpell() {
}

boost::optional<boost::shared_ptr<Error> > DummySpell::EnemySpell(boost::shared_ptr<EnemyData>, boost::shared_ptr<PTData>, unsigned int) const {
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > DummySpell::CharSpell(boost::shared_ptr<CharData>, boost::shared_ptr<EnemyPTData>, unsigned int) const {
	return boost::none;
}

} // actions

} // wten
