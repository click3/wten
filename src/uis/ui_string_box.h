
namespace wten {

namespace uis {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UIStringBox : public UIBox {
public:
	UIStringBox(boost::shared_ptr<const std::string> filename, boost::shared_ptr<const std::string> text);
	~UIStringBox();
	boost::shared_ptr<const std::string> GetText() const;
	boost::optional<boost::shared_ptr<Error> > SetText(boost::shared_ptr<const std::string> text);
};
#pragma warning(pop)

} // uis

} // wten
