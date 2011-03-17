
namespace wten {

class EnemyPTData;
class CharData;
class PTData;

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class Item : boost::noncopyable {
public:
	enum CONDITION {
		CONDITION_UNCERTAIN,
		CONDITION_UNCERTAIN_CURSE,
		CONDITION_UNCERTAIN_EQUIP,
		CONDITION_UNCERTAIN_EQUIP_CURSE,
		CONDITION_UNCERTAIN_ADHESION_CURSE,
		CONDITION_UNCERTAIN_BROKEN,
		CONDITION_NORMAL,
		CONDITION_CURSE,
		CONDITION_EQUIP,
		CONDITION_EQUIP_CURSE,
		CONDITION_BROKEN,
	};
	Item(boost::shared_ptr<const ItemInfo> info, CONDITION condition = CONDITION_NORMAL);
	~Item();
	bool IsUncertain() const;
	bool IsEquip() const;
	boost::shared_ptr<const std::wstring> GetName() const;
	boost::optional<boost::shared_ptr<const std::wstring> > GetDescription() const;
	unsigned int GetSalePrice() const;
	unsigned int GetPrice() const;
	ItemInfo::ITEM_TYPE GetItemType() const;
	std::vector<unsigned int> CalcAtkDamage(unsigned int hit_count) const;
	unsigned int GetHit() const;
	unsigned int GetHitCount() const;
	int GetAC() const;
	bool IsEquipPossible(boost::shared_ptr<const Job> job) const;
	CONDITION GetCondition() const;
	boost::optional<boost::shared_ptr<Error> > UseBattle(boost::shared_ptr<CharData> charcter, boost::shared_ptr<PTData> pt, boost::shared_ptr<EnemyPTData> enemy_pt);
	boost::optional<boost::shared_ptr<Error> > UseField(boost::shared_ptr<CharData> charcter, boost::shared_ptr<PTData> pt);
	boost::optional<boost::shared_ptr<Error> > EquipStatus(boost::shared_ptr<CharData> charcter) const;
	boost::optional<boost::shared_ptr<Error> > PossessionStatus(boost::shared_ptr<CharData> charcter) const;
	boost::optional<boost::shared_ptr<Error> > OnEquip(boost::shared_ptr<CharData> charcter);
	boost::optional<boost::shared_ptr<Error> > OnDetach();
	boost::optional<boost::shared_ptr<Error> > OnIdentification(boost::shared_ptr<CharData> charcter);
	boost::optional<boost::shared_ptr<Error> > OnDispel(boost::shared_ptr<CharData> charcter);
protected:
	const boost::shared_ptr<const ItemInfo> info;
	CONDITION condition;
};
#pragma warning(pop)

} // wten
