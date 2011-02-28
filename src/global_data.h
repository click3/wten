
namespace wten {

class GlobalData : boost::noncopyable {
private:
	GlobalData();
public:
	~GlobalData();
	static boost::shared_ptr<GlobalData> GetCurrentInstance(void);

enum DATA_INDEX {
	DATA_INDEX_GuildName = 0,
	DATA_INDEX_CurrentCastleStep,
	DATA_INDEX_GuildCreate,
	DATA_INDEX_CurrentTowerStep,
	DATA_INDEX_PlayTime,
	DATA_INDEX_CurrentBarStep,
	DATA_INDEX_CurrentGuildStep,

	DATA_INDEX_MAX
};

#define ADD_PROPERTY(name, type, default) 					\
type Get##name(void) const {							\
	if(!data[DATA_INDEX_##name]) {						\
		return default;							\
	}										\
	return *boost::static_pointer_cast<type>(data[DATA_INDEX_##name]);	\
}											\
void Set##name(type value) {							\
	data[DATA_INDEX_##name] = boost::shared_ptr<void>(new type(value));	\
}
#define ADD_PROPERTY_PTR(name, type, default) 					\
boost::shared_ptr<type> Get##name(void) const {					\
	if(!data[DATA_INDEX_##name]) {						\
		return boost::shared_ptr<type>(new type(default));		\
	}										\
	return boost::static_pointer_cast<type>(data[DATA_INDEX_##name]);	\
}											\
void Set##name(boost::shared_ptr<const type> value) {					\
	data[DATA_INDEX_##name] = boost::shared_ptr<void>(new type(*value));	\
}
#define ADD_UINT_PROPERTY(name, default) ADD_PROPERTY(name, unsigned int, default)
#define ADD_BOOL_PROPERTY(name, default) ADD_PROPERTY(name, bool, default)
#define ADD_STRING_PROPERTY(name, default) ADD_PROPERTY_PTR(name, std::string, default)

	ADD_STRING_PROPERTY(GuildName, "")
	ADD_UINT_PROPERTY(CurrentCastleStep, 0)
	ADD_BOOL_PROPERTY(GuildCreate, false)
	ADD_UINT_PROPERTY(CurrentTowerStep, 0)
	ADD_UINT_PROPERTY(PlayTime, 0)
	ADD_UINT_PROPERTY(CurrentBarStep, 0)
	ADD_UINT_PROPERTY(CurrentGuildStep, 0)

#undef ADD_PROPERTY_PTR
#undef ADD_PROPERTY
protected:
	std::vector<boost::shared_ptr<void> > data;
};

} // wten
