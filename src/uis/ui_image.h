
namespace wten {

namespace uis {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UIImage : public UIBase {
public:
	UIImage(boost::shared_ptr<const std::wstring> filename);
	UIImage(boost::shared_ptr<const Graph> image);
	~UIImage();
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth() const;
	utility::opt_error<unsigned int>::type CalcHeight() const;
protected:
	const boost::shared_ptr<const Graph> image;
};
#pragma warning(pop)

} // uis

} // wten
