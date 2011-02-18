#include "stdafx.h"

namespace wten {

using namespace utility;

Action::Action(unsigned int id, TARGET_TYPE target_type, ACTION_TYPE action_type) :
	id(id), target_type(target_type), action_type(action_type)
{
}

Action::~Action() {
}

unsigned int Action::GetId() const {
	return id;
}

Action::TARGET_TYPE Action::GetTargetType() const {
	return target_type;
}

Action::ACTION_TYPE Action::GetActionType() const {
	return action_type;
}

} // action
