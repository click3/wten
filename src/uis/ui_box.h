
namespace wten {

namespace uis {

class UIBox : public UIBase {
public:
	UIBox(boost::shared_ptr<const Graph> src);
	~UIBox();
	boost::optional<boost::shared_ptr<Error> > SetOwnerWindow(boost::weak_ptr<const windows::WindowBase> window);
	boost::optional<boost::shared_ptr<Error> > Move(void);
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Resize(void);
	boost::optional<boost::shared_ptr<Error> > SetInnerUI(boost::shared_ptr<UIBase> ui);
	boost::shared_ptr<UIBase> GetInnerUI(void) const;
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth() const;
	utility::opt_error<unsigned int>::type CalcHeight() const;
protected:
	const boost::shared_ptr<Graph> left_up;
	const boost::shared_ptr<Graph> left_down;
	const boost::shared_ptr<Graph> right_up;
	const boost::shared_ptr<Graph> right_down;
	const boost::shared_ptr<Graph> left_line;
	const boost::shared_ptr<Graph> right_line;
	const boost::shared_ptr<Graph> top_line;
	const boost::shared_ptr<Graph> bottom_line;
	const boost::shared_ptr<Graph> blank;

	boost::shared_ptr<UIBase> inner_ui;
};

} // uis

} // wten
