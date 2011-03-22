
namespace wten {

namespace uis {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UIPager : public UIBase {
public:
	UIPager(const std::vector<boost::shared_ptr<uis::UIBase> > &page_list, boost::shared_ptr<const Graph> arrow_enable, boost::shared_ptr<Graph> arrow_disble);
	UIPager(const std::vector<boost::shared_ptr<uis::UIBase> > &page_list, boost::shared_ptr<const std::wstring> arrow_enable_path = utility::WChar2Ptr(L"data/ui/arrow2_enable.png"), boost::shared_ptr<const std::wstring> arrow_disble_path = utility::WChar2Ptr(L"data/ui/arrow2_disable.png"));
	~UIPager();
	boost::optional<boost::shared_ptr<Error> > SetOwnerWindow(boost::weak_ptr<const windows::WindowBase> window);
	boost::optional<boost::shared_ptr<Error> > ClearOwnerWindow(void);
	enum MOVE_TYPE {
		MOVE_TYPE_PREV,
		MOVE_TYPE_NEXT,
	};
	boost::optional<boost::shared_ptr<Error> > Select(MOVE_TYPE move_type);
	unsigned int GetIndex(void) const;
	boost::shared_ptr<uis::UIBase> GetPage(void) const;
	boost::optional<boost::shared_ptr<Error> > Move(void);
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Resize(void);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcPageWidth() const;
	utility::opt_error<unsigned int>::type CalcPageHeight() const;
	utility::opt_error<unsigned int>::type CalcWidth() const;
	utility::opt_error<unsigned int>::type CalcHeight() const;
	unsigned int GetPageCount(void) const;
protected:
	const std::vector<boost::shared_ptr<uis::UIBase> > page_list;
	const boost::shared_ptr<UIString> pager_label;
	const boost::shared_ptr<UIImage> next_arrow_enable;
	const boost::shared_ptr<UIImage> next_arrow_disable;
	const boost::shared_ptr<UIImage> prev_arrow_enable;
	const boost::shared_ptr<UIImage> prev_arrow_disable;
	unsigned int page_index;
};
#pragma warning(pop)
#pragma pack(pop)

} // uis

} // wten
