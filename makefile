cc  = cl
!if $(RELEASE) == y
	opt = /nologo /errorReport:none /MP8 /Wall /WX /MT  /EHa /Ox /GL /GF /Gy /Fpwten.pch /Zm300
	link_opt = /link /OPT:REF,ICF
!else
	opt = /nologo /errorReport:none /MP8 /Wall /WX /MTd /EHa /Od             /Fpwten.pch /Zm300
	link_opt = /link /OPT:NOREF,NOICF
!endif
obj = DxLib_lib.obj utility.obj global_data.obj play_time.obj graph.obj char_condition.obj pt_condition.obj enemy_condition.obj enemy_info.obj enemy_status.obj action.obj job.obj item_info.obj item.obj spell_base.obj dummy_spell.obj char_status.obj char_data.obj pt_data.obj ui_base.obj ui_box.obj ui_string.obj ui_image.obj ui_selector_base.obj ui_selector.obj ui_string_box.obj ui_queue.obj ui_pager.obj ui_pt_status.obj ui_input_string.obj ui_input_dlg.obj ui_char_status.obj ui_tairetsu.obj ui_dummy.obj event_base.obj key_event.obj on_select_event.obj on_select_change_event.obj pop_window_event.obj next_step_event.obj input_string_event.obj next_window_event.obj item_buy_event.obj item_buy_cancel_event.obj tairetsu_selected_event.obj select_window.obj page_select_window.obj script_window.obj text_window.obj input_dlg_window.obj tairetsu_window.obj opening_window.obj camp_window.obj camp_base_window.obj camp_status_window.obj camp_item_window.obj camp_tairetsu_window.obj shop_item_list_window.obj window_base.obj window_manager.obj event_checker_base.obj key_event_checker.obj event_manager.obj debug_scene.obj error_normal.obj event_notify.obj scene_base.obj scene_selector_scene.obj camp_scene.obj town_scene.obj castle_scene.obj opening_scene.obj title_scene.obj tower_gate_scene.obj bar_scene.obj guild_scene.obj temple_scene.obj shop_scene.obj hotel_scene.obj wten.obj stdafx.obj main.obj character_list.obj pt_list.obj job_list.obj item_info_list.obj spell_list.obj
exe = wten.exe

.c.obj:
	$(cc) /c /Yustdafx.h $(opt) /Tp $<
.cpp.obj:
	$(cc) /c /Yustdafx.h $(opt) /Tp $<
$(exe).exe: $(obj)
	version.exe
	$(cc) $(opt) /Fe$* $** $(lib) $(link_opt)

src/stdafx.h: src/DxLib_lib.h src/global_data.h src/play_time.h src/error.h src/list_csv_parser_base.h src/char_condition.h src/pt_condition.h src/enemy_condition.h src/enemy_info.h src/enemy_status.h src/action.h src/job.h src/job_list.h src/item_info.h src/item_info_list.h src/item.h src/actions/spell_base.h src/actions/dummy_spell.h src/spell_list.h src/char_status.h src/char_data.h src/pt_data.h src/pt_list.h src/character_list.h src/event.h src/events/event_base.h src/events/key_event.h src/events/on_select_event.h src/events/on_select_change_event.h src/events/pop_window_event.h src/events/next_step_event.h src/events/input_string_event.h src/events/next_window_event.h src/events/item_buy_event.h src/events/item_buy_cancel_event.h src/events/tairetsu_selected_event.h src/event_checker.h src/events/event_checker_base.h src/events/key_event_checker.h src/event_manager.h src/graph.h src/ui.h src/utility.h src/window.h src/window_manager.h src/scene.h src/wten.h src/debug_scene.h src/error_normal.h src/event_notify.h src/scenes/scene_base.h src/scenes/scene_selector_scene.h src/scenes/camp_scene.h src/scenes/town_scene.h src/scenes/castle_scene.h src/scenes/opening_scene.h src/scenes/title_scene.h src/scenes/tower_gate_scene.h src/scenes/bar_scene.h src/scenes/guild_scene.h src/scenes/temple_scene.h src/scenes/shop_scene.h src/scenes/hotel_scene.h src/windows/window_base.h src/windows/select_window.h src/windows/page_select_window.h src/windows/script_window.h src/windows/text_window.h src/windows/input_dlg_window.h src/windows/tairetsu_window.h src/windows/opening_window.h src/windows/camp_window.h src/windows/camp_base_window.h src/windows/camp_status_window.h src/windows/camp_item_window.h src/windows/camp_tairetsu_window.h src/windows/shop_item_list_window.h src/uis/ui_base.h src/uis/ui_box.h src/uis/ui_string.h src/uis/ui_image.h src/uis/ui_selector_base.h src/uis/ui_selector.h src/uis/ui_string_box.h src/uis/ui_queue.h src/uis/ui_pager.h src/uis/ui_pt_status.h src/uis/ui_input_string.h src/uis/ui_input_dlg.h src/uis/ui_char_status.h src/uis/ui_tairetsu.h src/uis/ui_dummy.h
	touch src/stdafx.h
