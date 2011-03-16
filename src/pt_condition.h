
namespace wten {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class PTCondition : boost::noncopyable {
public:
	PTCondition();
	~PTCondition();
	bool IsLight() const;
	bool AddLight(unsigned int value);
	bool SetLightFull();
	bool DecLight(unsigned int value);
	bool ResetLight();

	bool IsIdentifies() const;
	bool SetIdentifies();
	bool ResetIdentifies();

	bool IsSpellDisable() const;
	bool DisableSpell();
	bool EnableSpell();

	void BattleEnd();
	void FloorChange();
	void DungeonOut();
private:
	unsigned int light;
	bool light_full;
	bool identifies;
	bool spell_disable;
	unsigned char padding; //unused
};
#pragma warning(pop)
#pragma pack(pop)

} // wten
