
namespace wten {

namespace uis {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class UIImage : public UIBase {
public:
	UIImage(boost::shared_ptr<const std::wstring> filename);
	UIImage(boost::shared_ptr<const Graph> image);
	~UIImage();
	boost::shared_ptr<const Graph> GetImage(void) const;
	bool IsTurn(void) const;
	void SetTurn(bool flag);
	double GetRate(void) const;
	void SetRate(double rate);
	double GetAngle(void) const;
	void SetAngle(bool angle);
	boost::tuple<unsigned int, unsigned int> GetCenter(void) const;
	void SetCenter(unsigned int center_x, unsigned int center_y);
	boost::optional<boost::shared_ptr<Error> > Draw(void);
	boost::optional<boost::shared_ptr<Error> > Draw(unsigned int abs_x, unsigned int abs_y);
	utility::opt_error<unsigned int>::type CalcWidth() const;
	utility::opt_error<unsigned int>::type CalcHeight() const;
protected:
	const boost::shared_ptr<const Graph> image;
	bool turn;
	unsigned char padding[3]; // unused
	double rate;
	double angle;
	unsigned int center_x;
	unsigned int center_y;
};
#pragma warning(pop)
#pragma pack(pop)

} // uis

} // wten
