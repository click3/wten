
namespace wten { namespace scenes {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class TownScene : public SceneSelectorScene {
public:
	TownScene(boost::shared_ptr<const Graph> default_frame_graph);
	~TownScene();
};
#pragma warning(pop)

} // scenes

} // wten

