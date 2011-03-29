
namespace wten {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class CharData : boost::noncopyable, public boost::enable_shared_from_this<CharData> {
private:
	boost::optional<boost::shared_ptr<Error> > InitializeStatus(void);
public:
	CharData(boost::shared_ptr<CharStatus> status, boost::shared_ptr<CharCondition> condition, bool dungeon, unsigned int floor = 0, unsigned int x = 0, unsigned int y = 0);
	~CharData();

	boost::shared_ptr<const CharStatus> GetStatus(void) const;
	boost::shared_ptr<const CharCondition> GetCondition(void) const;
	boost::shared_ptr<CharStatus> GetStatus(void);
	boost::shared_ptr<CharCondition> GetCondition(void);
	unsigned int GetHP(void) const;
	unsigned int GetStr(void) const;
	unsigned int GetIQ(void) const;
	unsigned int GetPie(void) const;
	unsigned int GetVit(void) const;
	unsigned int GetAgi(void) const;
	unsigned int GetLuk(void) const;
	std::vector<unsigned int> GetMageMP(void) const;
	std::vector<unsigned int> GetPriestMP(void) const;
	int GetAC(void) const;
	unsigned int GetThiefSkill(void) const;
	void DecHP(unsigned int value);
	void HealHP(unsigned int value);
	void AddStr(unsigned int value);
	void AddIQ(unsigned int value);
	void AddPie(unsigned int value);
	void AddVit(unsigned int value);
	void AddAgi(unsigned int value);
	void AddLuk(unsigned int value);
	void DecMageMP(unsigned int lv);
	void DecPriestMP(unsigned int lv);
	void AddAC(unsigned int value);
	void AddThiefSkill(unsigned int value);
	boost::optional<boost::shared_ptr<Error> > ReloadStatus(void);

	bool IsDungeon(void);
	boost::optional<boost::shared_ptr<Error> > DungeonStart(unsigned int floor, unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > DungeonEnd(void);
	boost::tuple<unsigned int, unsigned int, unsigned int> GetPoint(void) const;
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > MoveFloor(unsigned int floor, unsigned int x, unsigned int y);
protected:
	const boost::shared_ptr<CharStatus> status;
	const boost::shared_ptr<CharCondition> condition;

	unsigned int hp;
	unsigned int str;
	unsigned int iq;
	unsigned int pie;
	unsigned int vit;
	unsigned int agi;
	unsigned int luk;

	int ac;
	unsigned int thief_skill;

	std::vector<unsigned int> mage_mp;
	std::vector<unsigned int> priest_mp;

	bool dungeon;
	unsigned char padding[3]; //unused
	unsigned int floor;
	unsigned int x;
	unsigned int y;
};
#pragma warning(pop)
#pragma pack(pop)

} // wten
