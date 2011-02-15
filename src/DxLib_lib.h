
namespace wten {

namespace errors {

class DxLibError : public ErrorNormal {
public:
	DxLibError() : ErrorNormal(ERROR_CODE_DXLIB_INTERNAL_ERROR) {}
};

} // errors

class DxLibWrapper : boost::noncopyable {
public:
	DxLibWrapper(bool window_mode = true, const std::string& title = std::string("Title"));
	~DxLibWrapper();

	static boost::optional<boost::shared_ptr<Error> > ChangeWindowMode(bool window_mode);
	static boost::optional<boost::shared_ptr<Error> > SetWindowTitle(const std::string& title);

	enum SCREEN_MODE {
		SCREEN_MODE_FRONT,
		SCREEN_MODE_BACK,
		SCREEN_MODE_WORK,
		SCREEN_MODE_TEMPFRONT,
	};
	static boost::optional<boost::shared_ptr<Error> > SetDrawScreen(SCREEN_MODE mode);
	static bool ProcessMessage();
	static boost::optional<boost::shared_ptr<Error> > ClearDrawScreen();
	static boost::optional<boost::shared_ptr<Error> > ScreenFlip();
	static utility::opt_error<boost::tuple<unsigned int,unsigned int> >::type GetWindowSize();
	static utility::opt_error<unsigned int>::type GetFontHeight();
	static utility::opt_error<unsigned int>::type DxLibWrapper::GetFontWidth(const std::string& text);
	static boost::optional<boost::shared_ptr<Error> > DrawString(unsigned int x, unsigned int y, const std::string& text, utility::Color color);
	static utility::opt_error<unsigned int>::type GetJoypadInputState(void);
};

} // wten
