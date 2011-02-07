
namespace wten {

class DxLibWrapper;
class Scene;
class Error;

class WTen : boost::noncopyable {
public:
	WTen(boost::shared_ptr<Scene> start_scene);
	~WTen();
	boost::optional<boost::shared_ptr<Error> > DoStart();
private:
	typedef boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > LoopResult;

	LoopResult DoMainLoop(void);

	boost::shared_ptr<Scene> scene;
	boost::shared_ptr<DxLibWrapper> lib;
};

} // wten
