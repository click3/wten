
namespace wten { namespace scenes {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class BarScene : public CampScene {
public:

	BarScene();
	~BarScene();

	boost::optional<boost::shared_ptr<Error> > SceneInitialize(void);
	boost::optional<boost::shared_ptr<Error> > StepInitialize(void);
	boost::optional<boost::shared_ptr<Error> > OnEvent(boost::shared_ptr<Event> event);
	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > EnterFrame(void);
private:
	boost::optional<boost::shared_ptr<Error> > AddEvent(EVENT_TYPE event_type);

	unsigned int next_step;
	unsigned int current_step;
	const boost::shared_ptr<const std::string> title;
	const boost::shared_ptr<windows::ScriptWindow> script_window;
	boost::shared_ptr<Scene> next_scene;
};
#pragma warning(pop)

} // scenes

} // wten

