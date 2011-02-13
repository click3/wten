
namespace wten {

namespace uis {

class UIStringBox : public UIBox {
public:
	UIStringBox(const std::string& filename, const std::string& text);
	~UIStringBox();
	boost::optional<boost::shared_ptr<Error> > SetText(const std::string& text);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	utility::opt_error<unsigned int>::type CalcWidth();
	utility::opt_error<unsigned int>::type CalcHeight();
protected:
	std::string text;
};

} // uis

} // wten
