#include "stdafx.h"

namespace wten {

namespace {

unsigned int GetCurrentSystemTime(void) {
	time_t current;
	BOOST_ASSERT(time(&current) != -1);
	return static_cast<unsigned int>(current);
}

boost::shared_ptr<PlayTime> this_ptr;

} // anonymous

PlayTime::PlayTime() :
	start_time(GetCurrentSystemTime())
{
}

PlayTime::~PlayTime() {
}

//static
boost::shared_ptr<PlayTime> PlayTime::GetCurrentInstance(void) {
	if(!this_ptr) {
		this_ptr.reset(new PlayTime());
	}
	return this_ptr;
}

void PlayTime::ResetPlayTime(void) {
	start_time = GetCurrentSystemTime();
}

unsigned int PlayTime::GetCurrentPlayTime(void) const {
	return GlobalData::GetCurrentInstance()->GetPlayTime() + GetCurrentSystemTime() - start_time;
}

boost::shared_ptr<std::string> PlayTime::GetCurrentPlayTimeString(void) const {
	const unsigned int current_time = GetCurrentPlayTime();
	const unsigned int hour = current_time / 60 / 60;
	const unsigned int min = (current_time / 60) % 60;
	const unsigned int sec = current_time % 60;
	char text_char[256];
	sprintf(text_char, "%d:%02d:%02d", hour, min, sec);
	return boost::shared_ptr<std::string>(new std::string(text_char));
}

} // wten

