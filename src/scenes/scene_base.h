
namespace wten {

class WindowManager;

namespace scenes {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class SceneBase : public Scene, public EventNotifyInterface, public boost::enable_shared_from_this<SceneBase> {
private:
	void Initialize(void);
public:
	SceneBase(boost::shared_ptr<const std::wstring> default_frame_filename);
	SceneBase(boost::shared_ptr<const Graph> default_frame_graph);
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

	boost::optional<boost::shared_ptr<Error> > AddUI(boost::shared_ptr<uis::UIBase> ui, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > AddWindow(boost::shared_ptr<windows::WindowBase> window, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > AddBoxUI(uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > AddImageUI(boost::shared_ptr<const std::wstring> image_filename, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > AddTextUI(boost::shared_ptr<const std::wstring> text, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > AddPTStatusUI(boost::shared_ptr<const PTData> pt_data, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > AddCharStatusUI(boost::shared_ptr<const PTData> pt_data, unsigned int char_index, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > AddSelectorWindow(const std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > >& select_list, unsigned int line_count, boost::optional<unsigned int> cancel_index, unsigned int x = 50, unsigned int y = 85, unsigned int width = 540, unsigned int height = 180);
	boost::optional<boost::shared_ptr<Error> > AddTextWindow(boost::shared_ptr<const std::wstring> text, unsigned int x = 50, unsigned int y = 50, unsigned int width = 540, unsigned int height = 380);
	boost::optional<boost::shared_ptr<Error> > AddInputDlgWindow(boost::shared_ptr<const std::wstring> message, unsigned int x = 150, unsigned int y = 205, unsigned int width = 340, unsigned int height = 70);
	boost::optional<boost::shared_ptr<Error> > Clear(void);
protected:
	const boost::shared_ptr<WindowManager> window_manager;
	boost::shared_ptr<PTData> pt;
	const boost::shared_ptr<const Graph> default_frame_graph;
	const boost::shared_ptr<windows::WindowBase> base_window;
};
#pragma warning(pop)

} // scenes

} // wten
