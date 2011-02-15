
namespace wten {

class CharCondition {
public:
	enum Condition {
		CONDITION_OK,
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
	Condition GetCondition();
	bool IsOk();
	bool IsSleep();
	bool IsFear();
	bool IsParalyzed();
	bool IsStoned();
	bool IsDead();
	bool IsAshed();
	bool IsLost();
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
	bool IsPoison();
	bool SetPoison();
	bool RecoveryPoison();
	bool IsSilence();
	bool SetSilence();
	bool RecoverySilence();
	bool IsAction();
	bool IsAlive();
	void BattleEnd();
	void FloorChange();
	void DungeonOut();
private:
	Condition condition;
	bool poison;
	bool silence;
};

} // wten
