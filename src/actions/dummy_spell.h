
namespace wten {

namespace actions {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class DummySpell : public SpellBase {
public:
	DummySpell(unsigned int id, TARGET_TYPE target_type, ACTION_TYPE action_type, SPELL_JOB use_job, unsigned int lv, boost::shared_ptr<const std::string> description);
	~DummySpell();
	boost::optional<boost::shared_ptr<Error> > EnemySpell(boost::shared_ptr<EnemyData> enemy, boost::shared_ptr<PTData> pt, unsigned int target_index) const;
	boost::optional<boost::shared_ptr<Error> > CharSpell(boost::shared_ptr<CharData> character, boost::shared_ptr<EnemyPTData> pt, unsigned int target_index) const;
};
#pragma warning(pop)

} // actions

} // wten
