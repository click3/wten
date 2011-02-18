
namespace wten {

class EnemyCondition {
public:
	EnemyCondition();
	~EnemyCondition();

	enum CONDITION {
		CONDITION_OK,
		CONDITION_SLEEP,
		CONDITION_DEAD,
	};
	CONDITION GetCondition();
	bool IsOk();
	bool IsSleep();
	bool IsDead();
	bool SetSleep();
	bool SetDead();
	bool RecoverySleep();
	bool RecoveryDead();
	bool IsPoison();
	bool SetPoison();
	bool RecoveryPoison();
	bool IsSilence();
	bool SetSilence();
	bool RecoverySilence();
	bool IsAction();
	bool IsAlive();
	int GetACBonus();
	void SetACBonus(int bonus);
	void AddACBonus(int bonus);
	bool ResetACBonus();
	bool IsParry();
	void SetParry();
	void TurnEnd();
private:
	CONDITION condition;
	bool silence;
	bool poison;
	int ac_bonus;
	bool parry;
};

} // wten

