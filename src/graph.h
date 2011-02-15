
namespace wten {

typedef boost::shared_ptr<void> DxLibGraphHandle;

class Graph : boost::noncopyable {
private:
	DxLibGraphHandle inner_ptr;
	Graph(const DxLibGraphHandle& handle);
	boost::optional<boost::tuple<int, int>> GetSize(void);
	unsigned int width;
	unsigned int height;
public:
	Graph(const std::string& filename);
	unsigned int GetWidth();
	unsigned int GetHeight();
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > DrawEx(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
	boost::optional<boost::shared_ptr<Graph>> Derivation(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
};

} // wten

