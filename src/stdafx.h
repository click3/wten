//std::minÇ∆std::maxÇ∆íËã`Ç™èdï°Ç∑ÇÈÇΩÇﬂ
#define NOMINMAX
#include <windows.h>

#include "DxLib.h"

#include "boost/utility.hpp"
#include "boost/assert.hpp"
#include "boost/scope_exit.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/optional.hpp"
#include "boost/tuple/tuple.hpp"
#include "boost/variant.hpp"
#include "boost/foreach.hpp"

#include <locale.h>
#include <stdio.h>

#include <vector>
#include <queue>
#include <map>
#include <algorithm>

#include "org/click3/notification_center.h"

#include "error.h"
#include "utility.h"
#include "error_normal.h"
#include "graph.h"
#include "event.h"
#include "window.h"
#include "window_base.h"
#include "ui.h"
#include "uis/ui_base.h"
#include "uis/ui_box.h"
#include "uis/ui_string.h"
#include "uis/ui_image.h"
#include "uis/ui_string_box.h"
#include "event_manager.h"
#include "event_notify.h"
#include "window_manager.h"
#include "scene.h"
#include "scene_base.h"
#include "DxLib_lib.h"
#include "wten.h"

#include "debug_scene.h"
