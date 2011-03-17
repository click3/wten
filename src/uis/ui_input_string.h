
namespace wten {

namespace uis {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UIInputString : public UIBase {
public:
	UIInputString();
	~UIInputString();
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth() const;
	utility::opt_error<unsigned int>::type CalcHeight() const;
	boost::shared_ptr<std::wstring> GetText(void) const;
protected:
	boost::shared_ptr<std::wstring> text;
};
#pragma warning(pop)

} // uis

} // wten
