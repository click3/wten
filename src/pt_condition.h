
namespace wten {

class PTCondition {
public:
	PTCondition();
	~PTCondition();
	bool IsLight();
	bool AddLight(unsigned int value);
	bool SetLightFull();
	bool DecLight(unsigned int value);
	bool ResetLight();

	bool IsIdentifies();
	bool SetIdentifies();
	bool ResetIdentifies();

	bool IsSpellDisable();
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

} // wten
