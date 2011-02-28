#include "stdafx.h"

using namespace wten;
using namespace boost::assign;

namespace {

boost::shared_ptr<const Job> CreateDummyJob() {
	static unsigned int id = 1;
	boost::shared_ptr<const std::string> name(new std::string("DUMMY"));
	unsigned int hp_base = 10, hp_count_bonus = 0, str = 10, iq = 10, pie = 10, vit = 10, agi = 10, luk = 10, thief_skill = 0;
	std::vector<boost::tuple<unsigned int, boost::shared_ptr<const actions::SpellBase> > > spells;
	std::vector<unsigned int> exp_list;
	exp_list += 0,10,100;
	boost::shared_ptr<const Job> job(new Job(id, name, hp_base, hp_count_bonus, str, iq, pie, vit, agi, luk, thief_skill, spells, exp_list));
	id++;
	return job;
}

boost::shared_ptr<CharData> CreateDummyCharData(const char *char_name) {
	boost::shared_ptr<const Job> job = CreateDummyJob();
	boost::shared_ptr<const std::string> name(new std::string(char_name));
	unsigned int lv = 1;
	unsigned int hp = job->CalcMaxHP(lv, 1);
	unsigned int str,iq,pie,vit,agi,luk,tg,exp;
	str = iq = pie = vit = agi = luk = tg = exp = 0;
	std::vector<boost::shared_ptr<Item> > item_list;
	std::vector<boost::tuple<boost::shared_ptr<const Job>, boost::shared_ptr<const actions::SpellBase> > > spell_list;
	boost::shared_ptr<CharStatus> char_status(new CharStatus(name, job, CharStatus::ALIGNMENT_GOOD, lv, hp, str, iq, pie, vit, agi, luk, tg, exp, item_list, spell_list));
	boost::shared_ptr<CharCondition> char_condition(new CharCondition());
	boost::shared_ptr<CharData> character(new CharData(char_status, char_condition, false));
	return character;
}

boost::shared_ptr<PTData> CreateDummyPT() {
	std::vector<boost::shared_ptr<CharData> > characters;
	characters += CreateDummyCharData("やる夫");
	characters += CreateDummyCharData("やらない夫");
	characters += CreateDummyCharData("坂本美緒");
	characters += CreateDummyCharData("黒沢");
	characters += CreateDummyCharData("高槻やよい");
	characters += CreateDummyCharData("コクリコ");
	boost::shared_ptr<PTCondition> pt_condition(new PTCondition());
	boost::shared_ptr<PTData> pt(new PTData(pt_condition, characters, false));
	return pt;
}

} // anonymous

//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ){
int main() {
	::setlocale(LC_ALL, _T(""));

	boost::shared_ptr<WTen> game;/*
	{
		boost::shared_ptr<Scene> scene(new scenes::DebugScene());
		game.reset(new WTen(scene));
	}*/
	{
		boost::shared_ptr<Scene> scene(new scenes::OpeningScene());
		game.reset(new WTen(scene));
	}
	boost::shared_ptr<PTData> pt = CreateDummyPT();
	PTList::GetCurrentInstance()->AddPT(pt);
	boost::optional<boost::shared_ptr<Error> > result = game->DoStart(pt);
	game.reset();
	if(result) {
		result.get()->Abort();
		return 1;
	}

	return 0;
}

