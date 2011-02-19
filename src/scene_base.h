
namespace wten {

class WindowManager;

namespace scenes {

class SceneBase : public Scene, public EventNotifyInterface, public boost::enable_shared_from_this<SceneBase> {
public:
	SceneBase();
	~SceneBase();

	boost::optional<boost::shared_ptr<Error> > DoStart(void);

	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DoNextFrame(void);
	void EventNotifyCallback(boost::shared_ptr<Event> event);

	/**
	 * 派生クラスではここに初期化コードを実装する
	 */
	virtual boost::optional<boost::shared_ptr<Error> > SceneInitialize(void);
protected:
	const boost::shared_ptr<WindowManager> window_manager;
};

} // scenes

} // wten
