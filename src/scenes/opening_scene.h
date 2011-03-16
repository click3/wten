
namespace wten { namespace scenes {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class OpeningScene : public SceneBase {
public:
	OpeningScene();
	~OpeningScene();

	boost::optional<boost::shared_ptr<Error> > SceneInitialize(void);
	boost::optional<boost::shared_ptr<Error> > NextStep(boost::shared_ptr<Event> event);
	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > EnterFrame(void);
private:
	const boost::shared_ptr<windows::ScriptWindow> script_window;
	boost::shared_ptr<Scene> next_scene;
};
#pragma warning(pop)

} // scenes

} // wten

