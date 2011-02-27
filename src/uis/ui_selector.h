
namespace wten {

namespace uis {

class UISelector : public UIBase {
public:
	UISelector(const std::vector<boost::shared_ptr<const std::string> >& texts = std::vector<boost::shared_ptr<const std::string> >(), boost::shared_ptr<const std::string> arrow_filename = boost::shared_ptr<const std::string>(new std::string("data/ui/arrow1.png")));
	~UISelector();
	boost::optional<boost::shared_ptr<Error> > Select(boost::shared_ptr<const std::string> text);
	boost::optional<boost::shared_ptr<Error> > Select(unsigned int index);
	enum MOVE_FOCUS {
		MOVE_FOCUS_UP,
		MOVE_FOCUS_DOWN,
	};
	boost::optional<boost::shared_ptr<Error> > Select(MOVE_FOCUS move_mode);
	utility::opt_error<unsigned int>::type GetIndex() const;
	utility::opt_error<boost::shared_ptr<const std::string> >::type GetText() const;
	boost::optional<boost::shared_ptr<Error> > SetOwnerWindow(boost::weak_ptr<const windows::WindowBase> window);
	boost::optional<boost::shared_ptr<Error> > ClearOwnerWindow(void);
	boost::optional<boost::shared_ptr<Error> > Move(void);
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Resize(void);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth() const;
	utility::opt_error<unsigned int>::type CalcHeight() const;
	unsigned int GetCount() const;
protected:
	const std::vector<boost::shared_ptr<UIString> > select_list;
	const boost::shared_ptr<UIImage> arrow;
	unsigned int index;
};

} // uis

} // wten
