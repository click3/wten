
namespace wten {

namespace uis {

class UIQueue : public UIBase {
public:
	enum POSITION {
		COL_POSITION_LEFT,
		COL_POSITION_RIGHT,
		ROW_POSITION_TOP,
		ROW_POSITION_BOTTOM,
	};
	UIQueue(const std::vector<boost::tuple<POSITION, boost::shared_ptr<UIBase> > >& ui_list);
	~UIQueue();
	boost::optional<boost::shared_ptr<Error> > SetOwnerWindow(boost::weak_ptr<const windows::WindowBase> window);
	boost::optional<boost::shared_ptr<Error> > Move(void);
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Resize(void);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth() const;
	utility::opt_error<unsigned int>::type CalcHeight() const;
protected:
	boost::optional<boost::shared_ptr<Error> > ReloadInnerUI(void);

	const bool col_split;
	const std::vector<boost::tuple<POSITION, boost::shared_ptr<UIBase> > > ui_list;
};

} // uis

} // wten
