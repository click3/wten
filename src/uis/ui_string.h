
namespace wten {

namespace uis {

class UIString : public UIBase {
public:
	UIString(const std::string& text);
	~UIString();
	boost::optional<boost::shared_ptr<Error> > SetText(const std::string& text);
	utility::opt_error<std::string>::type GetText();
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth();
	utility::opt_error<unsigned int>::type CalcHeight();
protected:
	std::string text;
};

} // uis

} // wten
