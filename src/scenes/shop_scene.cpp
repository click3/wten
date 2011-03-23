#include "stdafx.h"

namespace wten { namespace scenes {

using namespace utility;
using namespace boost::assign;

namespace {

enum STEP {
	NORMAL_STEP,
	BUY_LIST_STEP,
	BUY_CHARACTER_SELECT_STEP,
	BUY_CHECK_STEP,
	BUY_ITEM_LIST_MAX_STEP,
	BUY_WANT_MONEY_STEP,
	BUY_COLLECT_MONEY_SELECT_STEP,
	BUY_COLLECT_MONEY_STEP,
	BUY_WANT_ALL_MONEY_STEP,
	BUY_STEP,
	BUY_EQUIPE_SELECT_STEP,
	BUY_EQUIPED_STEP,
	SELL_LIST_STEP,
	SELL_STEP,
	DISENCHANT_STEP,
	CONTRIBUTION_STEP,
	RETURN_STEP,
};

boost::shared_ptr<std::wstring> GetTitle(void) {
	// TODO
	return boost::shared_ptr<std::wstring>(new std::wstring(L"ベストバル商店街"));
}

unsigned int GetCurrentStep(void) {
	return GlobalData::GetCurrentInstance()->GetCurrentShopStep();
}

void SetCurrentStep(STEP step) {
	GlobalData::GetCurrentInstance()->SetCurrentShopStep(step);
}

void SendNextStepEvent(void) {
	boost::shared_ptr<Event> event(new events::NextStepEvent());
	EventNotify::Send(event);
}

} // anonymous

void ShopScene::Initialize(void) {
	boost::optional<boost::shared_ptr<Error> > error;
	if(error = AddEvent(EVENT_TYPE_NEXT_STEP)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	if(error = AddEvent(EVENT_TYPE_ON_SELECT)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	if(error = AddEvent(EVENT_TYPE_ITEM_BUY)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
	if(error = AddEvent(EVENT_TYPE_ITEM_BUY_CANCEL)) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

ShopScene::ShopScene(boost::shared_ptr<const std::wstring> default_frame_filename) :
	CampScene(default_frame_filename), current_step(GetCurrentStep()), title(GetTitle()), script_window(new windows::ScriptWindow())
{
	BOOST_ASSERT(title);
	BOOST_ASSERT(!title->empty());
	BOOST_ASSERT(script_window);
	BOOST_ASSERT(!next_scene);
	Initialize();
}

ShopScene::ShopScene(boost::shared_ptr<const Graph> default_frame_graph) :
	CampScene(default_frame_graph), current_step(GetCurrentStep()), title(GetTitle()), script_window(new windows::ScriptWindow())
{
	BOOST_ASSERT(title);
	BOOST_ASSERT(!title->empty());
	BOOST_ASSERT(script_window);
	BOOST_ASSERT(!next_scene);
	Initialize();
}

ShopScene::~ShopScene() {
}

boost::optional<boost::shared_ptr<Error> > ShopScene::SceneInitialize(void) {
	OPT_ERROR(CampScene::SceneInitialize());
	next_scene.reset();
	OPT_ERROR(AddWindow(script_window, 0, 0, 0, 0));
	OPT_ERROR(AddBoxUI(uis::UIBase::MOVE_MODE_FREE_FREE, 10, 25, 620, 445));
	OPT_ERROR(AddTextUI(title, uis::UIBase::MOVE_MODE_CENTER_FREE, 262, 9, 116, 32));
	OPT_ERROR(AddPTStatusUI(pt, uis::UIBase::MOVE_MODE_FREE_FREE, 0, 350, DEFAULT_SCREEN_SIZE_X, 130));
	return StepInitialize();
}

boost::optional<boost::shared_ptr<Error> > ShopScene::StepInitialize(void) {
	switch(current_step) {
		case NORMAL_STEP: {
			buy_item.reset();
			buy_character.reset();
			money_collect_flag = false;
			std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > > ui_list;
			const wchar_t *text_list[] = {
				L"購入する",
				L"売却する",
				L"呪いを解く",
				L"寄付する",
				L"外に出る"
			};
			boost::shared_ptr<void> step_list[] = {
				boost::shared_ptr<void>(new STEP(BUY_LIST_STEP)),
				boost::shared_ptr<void>(new STEP(SELL_LIST_STEP)),
				boost::shared_ptr<void>(new STEP(DISENCHANT_STEP)),
				boost::shared_ptr<void>(new STEP(CONTRIBUTION_STEP)),
				boost::shared_ptr<void>(new STEP(RETURN_STEP))
			};
			for(unsigned int i = 0; i < 5; i++) {
				boost::shared_ptr<const std::wstring> text(new std::wstring(text_list[i]));
				boost::shared_ptr<void> step(step_list[i]);
				ui_list.push_back(make_tuple(text, step));
			}
			OPT_ERROR(AddSelectorWindow(ui_list, 1, ui_list.size()-1, 50, 100, 540, 180));
			break;
		}
		case BUY_LIST_STEP: {
			next_step = BUY_CHARACTER_SELECT_STEP;
			boost::shared_ptr<windows::ShopItemListWindow> window(new windows::ShopItemListWindow(default_frame_graph));
			OPT_ERROR(AddWindow(window, 50, 100, 540, 180));
			break;
		}
		case BUY_CHARACTER_SELECT_STEP: {
			BOOST_ASSERT(buy_item);
			next_step = BUY_CHECK_STEP;
			std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > > ui_list;
			BOOST_FOREACH(boost::shared_ptr<CharData> character, pt->GetCharacters()) {
				boost::shared_ptr<const std::wstring> text = character->GetStatus()->GetName();
				boost::shared_ptr<void> step = character;
				ui_list.push_back(boost::make_tuple(text, step));
			}
			ui_list.push_back(boost::make_tuple(WChar2Ptr(L"キャンセル"), boost::shared_ptr<void>()));
			OPT_ERROR(AddSelectorWindow(ui_list, 1, ui_list.size()-1, 50, 100, 540, 180));
			break;
		}
		case BUY_CHECK_STEP: {
			BOOST_ASSERT(buy_character);
			if(buy_character->GetStatus()->GetItemList().size() == 8) {
				next_step = BUY_ITEM_LIST_MAX_STEP;
			} else if(buy_item->GetPrice() > buy_character->GetStatus()->GetTG()) {
				if(money_collect_flag) {
					next_step = BUY_WANT_ALL_MONEY_STEP;
				} else {
					next_step = BUY_WANT_MONEY_STEP;
				}
			} else {
				next_step = BUY_STEP;
			}
			SendNextStepEvent();
			break;
		}
		case BUY_ITEM_LIST_MAX_STEP: {
			next_step = NORMAL_STEP;
			const wchar_t *text_char = L"アイテムを持てません。";
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case BUY_WANT_MONEY_STEP: {
			next_step = BUY_COLLECT_MONEY_SELECT_STEP;
			const wchar_t *text_char = L"TGが足りません。";
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case BUY_COLLECT_MONEY_SELECT_STEP: {
			std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > > ui_list;
			const wchar_t *text_list[] = {
				L"PTメンバーからお金を集める",
				L"キャンセル"
			};
			boost::shared_ptr<void> step_list[] = {
				boost::shared_ptr<void>(new STEP(BUY_COLLECT_MONEY_STEP)),
				boost::shared_ptr<void>(new STEP(NORMAL_STEP))
			};
			for(unsigned int i = 0; i < 2; i++) {
				boost::shared_ptr<const std::wstring> text(new std::wstring(text_list[i]));
				boost::shared_ptr<void> step(step_list[i]);
				ui_list.push_back(make_tuple(text, step));
			}
			OPT_ERROR(AddSelectorWindow(ui_list, 1, ui_list.size()-1, 50, 100, 540, 180));
			break;
		}
		case BUY_COLLECT_MONEY_STEP: {
			next_step = BUY_CHECK_STEP;
			money_collect_flag = true;
			unsigned int tg = 0;
			BOOST_FOREACH(boost::shared_ptr<CharData> character, pt->GetCharacters()) {
				BOOST_ASSERT(UINT_MAX - tg >= character->GetStatus()->GetTG());
				const unsigned int temp_tg = character->GetStatus()->GetTG();
				character->GetStatus()->DecTG(temp_tg);
				tg += temp_tg;
			}
			buy_character->GetStatus()->AddTG(tg);
			SendNextStepEvent();
			break;
		}
		case BUY_WANT_ALL_MONEY_STEP: {
			next_step = NORMAL_STEP;
			const wchar_t *text_char = L"TGが足りません。";
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case BUY_STEP: {
			buy_character->GetStatus()->DecTG(buy_item->GetPrice());
			boost::shared_ptr<Item> item(new Item(buy_item));
			buy_character->GetStatus()->AddItem(item);
			// TODO 在庫減少
			wchar_t text_char[256];
			WSPRINTF(text_char, L"%sは%sを購入しました。", buy_character->GetStatus()->GetName()->c_str(), buy_item->GetName()->c_str());
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			if(buy_item->IsEquipPossible(buy_character->GetStatus()->GetJob())) {
				next_step = BUY_EQUIPE_SELECT_STEP;
			} else {
				next_step = NORMAL_STEP;
			}
			break;
		}
		case BUY_EQUIPE_SELECT_STEP: {
			std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > > ui_list;
			const wchar_t *text_list[] = {
				L"アイテムを装備する",
				L"アイテムを装備しない"
			};
			boost::shared_ptr<void> step_list[] = {
				boost::shared_ptr<void>(new STEP(BUY_EQUIPED_STEP)),
				boost::shared_ptr<void>(new STEP(NORMAL_STEP))
			};
			for(unsigned int i = 0; i < 2; i++) {
				boost::shared_ptr<const std::wstring> text(new std::wstring(text_list[i]));
				boost::shared_ptr<void> step(step_list[i]);
				ui_list.push_back(make_tuple(text, step));
			}
			OPT_ERROR(AddSelectorWindow(ui_list, 1, ui_list.size()-1, 50, 100, 540, 180));
			break;
		}
		case BUY_EQUIPED_STEP:
			// TODO
		case SELL_LIST_STEP:
			// TODO
		case SELL_STEP:
			// TODO
		case DISENCHANT_STEP:
			// TODO
		case CONTRIBUTION_STEP:
			// TODO
		{
			next_step = NORMAL_STEP;
			const wchar_t *text_char = L"現在未実装です。";
			boost::shared_ptr<const std::wstring> text(new std::wstring(text_char));
			OPT_ERROR(AddTextWindow(text));
			break;
		}
		case RETURN_STEP: {
			next_scene.reset(new TownScene(default_frame_graph));
			break;
		}
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > ShopScene::OnEvent(boost::shared_ptr<Event> event) {
	if(event->GetEventType() == EVENT_TYPE_NEXT_STEP) {
		current_step = next_step;
		return StepInitialize();
	}
	switch(current_step) {
		case NORMAL_STEP:
		case BUY_COLLECT_MONEY_SELECT_STEP:
		case BUY_EQUIPE_SELECT_STEP: {
			if(event->GetEventType() == EVENT_TYPE_ON_SELECT) {
				const boost::shared_ptr<events::OnSelectEvent> on_select_event = boost::static_pointer_cast<events::OnSelectEvent>(event);
				next_step = *boost::static_pointer_cast<STEP>(on_select_event->GetUserData());
				SendNextStepEvent();
			} else {
				BOOST_ASSERT(false);
				next_step = NORMAL_STEP;
			}
			break;
		}
		case BUY_LIST_STEP: {
			if(event->GetEventType() == EVENT_TYPE_ITEM_BUY_CANCEL) {
				next_step = NORMAL_STEP;
			} else if(event->GetEventType() == EVENT_TYPE_ITEM_BUY) {
				const boost::shared_ptr<events::ItemBuyEvent> item_buy_event = boost::static_pointer_cast<events::ItemBuyEvent>(event);
				buy_item = item_buy_event->GetItemInfo();
			} else {
				BOOST_ASSERT(false);
				next_step = NORMAL_STEP;
			}
			SendNextStepEvent();
			break;
		}
		case BUY_CHARACTER_SELECT_STEP: {
			if(event->GetEventType() == EVENT_TYPE_ON_SELECT) {
				const boost::shared_ptr<events::OnSelectEvent> on_select_event = boost::static_pointer_cast<events::OnSelectEvent>(event);
				const boost::shared_ptr<void> user_data = on_select_event->GetUserData();
				if(!user_data) {
					next_step = NORMAL_STEP;
				} else {
					buy_character = boost::static_pointer_cast<CharData>(user_data);
				}
			} else {
				BOOST_ASSERT(false);
				next_step = NORMAL_STEP;
			}
			SendNextStepEvent();
			break;
		}
	}
	return boost::none;
}

boost::variant<boost::shared_ptr<Error>, boost::optional<boost::shared_ptr<Scene> >, boost::shared_ptr<SceneExit> > ShopScene::EnterFrame(void) {
	if(next_scene) {
		return next_scene;
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > ShopScene::AddEvent(EVENT_TYPE event_type) {
	BOOST_ASSERT(script_window);
	return script_window->AddEventProc(event_type, boost::bind(&ShopScene::OnEvent, this, _1));
}

} // scenes

} // wten

