
namespace wten {

class PTData;

namespace uis {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UIPTStatus : public UIBox {
private:
	void Initialize(void);
public:
	UIPTStatus(boost::shared_ptr<const std::wstring> frame_filename, boost::shared_ptr<const PTData> pt_data);
	UIPTStatus(boost::shared_ptr<const Graph> frame_graph, boost::shared_ptr<const PTData> pt_data);
	~UIPTStatus();
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
protected:
	const boost::shared_ptr<const PTData> pt_data;
	const std::vector<const std::vector<boost::shared_ptr<std::wstring> > > text_list;
	const boost::shared_ptr<UIQueue> queue_ui;
};
#pragma warning(pop)

} // uis

} // wten
