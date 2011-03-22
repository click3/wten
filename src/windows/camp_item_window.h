
namespace wten {

namespace windows {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class CampItemWindow : public CampBaseWindow {
public:
	CampItemWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const std::wstring> default_frame_filename);
	CampItemWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const Graph> default_frame_graph);
	~CampItemWindow();
	boost::optional<boost::shared_ptr<Error> > WindowInitialize(void);
	utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type NotifyEvent(boost::shared_ptr<Event> event);

	enum STATE {
		STATE_INITIALIZE,
		STATE_CHAR_SELECT,
		STATE_ITEM_SELECT,
		STATE_COMMAND_SELECT,
		STATE_TARGET_SELECT,
		STATE_APPLY,
	};

	enum COMMAND {
		COMMAND_MOVE,
		COMMAND_USE,
		COMMAND_EQUIP,
		COMMAND_EQUIP_RELEASE,
		COMMAND_DELETE,
	};
protected:
	boost::optional<boost::shared_ptr<Error> > OnKeyEvent(boost::shared_ptr<Event> event);
	boost::optional<boost::shared_ptr<Error> > OnSelectEvent(boost::shared_ptr<Event> event);
	boost::optional<boost::shared_ptr<Error> > OnNextStepEvent(boost::shared_ptr<Event> event);
	boost::optional<boost::shared_ptr<Error> > StateBack(void);

	boost::optional<boost::shared_ptr<Error> > StateToCharSelect(void);
	boost::optional<boost::shared_ptr<Error> > StateToItemSelect(boost::shared_ptr<void> data);
	boost::optional<boost::shared_ptr<Error> > StateToCommandSelect(boost::shared_ptr<void> data);
	boost::optional<boost::shared_ptr<Error> > StateToTargetSelect(boost::shared_ptr<void> data);
	boost::optional<boost::shared_ptr<Error> > StateToApply(boost::shared_ptr<void> data);

	boost::optional<boost::shared_ptr<Error> > CommandMove(void);
	boost::optional<boost::shared_ptr<Error> > CommandUse(void);
	boost::optional<boost::shared_ptr<Error> > CommandEquip(void);
	boost::optional<boost::shared_ptr<Error> > CommandEquipRelease(void);
	boost::optional<boost::shared_ptr<Error> > CommandDelete(void);

	STATE state;

	boost::shared_ptr<SelectWindow> char_select_window;
	boost::shared_ptr<CharData> selected_char;

	boost::shared_ptr<SelectWindow> item_select_window;
	boost::shared_ptr<uis::UIStringBox> item_description_ui;
	boost::shared_ptr<Item> selected_item;

	boost::shared_ptr<SelectWindow> item_command_select_window;
	boost::shared_ptr<COMMAND> selected_command;

	boost::shared_ptr<SelectWindow> item_target_select_window;
	boost::shared_ptr<CharData> target_char;

	boost::shared_ptr<const std::wstring> error_message;
};
#pragma warning(pop)

} // windows

} // wten
