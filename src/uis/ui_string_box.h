
namespace wten {

namespace uis {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UIStringBox : public UIBox {
public:
	UIStringBox(boost::shared_ptr<const std::wstring> filename, boost::shared_ptr<const std::wstring> text);
	~UIStringBox();
	boost::shared_ptr<const std::wstring> GetText() const;
	boost::optional<boost::shared_ptr<Error> > SetText(boost::shared_ptr<const std::wstring> text);
};
#pragma warning(pop)

} // uis

} // wten
