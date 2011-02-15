
namespace wten {

namespace uis {

class UIImage : public UIBase {
public:
	UIImage(const boost::shared_ptr<std::string>& filename);
	~UIImage();
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth();
	utility::opt_error<unsigned int>::type CalcHeight();
protected:
	boost::shared_ptr<Graph> image;
};

} // uis

} // wten
