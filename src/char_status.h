
namespace wten {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class CharStatus : boost::noncopyable {
public:
	enum ALIGNMENT {
		ALIGNMENT_GOOD,
		ALIGNMENT_NEUTRAL,
		ALIGNMENT_EVIL,
	};
	CharStatus(boost::shared_ptr<const std::wstring> name, boost::shared_ptr<const Job> job, ALIGNMENT alignment, unsigned int lv, unsigned int hp,
		unsigned int str, unsigned int iq, unsigned int pie, unsigned int vit, unsigned int agi, unsigned int luk,
		unsigned int tg, unsigned int exp, const std::vector<boost::shared_ptr<Item> >& item_list,
		const std::vector<boost::tuple<boost::shared_ptr<const Job>, boost::shared_ptr<const actions::SpellBase> > >& spell_list);
	~CharStatus(void);
	boost::shared_ptr<const std::wstring> GetName(void) const;
	boost::shared_ptr<const Job> GetJob(void) const;
	ALIGNMENT GetAlignment(void) const;
	unsigned int GetLv(void) const;
	unsigned int GetHP(void) const;
	unsigned int GetStr(void) const;
	unsigned int GetIQ(void) const;
	unsigned int GetPie(void) const;
	unsigned int GetVit(void) const;
	unsigned int GetAgi(void) const;
	unsigned int GetLuk(void) const;
	std::vector<unsigned int> GetMageMP(void) const;
	std::vector<unsigned int> GetPriestMP(void) const;
	unsigned int GetTG(void) const;
	unsigned int GetExp(void) const;
	std::vector<boost::shared_ptr<Item> > GetItemList(void) const;
	std::vector<boost::shared_ptr<const actions::SpellBase> > GetSpells(void) const;

	boost::optional<boost::shared_ptr<Error> > ChangeName(boost::shared_ptr<const std::wstring> new_name);
	void AddExp(unsigned int value);
	void AddTG(unsigned int value);
	boost::optional<boost::shared_ptr<Error> > AddItem(boost::shared_ptr<Item> item);
	boost::optional<boost::shared_ptr<Error> > DeleteItem(boost::shared_ptr<Item> item);
	boost::optional<boost::shared_ptr<Error> > LevelDrain(unsigned int value);
	utility::opt_error<boost::optional<std::vector<boost::optional<bool> > > >::type CheckLevelUP(unsigned int bed_lv);
protected:
	utility::opt_error<std::vector<boost::optional<bool> > >::type LevelUP(unsigned int bed_lv);

	boost::shared_ptr<const std::wstring> name;
	boost::shared_ptr<const Job> job;
	ALIGNMENT alignment;
	unsigned int lv;
	unsigned int hp;
	unsigned int str;
	unsigned int iq;
	unsigned int pie;
	unsigned int vit;
	unsigned int agi;
	unsigned int luk;

	std::vector<unsigned int> mage_mp;
	std::vector<unsigned int> priest_mp;

	unsigned int tg;
	unsigned int exp;

	std::vector<boost::shared_ptr<Item> > item_list;

	std::vector<boost::tuple<boost::shared_ptr<const Job>, boost::shared_ptr<const actions::SpellBase> > > spell_list;
};
#pragma warning(pop)

} // wten

