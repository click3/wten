
namespace wten {
	
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class EnemyStatus : boost::noncopyable {
public:
	EnemyStatus(boost::shared_ptr<const EnemyInfo> info);
	~EnemyStatus();
	boost::shared_ptr<const std::string> GetName() const;
	unsigned int GetLv() const;
	unsigned int GetMaxHP() const;
	int GetAC() const;
	unsigned int GetAtkCount() const;
	unsigned int CalcAtkDamage(unsigned int hit_count) const;
	bool CheckResist() const;
	bool IsResistType(Action::ACTION_TYPE type) const;
	unsigned int GetExp() const;
	unsigned int CalcTg(unsigned int thief_skill) const;
	boost::optional<boost::shared_ptr<const ItemInfo> > CalcDrop(unsigned int thief_skill) const;
private:
	const boost::shared_ptr<const EnemyInfo> info;
	boost::shared_ptr<const std::string> name;
	const unsigned int hp;
};
#pragma warning(pop)

} // wten
