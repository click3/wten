
namespace wten {

class WindowManager;

namespace scenes {

template<class T = SceneBase>
class SceneBase : public Scene, public EventNotifyInterface {
protected:
	SceneBase() :
		window_manager(new WindowManager())
	{ }

public:
	~SceneBase() { }

	static boost::shared_ptr<Scene> CreateScene() {
		boost::shared_ptr<T> ptr(new T());
		BOOST_ASSERT(ptr);
		ptr->this_ptr = ptr;
		BOOST_ASSERT(ptr->this_ptr.lock());
		return ptr;
	}

	boost::optional<boost::shared_ptr<Error> > DoStart(void) {
		EventNotify::Regist(this_ptr);
		boost::shared_ptr<T> ptr = this_ptr.lock();
		if(!ptr) {
			return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
		}
		OPT_ERROR(ptr->SceneInitialize());
		return boost::none;
	}

	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DoNextFrame(void)  {
		if(!window_manager) {
			return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
		}
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
	boost::optional<boost::shared_ptr<Error> > SceneInitialize(void) {
		return boost::none;
	}
private:
	boost::weak_ptr<T> this_ptr;
protected:
	boost::shared_ptr<WindowManager> window_manager;
};

} // scenes

} // wten
