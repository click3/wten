
namespace wten {

namespace windows {

class WindowBase : public Window, public boost::enable_shared_from_this<WindowBase> {
public:
	WindowBase(boost::shared_ptr<const std::string> default_frame_filename = boost::shared_ptr<const std::string>());
	~WindowBase();
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetPoint(void) const;
	utility::opt_error<boost::tuple<unsigned int, unsigned int> >::type GetSize(void) const;
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);

	boost::optional<boost::shared_ptr<Error> > AddUI(boost::shared_ptr<UI> ui);
	utility::opt_error<bool>::type RemoveUI(boost::shared_ptr<UI> ui);
	boost::optional<boost::shared_ptr<Error> > ClearUI(void);
	boost::optional<boost::shared_ptr<Error> > RemoveThisWindow(void);

	boost::optional<boost::shared_ptr<Error> > AddUI(boost::shared_ptr<uis::UIBase> ui, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > AddBoxUI(uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > AddImageUI(boost::shared_ptr<const std::string> image_filename, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > AddTextUI(boost::shared_ptr<const std::string> text, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > AddPTStatusUI(boost::shared_ptr<const PTData> pt_data, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
private:
	std::vector<boost::shared_ptr<UI> > ui_stack;
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
	boost::shared_ptr<const std::string> default_frame_filename;
};

} // windows

} // wten
