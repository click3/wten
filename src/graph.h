
namespace wten {

typedef boost::shared_ptr<void> DxLibGraphHandle;

class Graph : boost::noncopyable {
private:
	Graph(DxLibGraphHandle handle);
public:
	Graph(boost::shared_ptr<const std::string> filename);
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int x, unsigned int y) const;
	boost::optional<boost::shared_ptr<Error> > DrawEx(unsigned int x, unsigned int y, unsigned int w, unsigned int h) const;
	utility::opt_error<boost::shared_ptr<Graph> >::type Derivation(unsigned int x, unsigned int y, unsigned int w, unsigned int h) const;
private:
	const DxLibGraphHandle inner_ptr;
	const unsigned int width;
	const unsigned int height;
};

} // wten

