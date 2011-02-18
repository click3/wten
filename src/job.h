
namespace wten {

namespace actions {
	class SpellBase;
} // actions

class Job : boost::noncopyable {
public:
	Job(unsigned int id, boost::shared_ptr<const std::string> name,
		unsigned int hp_base, unsigned int hp_count_bonus,
		unsigned int str, unsigned int iq, unsigned int pie,
		unsigned int vit, unsigned int agi, unsigned int luk,
		const std::vector<boost::tuple<unsigned int, boost::shared_ptr<const actions::SpellBase> > >& spells,
		const std::vector<unsigned int>& exp_list);
	~Job();
	unsigned int GetId() const;
	boost::shared_ptr<const std::string> GetName() const;
	unsigned int CalcMaxHP(unsigned int lv, unsigned int current_hp) const;
	unsigned int GetStr() const;
	unsigned int GetIQ() const;
	unsigned int GetPie() const;
	unsigned int GetVit() const;
	unsigned int GetAgi() const;
	unsigned int GetLuk() const;
	std::vector<boost::shared_ptr<const actions::SpellBase> > GetSpell(unsigned int lv, unsigned int current_iq) const;
	unsigned int CalcLv(unsigned int exp) const;
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

	std::vector<boost::tuple<unsigned int, boost::shared_ptr<const actions::SpellBase> > > spells;
	std::vector<unsigned int> exp_list;
};

} // wten
