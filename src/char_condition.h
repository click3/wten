
namespace wten {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class CharCondition : boost::noncopyable {
public:
	enum CONDITION {
		CONDITION_OK,
		CONDITION_POISON,
		CONDITION_SILENCE,
		CONDITION_SLEEP,
		CONDITION_FEAR,
		CONDITION_PARALYZED,
		CONDITION_STONED,
		CONDITION_DEAD,
		CONDITION_ASHED,
		CONDITION_LOST,
	};
	CharCondition();
	~CharCondition();
	boost::shared_ptr<std::wstring> ToString(void) const;
	CONDITION GetCondition() const;
	bool IsOk() const;
	bool IsSleep() const;
	bool IsFear() const;
	bool IsParalyzed() const;
	bool IsStoned() const;
	bool IsDead() const;
	bool IsAshed() const;
	bool IsLost() const;
	bool SetSleep();
	bool SetFear();
	bool SetParalyze();
	bool SetStone();
	bool SetDead();
	bool SetAshed();
	bool SetLost();
	bool RecoverySleep();
	bool RecoveryFear();
	bool RecoveryParalyze();
	bool RecoveryStone();
	bool RecoveryDead();
	bool RecoveryAshed();
	bool RecoveryLost();
	bool IsPoison() const;
	bool SetPoison();
	bool RecoveryPoison();
	bool IsSilence() const;
	bool SetSilence();
	bool RecoverySilence();
	bool IsAction() const;
	bool IsAlive() const;
	int GetACBonus() const;
	void SetBattleACBonus(int bonus);
	void AddBattleACBonus(int bonus);
	bool ResetBattleACBonus();
	void SetACBonus(int bonus);
	void AddACBonus(int bonus);
	bool ResetACBonus();
	bool IsParry() const;
	void SetParry();
	void TurnEnd();
	void BattleEnd();
	void FloorChange();
	void DungeonOut();
private:
	CONDITION condition;
	int battle_ac_bonus;
	int ac_bonus;
	bool poison;
	bool silence;
	bool parry;
	unsigned char padding; //unused
};
#pragma warning(pop)
#pragma pack(pop)

} // wten
