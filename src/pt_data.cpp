#include "stdafx.h"

namespace wten {

PTData::PTData(boost::shared_ptr<PTCondition> condition, const std::vector<boost::shared_ptr<CharData> >& characters,
	bool dungeon, unsigned int floor, DIRECTION dir, unsigned int x, unsigned int y)
:
	condition(condition), characters(characters), dungeon(dungeon), floor(floor), dir(dir), x(x), y(y)
{
	BOOST_ASSERT(condition);
	BOOST_ASSERT(characters.size() <= 6);
	if(dungeon) {
		BOOST_ASSERT(floor > 0);
		BOOST_ASSERT(x < 20);
		BOOST_ASSERT(y < 20);
	} else {
		BOOST_ASSERT(floor == 0);
		BOOST_ASSERT(x == 0);
		BOOST_ASSERT(y == 0);
	}
	BOOST_FOREACH(boost::shared_ptr<CharData> character, characters) {
		BOOST_ASSERT(character);
		boost::optional<boost::shared_ptr<Error> > error = character->ReloadStatus();
		if(error) {
			error.get()->Abort();
			BOOST_ASSERT(false);
		}
	}
}

PTData::~PTData() {
}

boost::shared_ptr<const PTCondition> PTData::GetCondition(void) const {
	return condition;
}

std::vector<boost::shared_ptr<const CharData> > PTData::GetCharacters(void) const {
	std::vector<boost::shared_ptr<const CharData> > result;
	boost::copy(characters, std::back_inserter(result));
	return result;
}

std::vector<boost::shared_ptr<CharData> >::const_iterator PTData::Begin(void) const {
	return characters.begin();
}

std::vector<boost::shared_ptr<CharData> >::const_iterator PTData::End(void) const {
	return characters.end();
}

boost::shared_ptr<const CharData> PTData::operator[](unsigned int index) const {
	BOOST_ASSERT(index < characters.size());
	return characters[index];
}

boost::shared_ptr<PTCondition> PTData::GetCondition(void) {
	return condition;
}

std::vector<boost::shared_ptr<CharData> > PTData::GetCharacters(void) {
	return characters;
}

std::vector<boost::shared_ptr<CharData> >::iterator PTData::Begin(void) {
	return characters.begin();
}

std::vector<boost::shared_ptr<CharData> >::iterator PTData::End(void) {
	return characters.end();
}

boost::shared_ptr<CharData> PTData::operator[](unsigned int index) {
	BOOST_ASSERT(index < characters.size());
	return characters[index];
}

boost::optional<boost::shared_ptr<Error> > PTData::DungeonStart(unsigned int floor, DIRECTION dir, unsigned int x, unsigned int y) {
	BOOST_ASSERT(!dungeon);
	BOOST_ASSERT(x < 20);
	BOOST_ASSERT(y < 20);
	dungeon = true;
	floor = floor;
	dir = dir;
	this->x = x;
	this->y = y;
	BOOST_FOREACH(boost::shared_ptr<CharData> character, characters) {
		OPT_ERROR(character->DungeonStart(floor, x, y));
	}
	// TODO 色々
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > PTData::DungeonEnd(void) {
	BOOST_ASSERT(dungeon);
	BOOST_FOREACH(boost::shared_ptr<CharData> character, characters) {
		OPT_ERROR(character->DungeonEnd());
	}
	dungeon = false;
	floor = 0;
	x = 0;
	y = 0;
	// TODO 色々
	return boost::none;
}

boost::tuple<unsigned int, PTData::DIRECTION, unsigned int, unsigned int> PTData::GetPoint(void) const {
	BOOST_ASSERT(dungeon);
	return boost::make_tuple(floor, dir, x, y);
}

boost::optional<boost::shared_ptr<Error> > PTData::Move(DIRECTION dir, unsigned int x, unsigned int y) {
	BOOST_ASSERT(dungeon);
	BOOST_ASSERT(x < 20);
	BOOST_ASSERT(y < 20);
	BOOST_FOREACH(boost::shared_ptr<CharData> character, characters) {
		OPT_ERROR(character->Move(x, y));
	}
	this->dir = dir;
	this->x = x;
	this->y = y;
	// TODO 色々
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > PTData::Move(DIRECTION dir) {
	BOOST_ASSERT(dungeon);
	BOOST_ASSERT(this->x < 20);
	BOOST_ASSERT(this->y < 20);
	int x = static_cast<int>(this->x);
	int y = static_cast<int>(this->y);
	switch(dir) {
		case DIRECTION_NORTH:
			y++;
			break;
		case DIRECTION_SOUTH:
			y--;
			break;
		case DIRECTION_EAST:
			x++;
			break;
		case DIRECTION_WEST:
			x--;
			break;
	}
	if(x == 20) {
		x = 0;
	}
	if(x == -1) {
		x = 19;
	}
	if(y == 20) {
		y = 0;
	}
	if(y == -1) {
		y = 19;
	}
	// TODO 移動可否判定
	BOOST_FOREACH(boost::shared_ptr<CharData> character, characters) {
		OPT_ERROR(character->Move(static_cast<unsigned int>(x), static_cast<unsigned int>(y)));
	}
	this->x = static_cast<unsigned int>(x);
	this->y = static_cast<unsigned int>(y);
	// TODO 色々
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > PTData::MoveToFront(void) {
	return Move(dir);
}

boost::optional<boost::shared_ptr<Error> > PTData::MoveToBack(void) {
	DIRECTION dir;
	switch(this->dir) {
		case DIRECTION_NORTH:
			dir = DIRECTION_SOUTH;
			break;
		case DIRECTION_SOUTH:
			dir = DIRECTION_NORTH;
			break;
		case DIRECTION_EAST:
			dir = DIRECTION_WEST;
			break;
		case DIRECTION_WEST:
			dir = DIRECTION_EAST;
			break;
		default:
			BOOST_ASSERT(false);
			return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return Move(dir);
}

boost::optional<boost::shared_ptr<Error> > PTData::MoveToLeft(void) {
	DIRECTION dir;
	switch(this->dir) {
		case DIRECTION_NORTH:
			dir = DIRECTION_WEST;
			break;
		case DIRECTION_SOUTH:
			dir = DIRECTION_EAST;
			break;
		case DIRECTION_EAST:
			dir = DIRECTION_NORTH;
			break;
		case DIRECTION_WEST:
			dir = DIRECTION_SOUTH;
			break;
		default:
			BOOST_ASSERT(false);
			return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return Move(dir);
}

boost::optional<boost::shared_ptr<Error> > PTData::MoveToRight(void) {
	DIRECTION dir;
	switch(this->dir) {
		case DIRECTION_NORTH:
			dir = DIRECTION_EAST;
			break;
		case DIRECTION_SOUTH:
			dir = DIRECTION_WEST;
			break;
		case DIRECTION_EAST:
			dir = DIRECTION_SOUTH;
			break;
		case DIRECTION_WEST:
			dir = DIRECTION_NORTH;
			break;
		default:
			BOOST_ASSERT(false);
			return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return Move(dir);
}

boost::optional<boost::shared_ptr<Error> > PTData::MoveFloor(unsigned int floor, DIRECTION dir, unsigned int x, unsigned int y) {
	BOOST_ASSERT(dungeon);
	BOOST_ASSERT(floor > 0);
	BOOST_ASSERT(x < 20);
	BOOST_ASSERT(y < 20);
	BOOST_FOREACH(boost::shared_ptr<CharData> character, characters) {
		OPT_ERROR(character->MoveFloor(floor, x, y));
	}
	this->floor = floor;
	this->dir = dir;
	this->x = x;
	this->y = y;
	// TODO 色々
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > PTData::Turn(DIRECTION dir) {
	BOOST_ASSERT(dungeon);
	this->dir = dir;
	// TODO 色々
	return boost::none;
}

} // wten
