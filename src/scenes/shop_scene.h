
namespace wten { namespace scenes {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class ShopScene : public CampScene {
private:
	void Initialize(void);
public:
	ShopScene(boost::shared_ptr<const std::wstring> default_frame_filename);
	ShopScene(boost::shared_ptr<const Graph> default_frame_graph);
	~ShopScene();

	boost::optional<boost::shared_ptr<Error> > SceneInitialize(void);
	boost::optional<boost::shared_ptr<Error> > StepInitialize(void);
	boost::optional<boost::shared_ptr<Error> > OnEvent(boost::shared_ptr<Event> event);
	boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > EnterFrame(void);
private:
	boost::optional<boost::shared_ptr<Error> > AddEvent(EVENT_TYPE event_type);

	unsigned int next_step;
	unsigned int current_step;
	const boost::shared_ptr<const std::wstring> title;
	const boost::shared_ptr<windows::ScriptWindow> script_window;
	boost::shared_ptr<const ItemInfo> buy_item;
	boost::shared_ptr<CharData> buy_character;
	bool money_collect_flag;
	unsigned char padding[3]; // unused
	boost::shared_ptr<Scene> next_scene;
};
#pragma warning(pop)
#pragma pack(pop)

} // scenes

} // wten

