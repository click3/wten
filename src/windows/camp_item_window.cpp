#include "stdafx.h"

namespace wten { namespace windows {

using namespace utility;
using namespace boost::assign;

namespace {

boost::shared_ptr<SelectWindow> CreateCharSelectWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const Graph> default_frame_graph) {
	BOOST_ASSERT(pt->GetCharacters().size() > 0);
	std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > > text_list;
	BOOST_FOREACH(boost::shared_ptr<CharData> char_data, pt->GetCharacters()) {
		boost::shared_ptr<const std::wstring> text = char_data->GetStatus()->GetName();
		boost::shared_ptr<void> user_data = char_data;
		text_list += boost::make_tuple(text, user_data);
	}
	boost::shared_ptr<SelectWindow> result(new SelectWindow(text_list, 1, default_frame_graph));
	result->SetSelectClose(false);
	BOOST_ASSERT(!result->Move(50, 50));
	BOOST_ASSERT(!result->Resize());
	return result;
}

boost::shared_ptr<uis::UIStringBox> CreateItemDescriptionUI(boost::shared_ptr<CharData> selected_char, boost::shared_ptr<const Graph> default_frame_graph) {
	BOOST_ASSERT(selected_char->GetStatus()->GetItemList().size() > 0);
	boost::shared_ptr<const std::wstring> text;
	{
		boost::optional<boost::shared_ptr<const std::wstring> > text_opt = selected_char->GetStatus()->GetItemList()[0]->GetDescription();
		if(text_opt) {
			text = boost::get<boost::shared_ptr<const std::wstring> >(text);
		} else {
			text = boost::shared_ptr<const std::wstring>(new std::wstring(L""));
		}
	}

	boost::shared_ptr<uis::UIStringBox> result(new uis::UIStringBox(default_frame_graph, text));
	BOOST_ASSERT(!result->Move(0, 350));
	BOOST_ASSERT(!result->Resize(640, 130));
	return result;
}

boost::shared_ptr<SelectWindow> CreateItemSelectWindow(boost::shared_ptr<CharData> selected_char, boost::shared_ptr<const Graph> default_frame_graph) {
	BOOST_ASSERT(selected_char->GetStatus()->GetItemList().size() > 0);
	std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > > text_list;
	BOOST_FOREACH(boost::shared_ptr<Item> item, selected_char->GetStatus()->GetItemList()) {
		boost::shared_ptr<const std::wstring> text = item->GetName();
		boost::shared_ptr<void> user_data = item;
		text_list += boost::make_tuple(text, user_data);
	}
	boost::shared_ptr<SelectWindow> result(new SelectWindow(text_list, 1, default_frame_graph));
	result->SetSelectClose(false);
	BOOST_ASSERT(!result->Move(75, 75));
	BOOST_ASSERT(!result->Resize());
	return result;
}

std::vector<CampItemWindow::COMMAND> CreateCommandList(boost::shared_ptr<Item> selected_item) {
	std::vector<CampItemWindow::COMMAND> command_list;
	switch(selected_item->GetItemType()) {
		case ItemInfo::ITEM_TYPE_WEAPON:
		case ItemInfo::ITEM_TYPE_SHIELD:
		case ItemInfo::ITEM_TYPE_ARMOR:
		case ItemInfo::ITEM_TYPE_HELMET:
		case ItemInfo::ITEM_TYPE_GAUNTLET:
		case ItemInfo::ITEM_TYPE_ADORNMENT: {
			switch(selected_item->GetCondition()) {
				case Item::CONDITION_UNCERTAIN:
				case Item::CONDITION_UNCERTAIN_CURSE:
				case Item::CONDITION_NORMAL:
				case Item::CONDITION_CURSE: {
					command_list += CampItemWindow::COMMAND_MOVE, CampItemWindow::COMMAND_USE, CampItemWindow::COMMAND_EQUIP, CampItemWindow::COMMAND_DELETE;
					break;
				}
				case Item::CONDITION_UNCERTAIN_EQUIP:
				case Item::CONDITION_EQUIP: {
					command_list += CampItemWindow::COMMAND_MOVE, CampItemWindow::COMMAND_USE, CampItemWindow::COMMAND_EQUIP_RELEASE, CampItemWindow::COMMAND_DELETE;
					break;
				}
				case Item::CONDITION_UNCERTAIN_EQUIP_CURSE:
				case Item::CONDITION_UNCERTAIN_ADHESION_CURSE:
				case Item::CONDITION_EQUIP_CURSE: {
					command_list += CampItemWindow::COMMAND_USE;
					break;
				}
				case Item::CONDITION_UNCERTAIN_BROKEN:
				case Item::CONDITION_BROKEN: {
					command_list += CampItemWindow::COMMAND_MOVE, CampItemWindow::COMMAND_DELETE;
					break;
				}
				default:
					BOOST_ASSERT(false);
					return std::vector<CampItemWindow::COMMAND>();
			}
			break;
		}
		case ItemInfo::ITEM_TYPE_TOOL: {
			switch(selected_item->GetCondition()) {
				case Item::CONDITION_UNCERTAIN:
				case Item::CONDITION_NORMAL: {
					command_list += CampItemWindow::COMMAND_MOVE, CampItemWindow::COMMAND_USE, CampItemWindow::COMMAND_DELETE;
					break;
				}
				case Item::CONDITION_UNCERTAIN_BROKEN:
				case Item::CONDITION_BROKEN: {
					command_list += CampItemWindow::COMMAND_MOVE, CampItemWindow::COMMAND_DELETE;
					break;
				}
				default:
					BOOST_ASSERT(false);
					return std::vector<CampItemWindow::COMMAND>();
			}
			break;
		}
	}
	return command_list;
}

const wchar_t *COMMANDToString(CampItemWindow::COMMAND command) {
	switch(command) {
		case CampItemWindow::COMMAND_MOVE:
			return L"渡す";
		case CampItemWindow::COMMAND_USE:
			return L"使う";
		case CampItemWindow::COMMAND_EQUIP:
			return L"装備する";
		case CampItemWindow::COMMAND_EQUIP_RELEASE:
			return L"装備を外す";
		case CampItemWindow::COMMAND_DELETE:
			return L"捨てる";
		default:
			BOOST_ASSERT(false);
	}
	return L"Unknown";
}

boost::shared_ptr<SelectWindow> CreateCommandSelectWindow(boost::shared_ptr<Item> selected_item, boost::shared_ptr<const Graph> default_frame_graph) {
	std::vector<CampItemWindow::COMMAND> command_list = CreateCommandList(selected_item);
	std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > > text_list;
	BOOST_FOREACH(CampItemWindow::COMMAND command, command_list) {
		boost::shared_ptr<const std::wstring> text = boost::shared_ptr<const std::wstring>(new std::wstring(COMMANDToString(command)));
		boost::shared_ptr<void> user_data = boost::shared_ptr<CampItemWindow::COMMAND>(new CampItemWindow::COMMAND(command));
		text_list += boost::make_tuple(text, user_data);
	}
	boost::shared_ptr<SelectWindow> result(new SelectWindow(text_list, 1, default_frame_graph));
	result->SetSelectClose(false);
	BOOST_ASSERT(!result->Move(100, 100));
	BOOST_ASSERT(!result->Resize());
	return result;
}

boost::shared_ptr<SelectWindow> CreateTargetSelectWindow(boost::shared_ptr<PTData>pt, boost::shared_ptr<Item> selected_item, boost::shared_ptr<CampItemWindow::COMMAND>selected_command, boost::shared_ptr<const Graph> default_frame_graph) {
	BOOST_ASSERT(pt->GetCharacters().size() > 0);
	std::vector<boost::tuple<boost::shared_ptr<const std::wstring>, boost::shared_ptr<void> > > text_list;
	BOOST_FOREACH(boost::shared_ptr<CharData> char_data, pt->GetCharacters()) {
		boost::shared_ptr<const std::wstring> text = char_data->GetStatus()->GetName();
		boost::shared_ptr<void> user_data = char_data;
		text_list += boost::make_tuple(text, user_data);
	}
	boost::shared_ptr<SelectWindow> result(new SelectWindow(text_list, 1, default_frame_graph));
	result->SetSelectClose(false);
	BOOST_ASSERT(!result->Move(125, 125));
	BOOST_ASSERT(!result->Resize());
	return result;
}

} // anonymous

CampItemWindow::CampItemWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const std::wstring> default_frame_filename) :
	CampBaseWindow(pt, default_frame_filename), state(STATE_INITIALIZE)
{
	BOOST_ASSERT(pt);
	BOOST_ASSERT(default_frame_filename);
	BOOST_ASSERT(!default_frame_filename->empty());
	BOOST_ASSERT(!char_select_window);
	BOOST_ASSERT(!selected_char);
	BOOST_ASSERT(!item_select_window);
	BOOST_ASSERT(!item_description_ui);
	BOOST_ASSERT(!selected_item);
	BOOST_ASSERT(!item_command_select_window);
	BOOST_ASSERT(!selected_command);
	BOOST_ASSERT(!item_target_select_window);
	BOOST_ASSERT(!target_char);
	BOOST_ASSERT(!error_message);
}

