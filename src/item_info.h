
namespace wten {

class Job;

class ItemInfo {
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
	ItemInfo(boost::shared_ptr<const std::string> uncertainty_name, boost::shared_ptr<const std::string> name,
		boost::shared_ptr<const std::string> description, unsigned int sale_price, unsigned int price,
		ITEM_TYPE item_type, unsigned int atk_base, unsigned int atk_count, unsigned int atk_bonus,
		unsigned int hit, unsigned int hit_count, int ac, unsigned int broken_probability);
	~ItemInfo();

	boost::shared_ptr<const std::string> GetUncertaintyName() const;
	boost::shared_ptr<const std::string> GetName() const;
	boost::shared_ptr<const std::string> GetDescription() const;
	unsigned int GetSalePrice() const;
	unsigned int GetPrice() const;
	ITEM_TYPE GetItemType() const;
	std::vector<unsigned int> CalcAtkDamage(unsigned int hit_count) const;
	unsigned int GetHit() const;
	unsigned int GetHitCount() const;
	int GetAC() const;
	unsigned int GetBrokenProbability() const;
	bool IsEquipPossible(boost::shared_ptr<const Job> job) const;
protected:
	const boost::shared_ptr<const std::string> uncertainty_name;
	const boost::shared_ptr<const std::string> name;
	const boost::shared_ptr<const std::string> description;
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
};


} // wten
