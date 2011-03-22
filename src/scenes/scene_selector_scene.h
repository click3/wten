
namespace wten { namespace scenes {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class SceneSelectorScene : public CampScene {
	void Initialize(void);
public:
	typedef boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<Scene> > SCENE_PAIR;

	SceneSelectorScene(boost::shared_ptr<const std::wstring> default_frame_filename, boost::shared_ptr<const std::wstring> title, const std::vector<SCENE_PAIR>& scene_list);
	SceneSelectorScene(boost::shared_ptr<const Graph> default_frame_graph, boost::shared_ptr<const std::wstring> title, const std::vector<SCENE_PAIR>& scene_list);
	~SceneSelectorScene();

	boost::optional<boost::shared_ptr<Error> > SceneInitialize(void);
	boost::optional<boost::shared_ptr<Error> > OnSelect(boost::shared_ptr<Event> event);
	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > EnterFrame(void);
private:
	const boost::shared_ptr<const std::wstring> title;
	const std::vector<SCENE_PAIR> scene_list;
	const boost::shared_ptr<windows::ScriptWindow> script_window;
	boost::shared_ptr<Scene> next_scene;
};
#pragma warning(pop)

} // scenes

} // wten

