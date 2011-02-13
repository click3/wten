cc  = cc
opt = /errorReport:none /W1 /MT /EHsc /Ox /Fpwten.pch
obj = DxLib_lib.obj graph.obj window_base.obj window_manager.obj event_manager.obj debug_scene.obj error_normal.obj event_notify.obj scene_base.obj wten.obj stdafx.obj main.obj
exe = wten.exe

.c.obj:
        $(cc) /c /Yustdafx.h $(opt) /Tp $<
.cpp.obj:
        $(cc) /c /Yustdafx.h $(opt) /Tp $<
$(exe).exe: $(obj)
        $(cc) $(opt) /Fe$* $** $(lib)

src/stdafx.h: src/DxLib_lib.h src/error.h src/event.h src/event_manager.h src/graph.h src/ui.h src/utility.h src/window.h src/window_manager.h src/scene.h src/wten.h src/debug_scene.h src/error_normal.h src/event_notify.h src/scene_base.h src/window_base.h
	touch src/stdafx.h
stdafx.obj: src/stdafx.h
        $(cc) $(opt) /c /Yc /Tp src/stdafx.cpp

DxLib_lib.obj: src/DxLib_lib.cpp stdafx.obj
graph.obj: src/graph.cpp stdafx.obj
window_base.obj: src/window_base.cpp stdafx.obj
window_manager.obj: src/window_manager.cpp stdafx.obj
event_manager.obj: src/event_manager.cpp stdafx.obj
event_notify.obj: src/event_notify.cpp stdafx.obj
error_normal.obj: src/error_normal.cpp stdafx.obj
scene_base.obj: src/scene_base.cpp stdafx.obj
wten.obj: src/wten.cpp stdafx.obj
main.obj: src/main.cpp stdafx.obj

debug_scene.obj:  src/debug_scene.cpp stdafx.obj
