
#ifndef _DEBUG
// BOOST_ASSERT�𖳌��ɂ���
#define BOOST_DISABLE_ASSERTS
#endif

//�O�����C�u�����[�̌x���͖��������Ă���
#pragma warning(push)
#pragma warning(disable: 4061) // case��`����Ă��Ȃ��񋓎q������܂�
#pragma warning(disable: 4100) // �錾���ꂽ�������g�p���Ă��܂���
#pragma warning(disable: 4127) // ���������萔�ł�
#pragma warning(disable: 4189) // �ϐ��ɑ����Q�Ƃ���Ă��܂���
#pragma warning(disable: 4201) // ��W���̊g���@�\�A�����̍\����/���p�̂��g�p���Ă��܂�
#pragma warning(disable: 4263) // ���z�֐����I�[�o�[���C�h���Ă��܂����A�����̌^���Ⴂ�܂�
#pragma warning(disable: 4264) // �����̌^�݈̂Ⴄ�����֐�����`���ꂽ���߁A���z�֐��ɂ̓A�N�Z�X�ł��Ȃ��Ȃ�܂�
#pragma warning(disable: 4266) // ���z�֐��̂��ׂẴI�[�o�[���[�h���I�[�o�[���C�h���Ă��܂���
#pragma warning(disable: 4350) // const�Ȃ��̎Q�Ɠn���̓��e�������󂯎�邱�Ƃ��ł��Ȃ����߁A�ʂ̃R���X�g���N�^���Ă΂�܂�
#pragma warning(disable: 4365) // signed/unsigned���Ⴄ�^�ϊ����s���܂���
#pragma warning(disable: 4512) // ������Z�q�𐶐����邽�߂ɕK�v�ȃR���X�g���N�^���A�N�Z�X�ł��܂���A������Z�q�����܂���ł���
#pragma warning(disable: 4548) // �����ȃJ���}��
#pragma warning(disable: 4555) // ����p�̂Ȃ���
#pragma warning(disable: 4619) // �����������݂��x���ԍ��͑��݂��܂���
#pragma warning(disable: 4625) // ��{�N���X�̃R�s�[�R���X�g���N�^���A�N�Z�X�s�\�Ȃ̂ŃR�s�[�R���X�g���N�^�����܂���ł���
#pragma warning(disable: 4626) // ��{�N���X�̑�����Z�q���A�N�Z�X�s�\�Ȃ̂ő�����Z�q�����܂���ł���
#pragma warning(disable: 4640) // static�ȃ��[�J���ϐ��̏��������X���b�h�Z�[�t�ł͂���܂���
#pragma warning(disable: 4668) // ��`����Ă��Ȃ��V���{����#if/#elif�Ŏg�p����܂���
#pragma warning(disable: 4820) // �\���̂̃p�b�e�B���O���������܂���

// RELEASE�r���h���̂ݔ�������x���̖�����
#ifndef _DEBUG
#pragma warning(disable: 4710) // inline�錾����Ă���֐�/���\�b�h��inline�W�J���܂���ł���
#pragma warning(disable: 4711) // inline�錾����Ă��Ȃ��֐�/���\�b�h��inline�W�J���܂���
#endif

//wchar_t������̕�����Ƃ��Ďg�p����
#define UNICODE
//std::min��std::max�ƒ�`���d�����邽��
#define NOMINMAX
#include <windows.h>

#include "DxLib.h"

//phoenix�ň�����ő����
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
//�����R�[�h�G���[���邽��
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
//�O�����C�u�����[�̌x�����������܂�

#pragma warning(disable: 4061) // case��`����Ă��Ȃ��񋓎q������܂�
#pragma warning(disable: 4127) // ���������萔�ł�
#pragma warning(disable: 4350) // const�Ȃ��̎Q�Ɠn���̓��e�������󂯎�邱�Ƃ��ł��Ȃ����߁A�ʂ̃R���X�g���N�^���Ă΂�܂�
#pragma warning(disable: 4503) // ��������4096�����𒴂������ߐ؂�̂Ă��܂�
#pragma warning(disable: 4514) // �g�p����Ă��Ȃ��֐�/���\�b�h���폜����܂���
#pragma warning(disable: 4640) // static�ȃ��[�J���ϐ��̏��������X���b�h�Z�[�t�ł͂���܂���
#pragma warning(disable: 4710) // �C�����C���֐��Ƃ��đI������܂������C�����C���W�J�ł��܂���ł���

// RELEASE�r���h���̂ݔ�������x���̖�����
#ifndef _DEBUG
#pragma warning(disable: 4100) // �錾���ꂽ�������g�p���Ă��܂���
#pragma warning(disable: 4189) // �ϐ��ɑ����Q�Ƃ���Ă��܂���
#pragma warning(disable: 4710) // inline�錾����Ă���֐�/���\�b�h��inline�W�J���܂���ł���
#pragma warning(disable: 4711) // inline�錾����Ă��Ȃ��֐�/���\�b�h��inline�W�J���܂���
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
