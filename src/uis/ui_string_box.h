
namespace wten {

namespace uis {

class UIStringBox : public UIBox {
public:
	UIStringBox(const std::string& filename, const std::string& text);
	~UIStringBox();
	boost::optional<boost::shared_ptr<Error> > SetText(const std::string& text);
	boost::optional<boost::shared_ptr<Error> > PointAndSizeIsValid(void);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
protected:
	utility::opt_error<unsigned int>::type CalcWidth();
	utility::opt_error<unsigned int>::type CalcHeight();
	std::string text;
};

} // uis

} // wten
