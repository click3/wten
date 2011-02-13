
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
			return boost::shared_ptr<Error>(new errors::ErrorNormal(ERROR_CODE_INTERNAL_ERROR));
		}
		boost::optional<boost::shared_ptr<Error> > error = ptr->SceneInitialize();
		if(error) {
			return error.get();
		}
		return boost::none;
	}

	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > DoNextFrame(void)  {
		if(!window_manager) {
			return boost::shared_ptr<Error>(new errors::ErrorNormal(ERROR_CODE_INTERNAL_ERROR));
		}

		if(boost::optional<boost::shared_ptr<Error> > error = window_manager->DoEvent()) {
			return error.get();
		}

		if(boost::optional<boost::shared_ptr<Error> > error = window_manager->Draw()) {
			return error.get();
		}

		return boost::none;
	}
	void EventNotifyCallback(boost::shared_ptr<Event> event) {
		BOOST_ASSERT(window_manager);
		window_manager->EnqueueEvent(event);
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
