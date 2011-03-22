
namespace wten { namespace scenes {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class OpeningScene : public SceneBase {
private:
	void Initialize(void);
public:
	OpeningScene(boost::shared_ptr<const std::wstring> default_frame_filename);
	OpeningScene(boost::shared_ptr<const Graph> default_frame_graph);
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

