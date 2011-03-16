
namespace wten {

#pragma pack(push, 4)
#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class EnemyCondition : boost::noncopyable {
public:
	EnemyCondition();
	~EnemyCondition();

	enum CONDITION {
		CONDITION_OK,
		CONDITION_SLEEP,
		CONDITION_DEAD,
	};
	CONDITION GetCondition() const;
	bool IsOk() const;
	bool IsSleep() const;
	bool IsDead() const;
	bool SetSleep();
	bool SetDead();
	bool RecoverySleep();
	bool RecoveryDead();
	bool IsPoison() const;
	bool SetPoison();
	bool RecoveryPoison();
	bool IsSilence() const;
	bool SetSilence();
	bool RecoverySilence();
	bool IsAction() const;
	bool IsAlive() const;
	int GetACBonus() const;
	void SetACBonus(int bonus);
	void AddACBonus(int bonus);
	bool ResetACBonus();
	bool IsParry() const;
	void SetParry();
	void TurnEnd();
private:
	CONDITION condition;
	int ac_bonus;
	bool silence;
	bool poison;
	bool parry;
	unsigned char padding; //unused
};
#pragma warning(pop)
#pragma pack(pop)

} // wten

