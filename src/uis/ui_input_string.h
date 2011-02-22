
namespace wten {

namespace uis {

class UIInputString : public UIBase {
public:
	UIInputString();
	~UIInputString();
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth() const;
	utility::opt_error<unsigned int>::type CalcHeight() const;
	boost::shared_ptr<std::string> GetText(void) const;
protected:
	boost::shared_ptr<std::string> text;
};

} // uis

} // wten
