
namespace wten {

namespace windows {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class SelectWindow : public WindowBase {
public:
	SelectWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > >& input, unsigned int line_count, boost::shared_ptr<const std::wstring> frame_filename);
	SelectWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > >& input, unsigned int line_count, boost::shared_ptr<const Graph> frame);
	~SelectWindow();
	bool IsSelectClose(void) const;
	void SetSelectClose(bool flag);
	boost::optional<boost::shared_ptr<Error> > SetCancelSelectionDataIndex(boost::optional<unsigned int> cancel_data_index);
	boost::optional<boost::shared_ptr<Error> > SetCancelSelectionDataIndex(boost::shared_ptr<void> data);
	boost::optional<boost::shared_ptr<Error> > SetCancelSelectionDataIndex(boost::shared_ptr<const std::wstring> text);
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	boost::optional<boost::shared_ptr<Error> > Resize();
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
private:
	boost::optional<boost::shared_ptr<Error> > OnSelect(void);
	boost::optional<boost::shared_ptr<Error> > OnSelectChange(void);

	bool select_close;
	unsigned char padding[3]; //unused
	const boost::shared_ptr<uis::UISelector> selector;
	const boost::shared_ptr<uis::UIBox> frame;
	const std::vector<boost::shared_ptr<void> > data_list;
	boost::optional<unsigned int> cancel_data_index;
};
#pragma warning(pop)
#pragma pack(pop)

} // windows

} // wten
