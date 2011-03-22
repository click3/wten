
namespace wten {

namespace uis {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UIInputDlg : public UIBox {
private:
	void Initialize(boost::shared_ptr<const std::wstring> message);
public:
	UIInputDlg(boost::shared_ptr<const std::wstring> message, boost::shared_ptr<const std::wstring> frame_filename);
	UIInputDlg(boost::shared_ptr<const std::wstring> message, boost::shared_ptr<const Graph> frame_graph);
	~UIInputDlg();
	boost::shared_ptr<std::wstring> GetText(void) const;
protected:
	const boost::shared_ptr<UIInputString> ui_input_string;
};
#pragma warning(pop)

} // uis

} // wten
