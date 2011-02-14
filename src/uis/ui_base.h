
namespace wten {

namespace uis {

class UIBase : public UI {
public:
	UIBase();
	~UIBase();
	boost::optional<boost::shared_ptr<Error> > SetOwnerWindow(boost::weak_ptr<windows::WindowBase> window);
	boost::optional<boost::shared_ptr<Error> > InnerRectCheck(void);
	virtual boost::optional<boost::shared_ptr<Error> > PointAndSizeIsValid(void);
	utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetPoint(void);
	utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetAbsolutePoint(void);
	utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetSize(void);

	enum MOVE_MODE {
		MOVE_MODE_LEFT_UP,
		MOVE_MODE_LEFT_CENTER,
		MOVE_MODE_LEFT_DOWN,
		MOVE_MODE_LEFT_FREE,
		MOVE_MODE_CENTER_UP,
		MOVE_MODE_CENTER_CENTER,
		MOVE_MODE_CENTER_DOWN,
		MOVE_MODE_CENTER_FREE,
		MOVE_MODE_RIGHT_UP,
		MOVE_MODE_RIGHT_CENTER,
		MOVE_MODE_RIGHT_DOWN,
		MOVE_MODE_RIGHT_FREE,
		MOVE_MODE_FREE_UP,
		MOVE_MODE_FREE_CENTER,
		MOVE_MODE_FREE_DOWN,
		MOVE_MODE_FREE_FREE,
	};
	void SetMoveMode(MOVE_MODE move_mode);
	MOVE_MODE GetMoveMode(void);
	boost::optional<boost::shared_ptr<Error> > Move();
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > AbsoluteMove(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Resize(void);
	virtual utility::opt_error<unsigned int>::type CalcWidth();
	virtual utility::opt_error<unsigned int>::type CalcHeight();
protected:
	boost::weak_ptr<windows::WindowBase> owner;
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
	MOVE_MODE move_mode;
};

} // uis

} // wten
