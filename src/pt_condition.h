
namespace wten {

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
	bool light_full;
	unsigned int light;
	bool identifies;
	bool spell_disable;
};
#pragma warning(pop)

} // wten
