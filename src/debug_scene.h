
namespace wten { namespace scenes {

class DebugScene : public Scene {
private:
	class DebugSceneImpl;
	boost::shared_ptr<DebugSceneImpl> impl_;
public:
	DebugScene();
	boost::optional<boost::shared_ptr<Error> > DoStart(void);
	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DoNextFrame(void);
};

} // scenes

} // wten

