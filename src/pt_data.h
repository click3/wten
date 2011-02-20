
namespace wten {

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
	boost::shared_ptr<const CharData> operator[](unsigned int index) const;

	boost::shared_ptr<PTCondition> GetCondition(void);
	std::vector<boost::shared_ptr<CharData> > GetCharacters(void);
	boost::shared_ptr<CharData> operator[](unsigned int index);

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
protected:
	boost::shared_ptr<PTCondition> condition;
	std::vector<boost::shared_ptr<CharData> > characters;

	bool dungeon;
	unsigned int floor;
	DIRECTION dir;
	unsigned int x;
	unsigned int y;
};

} // wten
