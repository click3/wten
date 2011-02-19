
namespace wten {

class WindowManager;

namespace scenes {

class SceneBase : public Scene, public EventNotifyInterface, public boost::enable_shared_from_this<SceneBase> {
public:
	SceneBase() :
		window_manager(new WindowManager())
	{ }
	~SceneBase() { }

	boost::optional<boost::shared_ptr<Error> > DoStart(void) {
		boost::shared_ptr<SceneBase> this_ptr = shared_from_this();
		BOOST_ASSERT(this_ptr);
		EventNotify::Regist(this_ptr);
		OPT_ERROR(this_ptr->SceneInitialize());
		return boost::none;
	}

	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DoNextFrame(void)  {
		BOOST_ASSERT(window_manager);
		OPT_ERROR(window_manager->DoEvent());
		OPT_ERROR(window_manager->Draw());

		return boost::none;
	}
	void EventNotifyCallback(boost::shared_ptr<Event> event) {
		BOOST_ASSERT(window_manager);
		if(boost::optional<boost::shared_ptr<Error> > error = window_manager->EnqueueEvent(event)) {
			error.get()->Abort();
		}
	}

	/**
	 * 派生クラスではここに初期化コードを実装する
	 */
	virtual boost::optional<boost::shared_ptr<Error> > SceneInitialize(void) {
		return boost::none;
	}
protected:
	const boost::shared_ptr<WindowManager> window_manager;
};

} // scenes

} // wten
