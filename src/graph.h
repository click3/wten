
namespace wten {

typedef boost::shared_ptr<void> DxLibGraphHandle;

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class Graph : boost::noncopyable {
private:
	Graph(DxLibGraphHandle handle);
public:
	Graph(boost::shared_ptr<const std::wstring> filename);
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int x, unsigned int y) const;
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int x, unsigned int y, bool turn, double rate, double angle, unsigned int center_x, unsigned int center_y) const;
	boost::optional<boost::shared_ptr<Error> > DrawEx(unsigned int x, unsigned int y, unsigned int w, unsigned int h) const;
	utility::opt_error<boost::shared_ptr<Graph> >::type Derivation(unsigned int x, unsigned int y, unsigned int w, unsigned int h) const;
private:
	const DxLibGraphHandle inner_ptr;
	const unsigned int width;
	const unsigned int height;
};
#pragma warning(pop)

} // wten

