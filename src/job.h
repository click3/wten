
namespace wten {

namespace actions {
	class SpellBase;
} // actions

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class Job : boost::noncopyable {
public:
	Job(unsigned int id, boost::shared_ptr<const std::string> name,
		unsigned int hp_base, unsigned int hp_count_bonus,
		unsigned int str, unsigned int iq, unsigned int pie,
		unsigned int vit, unsigned int agi, unsigned int luk, unsigned int thief_skill,
		const std::vector<boost::tuple<unsigned int, boost::shared_ptr<const actions::SpellBase> > >& spells,
		const std::vector<unsigned int>& exp_list);
	~Job();
	unsigned int GetId(void) const;
	boost::shared_ptr<const std::string> GetName(void) const;
	unsigned int CalcMaxHP(unsigned int lv, unsigned int current_hp) const;
	unsigned int GetStr(void) const;
	unsigned int GetIQ(void) const;
	unsigned int GetPie(void) const;
	unsigned int GetVit(void) const;
	unsigned int GetAgi(void) const;
	unsigned int GetLuk(void) const;
	unsigned int CalcThiefSkill(unsigned lv, unsigned int current_agi) const;
	std::vector<boost::shared_ptr<const actions::SpellBase> > GetSpell(unsigned int lv, unsigned int current_iq) const;
	unsigned int CalcLv(unsigned int exp) const;
	unsigned int CalcExp(unsigned int level) const;
protected:
	unsigned int id;
	boost::shared_ptr<const std::string> name;
	unsigned int hp_base;
	unsigned int hp_count_bonus;
	unsigned int str;
	unsigned int iq;
	unsigned int pie;
	unsigned int vit;
	unsigned int agi;
	unsigned int luk;

	unsigned int thief_skill;

	std::vector<boost::tuple<unsigned int, boost::shared_ptr<const actions::SpellBase> > > spells;
	std::vector<unsigned int> exp_list;
};
#pragma warning(pop)

} // wten
