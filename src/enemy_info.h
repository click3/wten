
namespace wten {

class ItemInfo;

enum MONSTER_TYPE {
	MONSTER_TYPE_ANIMAL,
	MONSTER_TYPE_UNDEAD,
};

class EnemyInfo : boost::noncopyable {
public:
	EnemyInfo(boost::shared_ptr<const std::string> uncertainty_name, boost::shared_ptr<const std::string> name,
		MONSTER_TYPE type, unsigned int lv, unsigned int hp_base, unsigned int hp_bonus, int ac,
		unsigned int atk_base, unsigned int atk_count, unsigned int atk_bonus,
		unsigned int resist, const std::vector<Action::ACTION_TYPE>& resist_actions,
		unsigned int exp, unsigned int tg_base, unsigned int drop_base,
		boost::shared_ptr<const ItemInfo> drop_item);
	~EnemyInfo();
	boost::shared_ptr<const std::string> GetUncertaintyName() const;
	boost::shared_ptr<const std::string> GetName() const;
	MONSTER_TYPE GetType() const;
	unsigned int GetLv() const;
	unsigned int CalcMaxHP() const;
	int GetAC() const;
	unsigned int GetAtkCount() const;
	unsigned int CalcAtkDamage(unsigned int hit_count) const;
	bool CheckResist() const;
	bool IsResistType(Action::ACTION_TYPE type) const;
	unsigned int GetExp() const;
	unsigned int CalcTg(unsigned int thief_skill) const;
	boost::optional<boost::shared_ptr<const ItemInfo> > CalcDrop(unsigned int thief_skill) const;
protected:
	const boost::shared_ptr<const std::string> uncertainty_name;
	const boost::shared_ptr<const std::string> name;
	const MONSTER_TYPE type;
	const unsigned int lv;
	const unsigned int hp_base;
	const unsigned int hp_bonus;
	const int ac;
	const unsigned int atk_base;
	const unsigned int atk_count;
	const unsigned int atk_bonus;
	const unsigned int resist;
	const std::vector<Action::ACTION_TYPE> resist_actions;
	const unsigned int exp;
	const unsigned int tg_base;
	const unsigned int drop_base;
	const boost::shared_ptr<const ItemInfo> drop_item;
};

} // wten
