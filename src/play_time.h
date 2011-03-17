
namespace wten {

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class PlayTime : boost::noncopyable {
private:
	PlayTime();
public:
	~PlayTime();
	static boost::shared_ptr<PlayTime> GetCurrentInstance(void);
	void ResetPlayTime(void);
	unsigned int GetCurrentPlayTime(void) const;
	boost::shared_ptr<std::wstring> GetCurrentPlayTimeString(void) const;
protected:
	unsigned int start_time;
};
#pragma warning(pop)

} // wten

