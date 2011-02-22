
namespace wten {

namespace uis {

class UIString : public UIBase {
public:
	UIString(boost::shared_ptr<const std::string> text);
	~UIString();
	boost::optional<boost::shared_ptr<Error> > SetText(boost::shared_ptr<const std::string> text);
	boost::shared_ptr<const std::string> GetText() const;
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth() const;
	utility::opt_error<unsigned int>::type CalcHeight() const;
protected:
	std::vector<boost::shared_ptr<const std::string> > text_list;
};

} // uis

} // wten
