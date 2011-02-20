#include "stdafx.h"
#include <stdio.h>


namespace wten { namespace scenes {

using namespace utility;
using namespace boost::assign;

namespace {

boost::optional<boost::shared_ptr<Error> > AddUI(boost::shared_ptr<windows::WindowBase> window, boost::shared_ptr<const std::string> filename, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(!filename || filename->empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<Graph> src(new Graph(filename));
	boost::shared_ptr<uis::UIBase> ui(new uis::UIBox(src));
	if(!ui) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	ui->SetMoveMode(move_mode);

	OPT_ERROR(window->AddUI(ui));
	OPT_ERROR(ui->Move(x, y));
	OPT_ERROR(ui->Resize(width, height));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > AddTextUI(const boost::shared_ptr<windows::WindowBase> window, boost::shared_ptr<const std::string> filename, boost::shared_ptr<const std::string> text, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(!filename || filename->empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<uis::UIBase> ui(new uis::UIStringBox(filename, text));
	if(!ui) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	ui->SetMoveMode(move_mode);

	OPT_ERROR(window->AddUI(ui));
	OPT_ERROR(ui->Move(x, y));
	OPT_ERROR(ui->Resize(width, height));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > AddSelectorWindow(const boost::shared_ptr<WindowManager> manager, const boost::shared_ptr<std::string>& filename, const std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > >& select_list, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!manager) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(!filename || filename->empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<windows::SelectWindow> window(new windows::SelectWindow(select_list, filename));
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	OPT_ERROR(manager->PushWindow(window));
	OPT_ERROR(window->Move(x, y));
	OPT_ERROR(window->Resize(width, height));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > AddPTStatusUI(boost::shared_ptr<windows::WindowBase> window, boost::shared_ptr<const std::string> filename, boost::shared_ptr<const PTData> pt_data, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(!filename || filename->empty()) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	boost::shared_ptr<uis::UIBase> ui(new uis::UIPTStatus(filename, pt_data));
	if(!ui) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	ui->SetMoveMode(move_mode);

	OPT_ERROR(window->AddUI(ui));
	OPT_ERROR(ui->Move(x, y));
	OPT_ERROR(ui->Resize(width, height));
	return boost::none;
}

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
	boost::shared_ptr<CharStatus> char_status(new CharStatus(name, job, lv, hp, str, iq, pie, vit, agi, luk, tg, exp, item_list, spell_list));
	boost::shared_ptr<CharCondition> char_condition(new CharCondition());
	boost::shared_ptr<CharData> character(new CharData(char_status, char_condition));
	return character;
}

boost::shared_ptr<PTData> CreateDummyPT() {
	std::vector<boost::shared_ptr<CharData> > characters;
	characters += CreateDummyCharData("���v");
	characters += CreateDummyCharData("���Ȃ��v");
	characters += CreateDummyCharData("��{����");
	characters += CreateDummyCharData("����");
	characters += CreateDummyCharData("���΂�悢");
	characters += CreateDummyCharData("�R�N���R");
	boost::shared_ptr<PTCondition> pt_condition(new PTCondition());
	boost::shared_ptr<PTData> pt(new PTData(pt_condition, characters, false));
	return pt;
}

} // anonymous

DebugScene::DebugScene(void) {
}

boost::optional<boost::shared_ptr<Error> > DebugScene::DoStart(void) {
	OPT_ERROR(SceneBase::DoStart());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > DebugScene::SceneInitialize(void) {
	if(!window_manager) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	boost::shared_ptr<windows::WindowBase> window(new windows::WindowBase());
	if(!window) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	OPT_ERROR(window_manager->PushWindow(window));
	OPT_ERROR(window->Resize(640, 480));

	boost::shared_ptr<std::string> box(new std::string("data/ui/box1.png"));
	OPT_ERROR(AddUI(window, box, uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445));
	OPT_ERROR(AddTextUI(window, box, boost::shared_ptr<std::string>(new std::string("��s�s�s�u�W�[�N�t�����g�v")), uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	std::vector<boost::tuple<boost::shared_ptr<const std::string>, boost::shared_ptr<void> > > select_list;
#define ADD_SELECT(text) select_list.push_back(boost::make_tuple<boost::shared_ptr<std::string>, boost::shared_ptr<void> >(boost::shared_ptr<std::string>(new std::string(text)), boost::shared_ptr<void>()))
	ADD_SELECT("�h���u���[�[�����C�f���v");
	ADD_SELECT("�x�X�g�o�����X�X");
	ADD_SELECT("�g�[�g���@");
	ADD_SELECT("����u���Z�M�v");
	ADD_SELECT("�W�[�N�t�����g�R�m�c����");
	ADD_SELECT("�V���̓��@�t��");
#undef ADD_SELECT
	OPT_ERROR(AddSelectorWindow(window_manager, box, select_list, 50, 100, 540, 150));

	//OPT_ERROR(AddUI(window, box, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 320, 640, 160));
	OPT_ERROR(AddPTStatusUI(window, box, CreateDummyPT(), uis::UIBase::MOVE_MODE_FREE_FREE, 0, 350, 640, 130));
	return boost::none;
}

} // scenes

} // wten

