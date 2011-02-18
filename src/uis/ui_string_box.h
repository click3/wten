
namespace wten {

namespace uis {

class UIStringBox : public UIBox {
public:
	UIStringBox(boost::shared_ptr<const std::string> filename, boost::shared_ptr<const std::string> text);
	~UIStringBox();
	boost::shared_ptr<const std::string> GetText() const;
	boost::optional<boost::shared_ptr<Error> > SetText(boost::shared_ptr<const std::string> text);
};

} // uis

} // wten
