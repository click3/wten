
namespace wten {

class DxLibWrapper;
class Scene;
class Error;
class PTData;

class WTen : boost::noncopyable {
public:
	WTen(boost::shared_ptr<Scene> start_scene);
	~WTen();
	static boost::shared_ptr<std::string> CreateWindowTitle(void);
	boost::optional<boost::shared_ptr<Error> > DoStart(boost::shared_ptr<PTData> pt);
private:
	typedef boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > LoopResult;

	LoopResult DoMainLoop(void);

	const boost::shared_ptr<DxLibWrapper> lib;
	boost::shared_ptr<Scene> scene;
};

} // wten
