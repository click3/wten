
namespace wten {

namespace uis {

class UIBox : public UIBase {
public:
	UIBox(const boost::shared_ptr<std::string>& filename);
	~UIBox();
	boost::optional<boost::shared_ptr<Error> > SetOwnerWindow(boost::weak_ptr<windows::WindowBase> window);
	boost::optional<boost::shared_ptr<Error> > Move(void);
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Resize(void);
	boost::optional<boost::shared_ptr<Error> > SetInnerUI(boost::shared_ptr<UIBase> ui);
	boost::shared_ptr<UIBase> GetInnerUI(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth();
	utility::opt_error<unsigned int>::type CalcHeight();
protected:
	boost::shared_ptr<Graph> left_up;
	boost::shared_ptr<Graph> left_down;
	boost::shared_ptr<Graph> right_up;
	boost::shared_ptr<Graph> right_down;
	boost::shared_ptr<Graph> left_line;
	boost::shared_ptr<Graph> right_line;
	boost::shared_ptr<Graph> up_line;
	boost::shared_ptr<Graph> down_line;
	boost::shared_ptr<Graph> blank;

	boost::shared_ptr<UIBase> inner_ui;
};

} // uis

} // wten
