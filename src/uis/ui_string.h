
namespace wten {

namespace uis {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UIString : public UIBase {
public:
	UIString(boost::shared_ptr<const std::string> text);
	UIString(boost::shared_ptr<const std::wstring> text);
	UIString(const std::string &text);
	UIString(const std::wstring &text);
	UIString(const char *text);
	UIString(const wchar_t *text);
	~UIString();
	boost::optional<boost::shared_ptr<Error> > SetText(boost::shared_ptr<const std::string> text);
	boost::optional<boost::shared_ptr<Error> > SetText(boost::shared_ptr<const std::wstring> text);
	boost::optional<boost::shared_ptr<Error> > SetText(const std::string &text);
	boost::optional<boost::shared_ptr<Error> > SetText(const std::wstring &text);
	boost::optional<boost::shared_ptr<Error> > SetText(const char *text);
	boost::optional<boost::shared_ptr<Error> > SetText(const wchar_t *text);
	boost::shared_ptr<const std::wstring> GetText() const;
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth() const;
	utility::opt_error<unsigned int>::type CalcHeight() const;
protected:
	std::vector<boost::shared_ptr<const std::wstring> > text_list;
};
#pragma warning(pop)

} // uis

} // wten
