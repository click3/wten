
namespace wten {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class PTData : boost::noncopyable {
public:
	enum DIRECTION {
		DIRECTION_NORTH,
		DIRECTION_SOUTH,
		DIRECTION_EAST,
		DIRECTION_WEST
	};

	PTData(boost::shared_ptr<PTCondition> condition, const std::vector<boost::shared_ptr<CharData> >& characters,
		bool dungeon, unsigned int floor = 0, DIRECTION dir = DIRECTION_NORTH, unsigned int x = 0, unsigned int y = 0);
	~PTData();
	boost::shared_ptr<const PTCondition> GetCondition(void) const;
	std::vector<boost::shared_ptr<const CharData> > GetCharacters(void) const;
	std::vector<boost::shared_ptr<CharData> >::const_iterator Begin(void) const;
	std::vector<boost::shared_ptr<CharData> >::const_iterator begin(void) const;
	std::vector<boost::shared_ptr<CharData> >::const_iterator End(void) const;
	std::vector<boost::shared_ptr<CharData> >::const_iterator end(void) const;
	boost::shared_ptr<const CharData> operator[](unsigned int index) const;
	boost::shared_ptr<const CharData> At(unsigned int index) const;
	boost::shared_ptr<const CharData> at(unsigned int index) const;
	unsigned int Size(void) const;
	unsigned int size(void) const;

	boost::shared_ptr<PTCondition> GetCondition(void);
	std::vector<boost::shared_ptr<CharData> > GetCharacters(void);
	std::vector<boost::shared_ptr<CharData> >::iterator Begin(void);
	std::vector<boost::shared_ptr<CharData> >::iterator begin(void);
	std::vector<boost::shared_ptr<CharData> >::iterator End(void);
	std::vector<boost::shared_ptr<CharData> >::iterator end(void);
	boost::shared_ptr<CharData> operator[](unsigned int index);
	boost::shared_ptr<CharData> At(unsigned int index);
	boost::shared_ptr<CharData> at(unsigned int index);
	void Clear(void);
	void clear(void);
	void PushBack(boost::shared_ptr<CharData> char_data);
	void push_back(boost::shared_ptr<CharData> char_data);

	boost::optional<boost::shared_ptr<Error> > DungeonStart(unsigned int floor, DIRECTION dir, unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > DungeonEnd(void);
	boost::tuple<unsigned int, DIRECTION, unsigned int, unsigned int> GetPoint(void) const;
	boost::optional<boost::shared_ptr<Error> > Move(DIRECTION dir, unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Move(DIRECTION dir);
	boost::optional<boost::shared_ptr<Error> > MoveToFront(void);
	boost::optional<boost::shared_ptr<Error> > MoveToBack(void);
	boost::optional<boost::shared_ptr<Error> > MoveToLeft(void);
	boost::optional<boost::shared_ptr<Error> > MoveToRight(void);
	boost::optional<boost::shared_ptr<Error> > MoveFloor(unsigned int floor, DIRECTION dir, unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Turn(DIRECTION dir);

	utility::opt_error<std::vector<boost::optional<boost::shared_ptr<std::wstring> > > >::type Hotel(unsigned int bed_lv, unsigned int price);
protected:
	boost::optional<boost::shared_ptr<Error> > DecHotelPrice(unsigned int price);
	boost::optional<boost::shared_ptr<Error> > HotelHeal(boost::shared_ptr<CharData> character, unsigned int bed_lv);
	utility::opt_error<boost::optional<boost::shared_ptr<std::wstring> > >::type CheckLevelUP(boost::shared_ptr<CharData> character, unsigned int bed_lv);

	boost::shared_ptr<PTCondition> condition;
	std::vector<boost::shared_ptr<CharData> > characters;

	bool dungeon;
	unsigned char padding[3]; //unused
	unsigned int floor;
	DIRECTION dir;
	unsigned int x;
	unsigned int y;
};
#pragma warning(pop)
#pragma pack(pop)

} // wten
