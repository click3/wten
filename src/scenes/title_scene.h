
namespace wten { namespace scenes {

class TitleScene : public SceneBase {
public:
	TitleScene();
	~TitleScene();

	boost::optional<boost::shared_ptr<Error> > SceneInitialize(void);
	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > EnterFrame(void);
private:
	boost::optional<boost::shared_ptr<Error> > OnSelect(boost::shared_ptr<Event> event);
	boost::optional<boost::shared_ptr<Error> > SaveDataLoad(void);

	const boost::shared_ptr<windows::ScriptWindow> script_window;
	boost::shared_ptr<Scene> next_scene;
	bool exit;
};

} // scenes

} // wten

