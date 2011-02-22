
namespace wten { namespace scenes {

class DebugScene : public SceneBase {
public:
	DebugScene();
	~DebugScene();
	boost::optional<boost::shared_ptr<Error> > SceneInitialize(void);
	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > EnterFrame(void);
};

} // scenes

} // wten

