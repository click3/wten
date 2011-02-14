
namespace wten {

namespace uis {

class UISelector : public UIBase {
public:
	UISelector(std::vector<std::string> texts = std::vector<std::string>(), const std::string& arrow_filename = "data/ui/arrow1.png");
	~UISelector();
	boost::optional<boost::shared_ptr<Error> > AddSelect(const std::string& text);
	boost::optional<boost::shared_ptr<Error> > Select(const std::string& text);
	boost::optional<boost::shared_ptr<Error> > Select(unsigned int index);
	enum MOVE_FOCUS {
		MOVE_FOCUS_UP,
		MOVE_FOCUS_DOWN,
	};
	boost::optional<boost::shared_ptr<Error> > Select(MOVE_FOCUS move_mode);
	utility::opt_error<unsigned int>::type GetIndex();
	utility::opt_error<std::string>::type GetText();
	boost::optional<boost::shared_ptr<Error> > SetOwnerWindow(boost::weak_ptr<windows::WindowBase> window);
	boost::optional<boost::shared_ptr<Error> > Move(void);
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Resize(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth();
	utility::opt_error<unsigned int>::type CalcHeight();
protected:
	std::vector<boost::shared_ptr<UIString> > select_list;
	boost::shared_ptr<UIImage> arrow;
	unsigned int index;
};

} // uis

} // wten
