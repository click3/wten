
namespace wten {

class WindowManager;

namespace scenes {

class SceneBase : public Scene, public EventNotifyInterface, public boost::enable_shared_from_this<SceneBase> {
public:
	SceneBase();
	~SceneBase();

	boost::optional<boost::shared_ptr<Error> > DoStart(boost::shared_ptr<PTData> pt);

	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DoNextFrame(void);
	void EventNotifyCallback(boost::shared_ptr<Event> event);

	/**
	 * 派生クラスではここに初期化処理を実装する
	 */
	virtual boost::optional<boost::shared_ptr<Error> > SceneInitialize(void) = 0;

	/**
	 * 派生クラスではここに毎フレームごとの処理を実装する
	 */
	virtual boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > EnterFrame(void) = 0;
protected:
	const boost::shared_ptr<WindowManager> window_manager;
	const boost::shared_ptr<windows::WindowBase> base_window;
	boost::shared_ptr<PTData> pt;
};

} // scenes

} // wten
