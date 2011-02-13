cc  = cc
opt = /errorReport:none /W1 /MT /EHsc /Ox /Fpwten.pch
obj = DxLib_lib.obj graph.obj window_manager.obj event_manager.obj debug_scene.obj error_normal.obj event_notify.obj scene_base.obj wten.obj stdafx.obj main.obj
exe = wten.exe

.c.obj:
        $(cc) /c /Yustdafx.h $(opt) /Tp $<
.cpp.obj:
        $(cc) /c /Yustdafx.h $(opt) /Tp $<
$(exe).exe: $(obj)
        $(cc) $(opt) /Fe$* $** $(lib)

src/stdafx.h: stdafx.obj
	touch src/stdafx.h
stdafx.obj: src/DxLib_lib.h src/error.h src/event.h src/event_manager.h src/graph.h src/ui.h src/utility.h src/window.h src/window_manager.h src/scene.h src/wten.h src/debug_scene.h src/error_normal.h src/event_notify.h src/scene_base.h
        $(cc) $(opt) /c /Yc /Tp src/stdafx.cpp

DxLib_lib.obj: src/DxLib_lib.cpp src/stdafx.h
graph.obj: src/graph.cpp src/stdafx.h
window_manager.obj: src/window_manager.cpp src/stdafx.h
event_manager.obj: src/event_manager.cpp src/stdafx.h
event_notify.obj: src/event_notify.cpp src/stdafx.h
error_normal.obj: src/error_normal.cpp src/stdafx.h
scene_base.obj: src/scene_base.cpp src/stdafx.h
wten.obj: src/wten.cpp src/stdafx.h
main.obj: src/main.cpp src/stdafx.h

debug_scene.obj:  src/debug_scene.cpp src/stdafx.h
