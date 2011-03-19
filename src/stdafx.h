
#ifndef _DEBUG
// BOOST_ASSERTを無効にする
#define BOOST_DISABLE_ASSERTS
#endif

//外部ライブラリーの警告は無効化しておく
#pragma warning(push)
#pragma warning(disable: 4061) // case定義されていない列挙子があります
#pragma warning(disable: 4100) // 宣言された引数を使用していません
#pragma warning(disable: 4127) // 条件式が定数です
#pragma warning(disable: 4189) // 変数に代入後参照されていません
#pragma warning(disable: 4201) // 非標準の拡張機能、無名の構造体/共用体を使用しています
#pragma warning(disable: 4263) // 仮想関数をオーバーライドしていますが、引数の型が違います
#pragma warning(disable: 4264) // 引数の型のみ違う同名関数が定義されたため、仮想関数にはアクセスできなくなります
#pragma warning(disable: 4266) // 仮想関数のすべてのオーバーロードをオーバーライドしていません
#pragma warning(disable: 4350) // constなしの参照渡しはリテラルを受け取ることができないため、別のコンストラクタが呼ばれます
#pragma warning(disable: 4365) // signed/unsignedが違う型変換が行われました
#pragma warning(disable: 4512) // 代入演算子を生成するために必要なコンストラクタがアクセスできません、代入演算子を作れませんでした
#pragma warning(disable: 4548) // 無効なカンマ式
#pragma warning(disable: 4555) // 副作用のない式
#pragma warning(disable: 4619) // 無効化を試みた警告番号は存在しません
#pragma warning(disable: 4625) // 基本クラスのコピーコンストラクタがアクセス不能なのでコピーコンストラクタが作れませんでした
#pragma warning(disable: 4626) // 基本クラスの代入演算子がアクセス不能なので代入演算子が作れませんでした
#pragma warning(disable: 4640) // staticなローカル変数の初期化がスレッドセーフではありません
#pragma warning(disable: 4668) // 定義されていないシンボルが#if/#elifで使用されました
#pragma warning(disable: 4820) // 構造体のパッティングが発生しました

// RELEASEビルド時のみ発生する警告の無効化
#ifndef _DEBUG
#pragma warning(disable: 4710) // inline宣言されている関数/メソッドをinline展開しませんでした
#pragma warning(disable: 4711) // inline宣言されていない関数/メソッドをinline展開しました
#endif

//wchar_tを既定の文字列として使用する
#define UNICODE
//std::minとstd::maxと定義が重複するため
#define NOMINMAX
#include <windows.h>

#include "DxLib.h"

//phoenixで扱える最大引数
#define BOOST_RESULT_OF_NUM_ARGS 19
#define FUSION_MAX_VECTOR_SIZE 19
#define PHOENIX_LIMIT 19

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

#include <limits.h>
#include <locale.h>
#include <stdio.h>

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <numeric>

#pragma warning(pop)
//外部ライブラリーの警告無効ここまで

#pragma warning(disable: 4061) // case定義されていない列挙子があります
#pragma warning(disable: 4127) // 条件式が定数です
#pragma warning(disable: 4350) // constなしの参照渡しはリテラルを受け取ることができないため、別のコンストラクタが呼ばれます
#pragma warning(disable: 4503) // 装飾名が4096文字を超えたため切り捨てられます
#pragma warning(disable: 4514) // 使用されていない関数/メソッドが削除されました
#pragma warning(disable: 4640) // staticなローカル変数の初期化がスレッドセーフではありません
#pragma warning(disable: 4710) // インライン関数として選択されましたがインライン展開できませんでした

// RELEASEビルド時のみ発生する警告の無効化
#ifndef _DEBUG
#pragma warning(disable: 4100) // 宣言された引数を使用していません
#pragma warning(disable: 4189) // 変数に代入後参照されていません
#pragma warning(disable: 4710) // inline宣言されている関数/メソッドをinline展開しませんでした
#pragma warning(disable: 4711) // inline宣言されていない関数/メソッドをinline展開しました
#endif

#include "org/click3/notification_center.h"

#include "error.h"
#include "utility.h"
#include "global_data.h"
#include "play_time.h"
#include "error_normal.h"
#include "list_csv_parser_base.h"
#include "graph.h"
#include "action.h"
#include "job.h"
#include "job_list.h"
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
#include "uis/ui_selector_base.h"
#include "uis/ui_selector.h"
#include "uis/ui_string_box.h"
#include "uis/ui_queue.h"
#include "uis/ui_pager.h"
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
#include "actions/dummy_spell.h"
#include "spell_list.h"
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
