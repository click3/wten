
namespace wten {

class PTData;

namespace uis {

class UIPTStatus : public UIBox {
public:
	UIPTStatus(boost::shared_ptr<const std::string> frame_filename, boost::shared_ptr<const PTData> pt_data);
	~UIPTStatus();
protected:
	const boost::shared_ptr<const PTData> pt_data;
	const std::vector<const std::vector<boost::shared_ptr<std::string> > > text_list;
	const boost::shared_ptr<UIQueue> queue_ui;
};

} // uis

} // wten
