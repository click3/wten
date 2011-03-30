
namespace wten {

class CharData;

namespace uis {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UITairetsu : public UIBase {
public:
	UITairetsu(boost::shared_ptr<const std::wstring> frame_filename, boost::shared_ptr<const std::wstring> arrow_filename = utility::WChar2Ptr(L"data/ui/arrow1.png"));
	UITairetsu(boost::shared_ptr<const Graph> frame_graph, boost::shared_ptr<const std::wstring> arrow_filename = utility::WChar2Ptr(L"data/ui/arrow1.png"));
	~UITairetsu();
	boost::optional<boost::shared_ptr<Error> > Set(boost::shared_ptr<CharData> char_data);
	boost::optional<boost::shared_ptr<Error> > Select(unsigned int index);
	enum MOVE_FOCUS {
		MOVE_FOCUS_UP,
		MOVE_FOCUS_DOWN
	};
	boost::optional<boost::shared_ptr<Error> > Select(MOVE_FOCUS move_mode);
	unsigned int GetIndex() const;
	std::vector<boost::shared_ptr<CharData> > GetCharDataList(void) const;
	boost::optional<boost::shared_ptr<Error> > SetOwnerWindow(boost::weak_ptr<const windows::WindowBase> window);
	boost::optional<boost::shared_ptr<Error> > ClearOwnerWindow(void);
	boost::optional<boost::shared_ptr<Error> > ResetUI(void);
	boost::optional<boost::shared_ptr<Error> > Move(void);
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(void);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth() const;
	utility::opt_error<unsigned int>::type CalcHeight() const;
protected:
	unsigned int index;
	const boost::shared_ptr<UIImage> arrow;
	std::vector<boost::shared_ptr<CharData> > char_data_list;
	const std::vector<boost::shared_ptr<UIString> > ui_string_list;
	const boost::shared_ptr<UIQueue> ui_queue;
};
#pragma warning(pop)
#pragma pack(pop)

} // uis

} // wten
