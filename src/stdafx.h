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

#include <vector>
#include <queue>
#include <map>

#include "org/click3/notification_center.h"

#include "utility.h"
#include "error.h"
#include "error_normal.h"
#include "graph.h"
#include "event.h"
#include "window.h"
#include "ui.h"
#include "event_manager.h"
#include "window_manager.h"
#include "scene.h"
#include "scene_base.h"
#include "DxLib_lib.h"
#include "wten.h"

#include "debug_scene.h"
