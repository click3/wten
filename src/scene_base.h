
namespace wten {

class WindowManager;

namespace scenes {

class SceneBase : public Scene, public EventNotifyInterface {
private:
	SceneBase();
public:
	~SceneBase();
	static boost::shared_ptr<Scene> CreateScene();
	boost::optional<boost::shared_ptr<Error> > DoStart(void);
	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DoNextFrame(void);
	void EventNotifyCallback(boost::shared_ptr<Event> event);
private:
	boost::weak_ptr<SceneBase> this_ptr;
protected:
	boost::shared_ptr<WindowManager> window_manager;
};

} // scenes

} // wten
