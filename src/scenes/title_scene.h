
namespace wten { namespace scenes {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class TitleScene : public SceneBase {
	void Initialize(void);
public:
	TitleScene(boost::shared_ptr<const std::wstring> default_frame_filename);
	TitleScene(boost::shared_ptr<const Graph> default_frame_graph);
	~TitleScene();

	boost::optional<boost::shared_ptr<Error> > SceneInitialize(void);
	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > EnterFrame(void);
private:
	boost::optional<boost::shared_ptr<Error> > OnSelect(boost::shared_ptr<Event> event);
	boost::optional<boost::shared_ptr<Error> > SaveDataLoad(void);

	const boost::shared_ptr<windows::ScriptWindow> script_window;
	boost::shared_ptr<Scene> next_scene;
	bool exit;
	unsigned char padding[3]; //unused
};
#pragma warning(pop)
#pragma pack(pop)

} // scenes

} // wten

