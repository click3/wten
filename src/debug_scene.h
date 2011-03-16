
namespace wten { namespace scenes {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class DebugScene : public SceneBase {
public:
	DebugScene();
	~DebugScene();
	boost::optional<boost::shared_ptr<Error> > SceneInitialize(void);
	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > EnterFrame(void);
};
#pragma warning(pop)

} // scenes

} // wten

