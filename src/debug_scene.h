
namespace wten { namespace scenes {

class DebugScene : public SceneBase<DebugScene> {
public:
	DebugScene();
	boost::optional<boost::shared_ptr<Error> > DoStart(void);
	boost::optional<boost::shared_ptr<Error> > SceneInitialize(void);
};

} // scenes

} // wten

