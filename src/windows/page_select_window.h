
namespace wten {

namespace windows {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class PageSelectWindow : public WindowBase {
public:
	PageSelectWindow(const std::vector<boost::tuple<boost::shared_ptr<uis::UIBase>, boost::shared_ptr<void> > >& input, unsigned int page_size, boost::shared_ptr<const std::wstring> frame_filename);
	PageSelectWindow(const std::vector<boost::tuple<boost::shared_ptr<uis::UIBase>, boost::shared_ptr<void> > >& input, unsigned int page_size, boost::shared_ptr<const Graph> frame);
	~PageSelectWindow();
	bool IsSelectClose(void) const;
	void SetSelectClose(bool flag);
	boost::optional<boost::shared_ptr<Error> > SetCancelData(boost::optional<boost::shared_ptr<void> > data);
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	boost::optional<boost::shared_ptr<Error> > Resize();
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);
private:
	boost::optional<boost::shared_ptr<Error> > OnSelect(void);
	boost::optional<boost::shared_ptr<Error> > OnSelectChange(void);
	boost::optional<boost::shared_ptr<Error> > OnCancel(void);

	bool select_close;
	unsigned char padding[3]; //unused
	const std::vector<boost::shared_ptr<uis::UISelectorBase> > selector_list;
	const boost::shared_ptr<uis::UIPager> pager;
	const boost::shared_ptr<uis::UIBox> frame;
	const std::vector<std::vector<boost::shared_ptr<void> > > data_list;
	boost::optional<boost::shared_ptr<void> > cancel_data;
};
#pragma warning(pop)
#pragma pack(pop)

} // windows

} // wten
