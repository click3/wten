
namespace wten {

namespace uis {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UIDummy : public UIBase {
public:
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
};
#pragma warning(pop)

} // uis

} // wten
