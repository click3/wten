
namespace wten {

namespace uis {

class UIBox : public UIBase {
public:
	UIBox(const std::string& filename);
	~UIBox();
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
private:
	boost::shared_ptr<Graph> left_up;
	boost::shared_ptr<Graph> left_down;
	boost::shared_ptr<Graph> right_up;
	boost::shared_ptr<Graph> right_down;
	boost::shared_ptr<Graph> left_line;
	boost::shared_ptr<Graph> right_line;
	boost::shared_ptr<Graph> up_line;
	boost::shared_ptr<Graph> down_line;
	boost::shared_ptr<Graph> blank;
};

} // uis

} // wten
