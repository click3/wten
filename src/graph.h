
namespace wten {

typedef int DxLibGraphHandle;

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4512)
class GraphImpl {
public:
	GraphImpl(boost::shared_ptr<const std::wstring> filename);
	GraphImpl(boost::shared_ptr<const std::wstring> source_filename, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
	GraphImpl(const GraphImpl& obj);
	~GraphImpl(void);

	std::size_t GetHash(void) const;
	void ClearHandle(void);
	boost::shared_ptr<const std::wstring> GetFilename(void) const;
	DxLibGraphHandle GetHandle(void) const;
	unsigned int GetWidth(void) const;
	unsigned int GetHeight(void) const;
	bool operator==(const GraphImpl &obj) const;
protected:
	DxLibGraphHandle LoadGraph();

	const boost::shared_ptr<const std::wstring> filename;
	const boost::shared_ptr<const std::wstring> source_filename;
	const unsigned int x1;
	const unsigned int y1;
	const unsigned int x2;
	const unsigned int y2;

	boost::optional<DxLibGraphHandle> handle;
};
#pragma warning(pop)
#pragma pack(pop)

std::size_t hash_value(const GraphImpl &obj);

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class Graph : boost::noncopyable, boost::flyweight<GraphImpl> {
	Graph(boost::shared_ptr<const std::wstring> source_filename, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
public:
	Graph(boost::shared_ptr<const std::wstring> filename);
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int x, unsigned int y) const;
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int x, unsigned int y, bool turn, double rate, double angle, unsigned int center_x, unsigned int center_y) const;
	boost::optional<boost::shared_ptr<Error> > DrawEx(unsigned int x, unsigned int y, unsigned int w, unsigned int h) const;
	utility::opt_error<boost::shared_ptr<Graph> >::type Derivation(unsigned int x, unsigned int y, unsigned int w, unsigned int h) const;
	static boost::optional<boost::shared_ptr<Error> > AllGraphReload(void);
};
#pragma warning(pop)
#pragma pack(pop)

} // wten
