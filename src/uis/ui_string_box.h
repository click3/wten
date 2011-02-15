
namespace wten {

namespace uis {

class UIStringBox : public UIBox {
public:
	UIStringBox(const boost::shared_ptr<std::string>& filename, const boost::shared_ptr<std::string>& text);
	~UIStringBox();
	boost::optional<boost::shared_ptr<Error> > SetText(const boost::shared_ptr<std::string>& text);
};

} // uis

} // wten
