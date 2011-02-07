
namespace wten {

typedef boost::shared_ptr<void> DxLibGraphHandle;

class Graph {
private:
	DxLibGraphHandle inner_ptr;
	Graph(const DxLibGraphHandle& handle);
	boost::optional<boost::tuple<int, int>> GetSize(void);
	unsigned int width;
	unsigned int height;
public:
	Graph(const TCHAR* filename);
	unsigned int GetWidth();
	unsigned int GetHeight();
	bool Draw(unsigned int x, unsigned int y);
	bool DrawEx(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
	boost::optional<boost::shared_ptr<Graph>> Derivation(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
};

} // wten

