
namespace wten {

namespace windows {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class TairetsuWindow : public WindowBase {
public:
	TairetsuWindow(std::vector<boost::shared_ptr<CharData> > char_list, bool is_full_member, boost::shared_ptr<const std::wstring> default_frame_filename);
	TairetsuWindow(std::vector<boost::shared_ptr<CharData> > char_list, bool is_full_member, boost::shared_ptr<const Graph> default_frame_graph);
	~TairetsuWindow();
	void SetCancelEvent(boost::optional<boost::shared_ptr<Event> > cancel_event);
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	boost::optional<boost::shared_ptr<Error> > ResetUI(void);
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
private:
	boost::optional<boost::shared_ptr<Error> > OnCharSelect(void);
	boost::optional<boost::shared_ptr<Error> > OnTairetsuSelect(void);
	boost::optional<boost::shared_ptr<Error> > OnTairetsuCancel(void);
	boost::optional<boost::shared_ptr<Error> > OnTairetsuSelectedEvent(void);
	boost::optional<boost::shared_ptr<Error> > OnCancelEvent(void);

	std::vector<boost::shared_ptr<CharData> > char_list;
	const bool is_full_member;
	bool select_char;
	unsigned char padding[2]; // unused
	boost::shared_ptr<CharData> selected_char;
	const boost::shared_ptr<uis::UIBox> frame;
	boost::shared_ptr<uis::UIPager> selector;
	const boost::shared_ptr<uis::UITairetsu> tairetsu;
	boost::optional<boost::shared_ptr<Event> > cancel_event;
};
#pragma warning(pop)
#pragma pack(pop)

} // windows

} // wten
