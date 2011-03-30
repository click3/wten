
namespace wten {

enum EVENT_TYPE {
	EVENT_TYPE_KEY,
	EVENT_TYPE_ON_SELECT,
	EVENT_TYPE_ON_SELECT_CHANGE,
	EVENT_TYPE_POP_WINDOW,
	EVENT_TYPE_NEXT_STEP,
	EVENT_TYPE_INPUT_STRING,
	EVENT_TYPE_NEXT_WINDOW,
	EVENT_TYPE_ITEM_BUY,
	EVENT_TYPE_ITEM_BUY_CANCEL,
	EVENT_TYPE_TAIRETSU_SELECTED,
};

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class Event : boost::noncopyable {
public:
	virtual ~Event() { }
	virtual EVENT_TYPE GetEventType(void) const = 0;
};
#pragma warning(pop)

} // wten
