
namespace wten { namespace scenes {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class CampScene : public SceneBase {
public:
	CampScene(boost::shared_ptr<const std::string> default_frame_filename = boost::shared_ptr<const std::string>(new std::string("data/ui/box1.png")));
	~CampScene();

	boost::optional<boost::shared_ptr<Error> > SceneInitialize(void);
	boost::optional<boost::shared_ptr<Error> > OnKeyEvent(boost::shared_ptr<Event> event);
	boost::optional<boost::shared_ptr<Error> > OnNextWindowEvent(boost::shared_ptr<Event> event);
	void CampDisabled(void);
private:
	boost::optional<boost::shared_ptr<Error> > AddCampWindow(void);

	const boost::shared_ptr<windows::ScriptWindow> camp_script_window;
	bool camp_enabled;
};
#pragma warning(pop)

} // scenes

} // wten

