
namespace wten {

namespace uis {

class UIDummy : public UIBase {
public:
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
};

} // uis

} // wten
