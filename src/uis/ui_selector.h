
namespace wten {

namespace uis {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UISelector : public UIBase {
public:
	UISelector(const std::vector<boost::shared_ptr<const std::wstring> >& texts = std::vector<boost::shared_ptr<const std::wstring> >(), unsigned int line_count = 1, boost::shared_ptr<const std::wstring> arrow_filename = boost::shared_ptr<const std::wstring>(new std::wstring(L"data/ui/arrow1.png")));
	~UISelector();
	boost::optional<boost::shared_ptr<Error> > Select(boost::shared_ptr<const std::wstring> text);
	boost::optional<boost::shared_ptr<Error> > Select(unsigned int index);
	enum MOVE_FOCUS {
		MOVE_FOCUS_UP,
		MOVE_FOCUS_DOWN,
		MOVE_FOCUS_LEFT,
		MOVE_FOCUS_RIGHT,
	};
	boost::optional<boost::shared_ptr<Error> > Select(MOVE_FOCUS move_mode);
	utility::opt_error<unsigned int>::type GetIndex() const;
	utility::opt_error<boost::shared_ptr<const std::wstring> >::type GetText() const;
	boost::optional<boost::shared_ptr<Error> > SetOwnerWindow(boost::weak_ptr<const windows::WindowBase> window);
	boost::optional<boost::shared_ptr<Error> > ClearOwnerWindow(void);
	boost::optional<boost::shared_ptr<Error> > Move(void);
	boost::optional<boost::shared_ptr<Error> > Move(unsigned int x, unsigned int y);
	boost::optional<boost::shared_ptr<Error> > Resize(unsigned int width, unsigned int height);
	boost::optional<boost::shared_ptr<Error> > Resize(void);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth() const;
	utility::opt_error<unsigned int>::type CalcHeight() const;
	utility::opt_error<unsigned int>::type CalcLineWidth(unsigned int index) const;
	utility::opt_error<unsigned int>::type CalcLineHeight(unsigned int index) const;
	unsigned int GetCount() const;
protected:
	const std::vector<boost::shared_ptr<UIString> > select_list;
	const boost::shared_ptr<UIImage> arrow;
	unsigned int index;
	const unsigned int line_count;
	const unsigned int line_size;
};
#pragma warning(pop)

} // uis

} // wten
