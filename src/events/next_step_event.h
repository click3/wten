
namespace wten {

class Window;

namespace events {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class NextStepEvent : public EventBase {
public:
	NextStepEvent(void);
	~NextStepEvent();
};
#pragma warning(pop)

} // events

} // wten