CampItemWindow::CampItemWindow(boost::shared_ptr<PTData> pt, boost::shared_ptr<const Graph> default_frame_graph) :
	CampBaseWindow(pt, default_frame_graph), state(STATE_INITIALIZE)
{
	BOOST_ASSERT(pt);
	BOOST_ASSERT(default_frame_graph);
	BOOST_ASSERT(!char_select_window);
	BOOST_ASSERT(!selected_char);
	BOOST_ASSERT(!item_select_window);
	BOOST_ASSERT(!item_description_ui);
	BOOST_ASSERT(!selected_item);
	BOOST_ASSERT(!item_command_select_window);
	BOOST_ASSERT(!selected_command);
	BOOST_ASSERT(!item_target_select_window);
	BOOST_ASSERT(!target_char);
	BOOST_ASSERT(!error_message);
}

CampItemWindow::~CampItemWindow() {
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::WindowInitialize(void) {
	OPT_ERROR(CampBaseWindow::WindowInitialize());
	OPT_ERROR(StateToCharSelect());
	return boost::none;
}

utility::opt_error<boost::optional<boost::shared_ptr<Event> > >::type CampItemWindow::NotifyEvent(boost::shared_ptr<Event> event) {
	if(event->GetEventType() == EVENT_TYPE_KEY) {
		OPT_ERROR(OnKeyEvent(event));
		return boost::none;
	}
	if(event->GetEventType() == EVENT_TYPE_ON_SELECT) {
		OPT_ERROR(OnSelectEvent(event));
		return boost::none;
	}
	if(event->GetEventType() == EVENT_TYPE_NEXT_STEP) {
		OPT_ERROR(OnNextStepEvent(event));
		return boost::none;
	}
	return CampBaseWindow::NotifyEvent(event);
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::OnKeyEvent(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(event->GetEventType() == EVENT_TYPE_KEY);
	boost::shared_ptr<events::KeyEvent> key_event = boost::static_pointer_cast<events::KeyEvent>(event);
	if(key_event->GetAction() == events::KeyEvent::KEY_PRESS) {
		switch(key_event->GetKey()) {
			case events::KeyEvent::KEY_B:
				if(!error_message) {
					OPT_ERROR(StateBack());
				}
				break;
			default:
				break;
		}
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::OnSelectEvent(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(event->GetEventType() == EVENT_TYPE_ON_SELECT);
	boost::shared_ptr<events::OnSelectEvent> on_select_event = boost::static_pointer_cast<events::OnSelectEvent>(event);
	switch(state) {
		case STATE_CHAR_SELECT:
			OPT_ERROR(StateToItemSelect(on_select_event->GetUserData()));
			break;
		case STATE_ITEM_SELECT:
			OPT_ERROR(StateToCommandSelect(on_select_event->GetUserData()));
			break;
		case STATE_COMMAND_SELECT:
			OPT_ERROR(StateToTargetSelect(on_select_event->GetUserData()));
			break;
		case STATE_TARGET_SELECT:
			OPT_ERROR(StateToApply(on_select_event->GetUserData()));
			break;
		default:
			BOOST_ASSERT(false);
			return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::OnNextStepEvent(boost::shared_ptr<Event> event) {
	BOOST_ASSERT(event->GetEventType() == EVENT_TYPE_NEXT_STEP);
	boost::shared_ptr<events::NextStepEvent> next_step_event = boost::static_pointer_cast<events::NextStepEvent>(event);
	switch(state) {
		case STATE_CHAR_SELECT:
			error_message.reset();
			OPT_ERROR(RemoveThisWindow());
			break;
		case STATE_ITEM_SELECT:
			error_message.reset();
			selected_char.reset();
			state = STATE_CHAR_SELECT;
			break;
		default:
			BOOST_ASSERT(false);
			return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::StateBack(void) {
	switch(state) {
		case STATE_CHAR_SELECT:
			SendPopWindowEvent(char_select_window);
			char_select_window.reset();
			OPT_ERROR(RemoveThisWindow());
			state = STATE_INITIALIZE;
			break;
		case STATE_ITEM_SELECT:
			{
				bool is_remove;
				OPT_BOOL(is_remove, RemoveUI(item_description_ui));
				if(!is_remove) {
					return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
				}
			}
			item_description_ui.reset();
			SendPopWindowEvent(item_select_window);
			item_select_window.reset();
			selected_char.reset();
			state = STATE_CHAR_SELECT;
			break;
		case STATE_COMMAND_SELECT:
			SendPopWindowEvent(item_command_select_window);
			item_command_select_window.reset();
			selected_item.reset();
			state = STATE_ITEM_SELECT;
			break;
		case STATE_TARGET_SELECT:
			SendPopWindowEvent(item_target_select_window);
			item_target_select_window.reset();
			selected_command.reset();
			state = STATE_COMMAND_SELECT;
			break;
		case STATE_APPLY:
			target_char.reset();
			state = STATE_TARGET_SELECT;
			break;
		default:
			BOOST_ASSERT(false);
			return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::StateToCharSelect(void) {
	BOOST_ASSERT(state == STATE_INITIALIZE);

	if(pt->GetCharacters().size() > 0) {
		char_select_window = CreateCharSelectWindow(pt, default_frame_graph);
		BOOST_ASSERT(char_select_window);

		SendNextWindowEvent(char_select_window);
	} else {
		const wchar_t *text = L"PTに所属しているキャラクターが居ません";
		error_message.reset(new std::wstring(text));
		OPT_ERROR(SendNextTextWindowEvent(error_message));
	}

	state = STATE_CHAR_SELECT;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::StateToItemSelect(boost::shared_ptr<void> data) {
	BOOST_ASSERT(state == STATE_CHAR_SELECT);
	selected_char = boost::static_pointer_cast<CharData>(data);
	BOOST_ASSERT(selected_char);

	if(selected_char->GetStatus()->GetItemList().size() > 0) {
		item_description_ui = CreateItemDescriptionUI(selected_char, default_frame_graph);
		BOOST_ASSERT(item_description_ui);
		item_select_window = CreateItemSelectWindow(selected_char, default_frame_graph);
		BOOST_ASSERT(item_select_window);

		OPT_ERROR(AddUI(item_description_ui));
		SendNextWindowEvent(item_select_window);
	} else {
		const wchar_t *text = L"そのキャラクターはアイテムを所持していません";
		error_message.reset(new std::wstring(text));
		OPT_ERROR(SendNextTextWindowEvent(error_message));
	}

	state = STATE_ITEM_SELECT;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::StateToCommandSelect(boost::shared_ptr<void> data) {
	BOOST_ASSERT(state == STATE_ITEM_SELECT);
	selected_item = boost::static_pointer_cast<Item>(data);
	BOOST_ASSERT(selected_item);

	item_command_select_window = CreateCommandSelectWindow(selected_item, default_frame_graph);
	BOOST_ASSERT(item_command_select_window);

	SendNextWindowEvent(item_command_select_window);
	state = STATE_COMMAND_SELECT;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::StateToTargetSelect(boost::shared_ptr<void> data) {
	BOOST_ASSERT(state == STATE_COMMAND_SELECT);
	selected_command = boost::static_pointer_cast<COMMAND>(data);
	BOOST_ASSERT(selected_command);

	item_target_select_window = CreateTargetSelectWindow(pt, selected_item, selected_command, default_frame_graph);
	BOOST_ASSERT(item_target_select_window);

	SendNextWindowEvent(item_target_select_window);
	state = STATE_TARGET_SELECT;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::StateToApply(boost::shared_ptr<void> data) {
	BOOST_ASSERT(state == STATE_TARGET_SELECT);
	target_char = boost::static_pointer_cast<CharData>(data);
	BOOST_ASSERT(target_char);
	state = STATE_APPLY;

	switch(*selected_command) {
		case COMMAND_MOVE:
			OPT_ERROR(CommandMove());
			break;
		case COMMAND_USE:
			OPT_ERROR(CommandUse());
			break;
		case COMMAND_EQUIP:
			OPT_ERROR(CommandEquip());
			break;
		case COMMAND_EQUIP_RELEASE:
			OPT_ERROR(CommandEquipRelease());
			break;
		case COMMAND_DELETE:
			OPT_ERROR(CommandDelete());
			break;
		default:
			BOOST_ASSERT(false);
			return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}

	StateBack();
	StateBack();
	StateBack();
	StateBack();
	StateBack();

	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::CommandMove(void) {
	// TODO
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::CommandUse(void) {
	// TODO
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::CommandEquip(void) {
	// TODO
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::CommandEquipRelease(void) {
	// TODO
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > CampItemWindow::CommandDelete(void) {
	// TODO
	return boost::none;
}

} // windows

} // wten
