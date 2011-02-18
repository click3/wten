
namespace wten {

namespace actions {

class SpellBase : public Action {
public:
	enum SPELL_JOB {
		SPELL_JOB_MAGE,
		SPELL_JOB_PRIEST,
	};
	SpellBase(unsigned int id, TARGET_TYPE target_type, ACTION_TYPE action_type, SPELL_JOB use_job, unsigned int lv, boost::shared_ptr<const std::string> description);
	~SpellBase();
	SPELL_JOB GetUseJob() const;
	unsigned int GetLv() const;
	boost::shared_ptr<const std::string> GetDescription() const;

	boost::optional<boost::shared_ptr<Error> > EnemyAction(boost::shared_ptr<EnemyData> enemy, boost::shared_ptr<PTData> pt, unsigned int target_index) const;
	boost::optional<boost::shared_ptr<Error> > CharAction(boost::shared_ptr<CharData> character, boost::shared_ptr<EnemyPTData> pt, unsigned int target_index) const;
	virtual boost::optional<boost::shared_ptr<Error> > EnemySpell(boost::shared_ptr<EnemyData> enemy, boost::shared_ptr<PTData> pt, unsigned int target_index) const = 0;
	virtual boost::optional<boost::shared_ptr<Error> > CharSpell(boost::shared_ptr<CharData> character, boost::shared_ptr<EnemyPTData> pt, unsigned int target_index) const = 0;

protected:
	const SPELL_JOB use_job;
	const unsigned int lv;
	const boost::shared_ptr<const std::string> description;
};

} // actions

} // wten
