
namespace wten {

namespace windows {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class TextWindow : public WindowBase {
public:
	TextWindow(boost::shared_ptr<const std::wstring> text, boost::shared_ptr<const std::wstring> frame_filename);
	TextWindow(boost::shared_ptr<const std::wstring> text, boost::shared_ptr<Graph> frame);
	TextWindow(boost::shared_ptr<const std::wstring> text);
	~TextWindow();
	bool IsOkClose(void) const;
	void SetOkClose(bool flag);
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
private:
	boost::optional<boost::shared_ptr<Error> > OnOK(void);

	bool ok_close;
	unsigned char padding[3]; //unused
	const boost::shared_ptr<uis::UIString> ui_string;
	const boost::shared_ptr<uis::UIBox> frame;
};
#pragma warning(pop)
#pragma pack(pop)

} // windows

} // wten
