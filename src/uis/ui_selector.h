
namespace wten {

namespace uis {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UISelector : public UISelectorBase {
public:
	UISelector(const std::vector<boost::shared_ptr<const std::wstring> >& texts);
	UISelector(const std::vector<boost::shared_ptr<const std::wstring> >& texts, unsigned int line_count);
	UISelector(const std::vector<boost::shared_ptr<const std::wstring> >& texts, unsigned int line_count, boost::shared_ptr<const std::wstring> arrow_filename);
	~UISelector();
	boost::optional<boost::shared_ptr<Error> > Select(boost::shared_ptr<const std::wstring> text);
	boost::optional<boost::shared_ptr<Error> > Select(unsigned int index);
	boost::optional<boost::shared_ptr<Error> > Select(MOVE_FOCUS move_mode);
	utility::opt_error<boost::shared_ptr<const std::wstring> >::type GetText() const;
};
#pragma warning(pop)

} // uis

} // wten
