
namespace wten {

namespace uis {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UIInputDlg : public UIBox {
public:
	UIInputDlg(boost::shared_ptr<const std::string> message, boost::shared_ptr<const std::string> frame_filename);
	~UIInputDlg();
	boost::shared_ptr<std::string> GetText(void) const;
protected:
	const boost::shared_ptr<UIInputString> ui_input_string;
};
#pragma warning(pop)

} // uis

} // wten
