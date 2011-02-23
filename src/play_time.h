
namespace wten {

class PlayTime : boost::noncopyable {
private:
	PlayTime();
public:
	~PlayTime();
	static boost::shared_ptr<PlayTime> GetCurrentInstance(void);
	void ResetPlayTime(void);
	unsigned int GetCurrentPlayTime(void) const;
	boost::shared_ptr<std::string> GetCurrentPlayTimeString(void) const;
protected:
	unsigned int start_time;
};

} // wten

