
namespace wten {

namespace events {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class TairetsuSelectedEvent : public EventBase {
public:
	TairetsuSelectedEvent(const std::vector<boost::shared_ptr<CharData> > &char_list);
	~TairetsuSelectedEvent();
	std::vector<boost::shared_ptr<CharData> > GetCharList(void) const;
private:
	const std::vector<boost::shared_ptr<CharData> > char_list;
};
#pragma warning(pop)
#pragma pack(pop)

} // events

} // wten