stdafx.obj: src/stdafx.h
        $(cc) $(opt) /c /Yc /Tp src/stdafx.cpp

DxLib_lib.obj: src/DxLib_lib.cpp stdafx.obj
utility.obj: src/utility.cpp stdafx.obj
global_data.obj: src/global_data.cpp stdafx.obj
play_time.obj: src/play_time.cpp stdafx.obj
graph.obj: src/graph.cpp stdafx.obj
char_condition.obj: src/char_condition.cpp stdafx.obj
pt_condition.obj: src/pt_condition.cpp stdafx.obj
enemy_condition.obj: src/enemy_condition.cpp stdafx.obj
enemy_info.obj: src/enemy_info.cpp stdafx.obj
enemy_status.obj: src/enemy_status.cpp stdafx.obj
action.obj: src/action.cpp stdafx.obj
job.obj: src/job.cpp stdafx.obj
job_list.obj: src/job_list.cpp stdafx.obj
item_info.obj: src/item_info.cpp stdafx.obj
item_info_list.obj: src/item_info_list.cpp stdafx.obj
item.obj: src/item.cpp stdafx.obj
spell_base.obj: src/actions/spell_base.cpp stdafx.obj
dummy_spell.obj: src/actions/dummy_spell.cpp stdafx.obj
spell_list.obj: src/spell_list.cpp stdafx.obj
char_status.obj: src/char_status.cpp stdafx.obj
char_data.obj: src/char_data.cpp stdafx.obj
pt_data.obj: src/pt_data.cpp stdafx.obj
pt_list.obj: src/pt_list.cpp stdafx.obj
character_list.obj: src/character_list.cpp stdafx.obj
ui_base.obj: src/uis/ui_base.cpp stdafx.obj
ui_box.obj: src/uis/ui_box.cpp stdafx.obj
ui_string.obj: src/uis/ui_string.cpp stdafx.obj
ui_image.obj: src/uis/ui_image.cpp stdafx.obj
ui_selector_base.obj: src/uis/ui_selector_base.cpp stdafx.obj
ui_selector.obj: src/uis/ui_selector.cpp stdafx.obj
ui_string_box.obj: src/uis/ui_string_box.cpp stdafx.obj
ui_queue.obj: src/uis/ui_queue.cpp stdafx.obj
ui_pager.obj: src/uis/ui_pager.cpp stdafx.obj
ui_pt_status.obj: src/uis/ui_pt_status.cpp stdafx.obj
ui_input_string.obj: src/uis/ui_input_string.cpp stdafx.obj
ui_input_dlg.obj: src/uis/ui_input_dlg.cpp stdafx.obj
ui_char_status.obj: src/uis/ui_char_status.cpp stdafx.obj
ui_tairetsu.obj: src/uis/ui_tairetsu.cpp stdafx.obj
ui_dummy.obj: src/uis/ui_dummy.cpp stdafx.obj
event_base.obj: src/events/event_base.cpp stdafx.obj
key_event.obj: src/events/key_event.cpp stdafx.obj
on_select_event.obj: src/events/on_select_event.cpp stdafx.obj
on_select_change_event.obj: src/events/on_select_change_event.cpp stdafx.obj
pop_window_event.obj: src/events/pop_window_event.cpp stdafx.obj
next_step_event.obj: src/events/next_step_event.cpp stdafx.obj
input_string_event.obj: src/events/input_string_event.cpp stdafx.obj
next_window_event.obj: src/events/next_window_event.cpp stdafx.obj
item_buy_event.obj: src/events/item_buy_event.cpp stdafx.obj
item_buy_cancel_event.obj: src/events/item_buy_cancel_event.cpp stdafx.obj
tairetsu_selected_event.obj: src/events/tairetsu_selected_event.cpp stdafx.obj
window_base.obj: src/windows/window_base.cpp stdafx.obj
select_window.obj: src/windows/select_window.cpp stdafx.obj
page_select_window.obj: src/windows/page_select_window.cpp stdafx.obj
script_window.obj: src/windows/script_window.cpp stdafx.obj
text_window.obj: src/windows/text_window.cpp stdafx.obj
input_dlg_window.obj: src/windows/input_dlg_window.cpp stdafx.obj
tairetsu_window.obj: src/windows/tairetsu_window.cpp stdafx.obj
opening_window.obj: src/windows/opening_window.cpp stdafx.obj
camp_window.obj: src/windows/camp_window.cpp stdafx.obj
camp_base_window.obj: src/windows/camp_base_window.cpp stdafx.obj
camp_status_window.obj: src/windows/camp_status_window.cpp stdafx.obj
camp_item_window.obj: src/windows/camp_item_window.cpp stdafx.obj
camp_tairetsu_window.obj: src/windows/camp_tairetsu_window.cpp stdafx.obj
shop_item_list_window.obj: src/windows/shop_item_list_window.cpp stdafx.obj
window_manager.obj: src/window_manager.cpp stdafx.obj
event_checker_base.obj: src/events/event_checker_base.cpp stdafx.obj
key_event_checker.obj: src/events/key_event_checker.cpp stdafx.obj
event_manager.obj: src/event_manager.cpp stdafx.obj
event_notify.obj: src/event_notify.cpp stdafx.obj
error_normal.obj: src/error_normal.cpp stdafx.obj
scene_base.obj: src/scenes/scene_base.cpp stdafx.obj
scene_selector_scene.obj: src/scenes/scene_selector_scene.cpp stdafx.obj
camp_scene.obj: src/scenes/camp_scene.cpp stdafx.obj
town_scene.obj: src/scenes/town_scene.cpp stdafx.obj
castle_scene.obj: src/scenes/castle_scene.cpp stdafx.obj
opening_scene.obj: src/scenes/opening_scene.cpp stdafx.obj
title_scene.obj: src/scenes/title_scene.cpp stdafx.obj
tower_gate_scene.obj: src/scenes/tower_gate_scene.cpp stdafx.obj
bar_scene.obj: src/scenes/bar_scene.cpp stdafx.obj
guild_scene.obj: src/scenes/guild_scene.cpp stdafx.obj
temple_scene.obj: src/scenes/temple_scene.cpp stdafx.obj
shop_scene.obj: src/scenes/shop_scene.cpp stdafx.obj
hotel_scene.obj: src/scenes/hotel_scene.cpp stdafx.obj
wten.obj: src/wten.cpp stdafx.obj src/version.h
main.obj: src/main.cpp stdafx.obj

debug_scene.obj:  src/debug_scene.cpp stdafx.obj
