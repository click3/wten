//std::minとstd::maxと定義が重複するため
#define NOMINMAX
#include <windows.h>

#include "DxLib.h"

//phoenixで扱える最大引数
#define BOOST_RESULT_OF_NUM_ARGS 14
#define FUSION_MAX_VECTOR_SIZE 14
#define PHOENIX_LIMIT 14

#include "boost/config/warning_disable.hpp"
#include "boost/utility.hpp"
#include "boost/assert.hpp"
#include "boost/scope_exit.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "boost/optional.hpp"
#include "boost/tuple/tuple.hpp"
#include "boost/variant.hpp"
#include "boost/foreach.hpp"
#include "boost/range/adaptor/filtered.hpp"
#include "boost/range/adaptor/transformed.hpp"
#include "boost/range/adaptor/uniqued.hpp"
#include "boost/range/algorithm/copy.hpp"
#include "boost/assign.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/range/algorithm.hpp"
#include "boost/function.hpp"
#include "boost/bind.hpp"
#include "boost/format.hpp"
#include "boost/lexical_cast.hpp"
//文字コードエラーするため
#pragma warning(push)
#pragma warning(disable: 4819)
#include "boost/spirit/include/qi.hpp"
#pragma warning(pop)
#include "boost/spirit/include/phoenix.hpp"

#include <locale.h>
#include <stdio.h>

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <numeric>

#include "org/click3/notification_center.h"

#include "error.h"
#include "utility.h"
#include "global_data.h"
#include "play_time.h"
#include "error_normal.h"
#include "graph.h"
#include "action.h"
#include "job.h"
#include "char_condition.h"
#include "pt_condition.h"
#include "enemy_condition.h"
#include "enemy_info.h"
#include "enemy_status.h"
#include "item_info.h"
#include "item.h"
#include "item_info_list.h"
#include "event.h"
#include "events/event_base.h"
#include "events/key_event.h"
#include "events/on_select_event.h"
#include "events/on_select_change_event.h"
#include "events/pop_window_event.h"
#include "events/input_string_event.h"
#include "window.h"
#include "ui.h"
#include "uis/ui_base.h"
#include "uis/ui_box.h"
#include "uis/ui_string.h"
#include "uis/ui_image.h"
#include "uis/ui_selector.h"
#include "uis/ui_string_box.h"
#include "uis/ui_queue.h"
#include "uis/ui_pt_status.h"
#include "uis/ui_input_string.h"
#include "uis/ui_input_dlg.h"
#include "uis/ui_dummy.h"
#include "uis/ui_char_status.h"
#include "event_checker.h"
#include "events/event_checker_base.h"
#include "events/key_event_checker.h"
#include "events/next_step_event.h"
#include "events/next_window_event.h"
#include "actions/spell_base.h"
#include "char_status.h"
#include "char_data.h"
#include "pt_data.h"
#include "pt_list.h"
#include "character_list.h"
#include "windows/window_base.h"
#include "windows/select_window.h"
#include "windows/script_window.h"
#include "windows/text_window.h"
#include "windows/input_dlg_window.h"
#include "windows/opening_window.h"
#include "windows/camp_window.h"
#include "windows/camp_base_window.h"
#include "windows/camp_status_window.h"
#include "windows/camp_item_window.h"
#include "event_manager.h"
#include "event_notify.h"
#include "window_manager.h"
#include "scene.h"
#include "scenes/scene_base.h"
#include "scenes/camp_scene.h"
#include "scenes/scene_selector_scene.h"
#include "scenes/town_scene.h"
#include "scenes/castle_scene.h"
#include "scenes/opening_scene.h"
#include "scenes/title_scene.h"
#include "scenes/tower_gate_scene.h"
#include "scenes/bar_scene.h"
#include "scenes/guild_scene.h"
#include "scenes/temple_scene.h"
#include "scenes/shop_scene.h"
#include "scenes/hotel_scene.h"
#include "DxLib_lib.h"
#include "wten.h"

#include "debug_scene.h"
