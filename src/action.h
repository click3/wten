
namespace wten {

class EnemyData;
class EnemyPTData;
class CharData;
class PTData;

#pragma warning(push)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
class Action : boost::noncopyable {
public:
	enum TARGET_TYPE {
		TARGET_TYPE_THIS,
		TARGET_TYPE_FRIEND_UNIT,
		TARGET_TYPE_FRIEND_FRONT,
		TARGET_TYPE_FRIEND_BACK,
		TARGET_TYPE_FRIEND_ALL,
		TARGET_TYPE_FRIEND_NO_SELECT,
		TARGET_TYPE_ENEMY_UNIT,
		TARGET_TYPE_ENEMY_AREA,
		TARGET_TYPE_ENEMY_FRONT,
		TARGET_TYPE_ENEMY_BACK,
		TARGET_TYPE_ENEMY_ALL,
		TARGET_TYPE_ENEMY_NO_SELECT,
	};
	enum ACTION_TYPE {
		ACTION_TYPE_NORMAL,
		ACTION_TYPE_FIRE,
		ACTION_TYPE_ICE,
		ACTION_TYPE_POISON,
		ACTION_TYPE_DRAIN,
		ACTION_TYPE_STONE,
		ACTION_TYPE_SPELL,
		ACTION_TYPE_SPECIAL,
	};
	Action(unsigned int id, TARGET_TYPE target_type, ACTION_TYPE action_type);
	virtual ~Action();
	unsigned int GetId() const;
	TARGET_TYPE GetTargetType() const;
	ACTION_TYPE GetActionType() const;
	virtual boost::optional<boost::shared_ptr<Error> > EnemyAction(boost::shared_ptr<EnemyData> enemy, boost::shared_ptr<PTData> pt, unsigned int target_index) const = 0;
	virtual boost::optional<boost::shared_ptr<Error> > CharAction(boost::shared_ptr<CharData> character, boost::shared_ptr<EnemyPTData> pt, unsigned int target_index) const = 0;
private:
	unsigned int id;
	TARGET_TYPE target_type;
	ACTION_TYPE action_type;
};
#pragma warning(pop)

} // wten
