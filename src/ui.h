
namespace wten {

class Window;

class UI {
public:
	virtual ~UI() { };
	virtual bool SetOwnerWindow(boost::weak_ptr<Window> window);
	virtual bool Draw(void);
};

} // wten
