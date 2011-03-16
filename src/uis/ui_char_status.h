
namespace wten {

class CharData;

namespace uis {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UICharStatus : public UIBox {
public:
	UICharStatus(boost::shared_ptr<const std::string> frame_filename, boost::shared_ptr<const PTData> pt_data, unsigned int char_index);
	~UICharStatus();
	enum CHANGE_INDEX {
		CHANGE_INDEX_NEXT,
		CHANGE_INDEX_BACK,
	};
	boost::optional<boost::shared_ptr<Error> > ChangeChar(CHANGE_INDEX change_index);
	boost::optional<boost::shared_ptr<Error> > ReloadStatus(void);
protected:
	boost::shared_ptr<const CharData> char_data;
	unsigned int char_index;
	const boost::shared_ptr<const PTData> pt_data;

	const std::vector<boost::shared_ptr<uis::UIString> > text_ui_list;
};
#pragma warning(pop)

} // uis

} // wten
