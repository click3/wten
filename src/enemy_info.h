
namespace wten {

class ItemInfo;

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class EnemyInfo : boost::noncopyable {
public:
	enum MONSTER_TYPE {
		MONSTER_TYPE_FIGHTER,
		MONSTER_TYPE_SAMURAI,
		MONSTER_TYPE_PRIEST,
		MONSTER_TYPE_MAGE,
		MONSTER_TYPE_MERCHANT,
		MONSTER_TYPE_THIEF,
		MONSTER_TYPE_GIANT,
		MONSTER_TYPE_MYTH,
		MONSTER_TYPE_DRAGON,
		MONSTER_TYPE_ANIMAL,
		MONSTER_TYPE_HUMAN_BEAST,
		MONSTER_TYPE_UNDEAD,
		MONSTER_TYPE_SATAN,
		MONSTER_TYPE_INSECT,
		MONSTER_TYPE_MAGIC_ANIMAL,
	};
	EnemyInfo(boost::shared_ptr<const std::wstring> uncertainty_name, boost::shared_ptr<const std::wstring> name,
		MONSTER_TYPE type, unsigned int lv, unsigned int hp_base, unsigned int hp_bonus, int ac,
		unsigned int atk_base, unsigned int atk_count, unsigned int atk_bonus,
		unsigned int resist, const std::vector<Action::ACTION_TYPE>& resist_actions,
		unsigned int exp, unsigned int tg_base, unsigned int drop_base,
		boost::shared_ptr<const ItemInfo> drop_item);
	~EnemyInfo();
	boost::shared_ptr<const std::wstring> GetUncertaintyName() const;
	boost::shared_ptr<const std::wstring> GetName() const;
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
	const boost::shared_ptr<const std::wstring> uncertainty_name;
	const boost::shared_ptr<const std::wstring> name;
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
#pragma warning(pop)

} // wten
