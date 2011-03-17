
namespace wten {

class Job;

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class ItemInfo : boost::noncopyable {
public:
	enum ITEM_TYPE {
		ITEM_TYPE_WEAPON,
		ITEM_TYPE_SHIELD,
		ITEM_TYPE_ARMOR,
		ITEM_TYPE_HELMET,
		ITEM_TYPE_GAUNTLET,
		ITEM_TYPE_ADORNMENT,
		ITEM_TYPE_TOOL
	};
	ItemInfo(unsigned int id, boost::shared_ptr<const std::wstring> uncertainty_name, boost::shared_ptr<const std::wstring> name,
		boost::shared_ptr<const std::wstring> description, unsigned int sale_price, unsigned int price,
		ITEM_TYPE item_type, unsigned int atk_base, unsigned int atk_count, unsigned int atk_bonus,
		unsigned int hit, unsigned int hit_count, int ac, unsigned int broken_probability,
		const std::vector<boost::shared_ptr<const Job> >& equip_possible, const std::vector<boost::tuple<Action::ACTION_TYPE, unsigned int> >& element_resist,
		const std::vector<boost::tuple<EnemyInfo::MONSTER_TYPE, unsigned int> >& monster_resist, const std::vector<boost::tuple<CharCondition::CONDITION, unsigned int> >& condition_resist);
	~ItemInfo();

	unsigned int GetID(void) const;
	boost::shared_ptr<const std::wstring> GetUncertaintyName(void) const;
	boost::shared_ptr<const std::wstring> GetName(void) const;
	boost::shared_ptr<const std::wstring> GetDescription(void) const;
	unsigned int GetSalePrice(void) const;
	unsigned int GetPrice(void) const;
	ITEM_TYPE GetItemType(void) const;
	std::vector<unsigned int> CalcAtkDamage(unsigned int hit_count) const;
	unsigned int GetHit(void) const;
	unsigned int GetHitCount(void) const;
	int GetAC(void) const;
	unsigned int GetBrokenProbability(void) const;
	bool IsEquipPossible(boost::shared_ptr<const Job> job) const;
	unsigned int GetElementResist(Action::ACTION_TYPE element) const;
	unsigned int GetMonsterResist(EnemyInfo::MONSTER_TYPE monster) const;
	unsigned int GetConditionResist(CharCondition::CONDITION condition) const;
protected:
	const unsigned int id;
	const boost::shared_ptr<const std::wstring> uncertainty_name;
	const boost::shared_ptr<const std::wstring> name;
	const boost::shared_ptr<const std::wstring> description;
	const unsigned int sale_price;
	const unsigned int price;
	const ITEM_TYPE item_type;
	const unsigned int atk_base;
	const unsigned int atk_count;
	const unsigned int atk_bonus;
	const unsigned int hit;
	const unsigned int hit_count;
	const int ac;
	const unsigned int broken_probability;
	const std::vector<boost::shared_ptr<const Job> > equip_possible;
	const std::vector<boost::tuple<Action::ACTION_TYPE, unsigned int> > element_resist;
	const std::vector<boost::tuple<EnemyInfo::MONSTER_TYPE, unsigned int> > monster_resist;
	const std::vector<boost::tuple<CharCondition::CONDITION, unsigned int> > condition_resist;
};
#pragma warning(pop)

} // wten
