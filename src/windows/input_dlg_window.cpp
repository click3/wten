#include "stdafx.h"

namespace wten { namespace windows {

using namespace utility;
using namespace boost::assign;

InputDlgWindow::InputDlgWindow(boost::shared_ptr<const std::wstring> message, boost::shared_ptr<const std::wstring> frame_filename) :
	WindowBase(frame_filename), ui_input_dlg(new uis::UIInputDlg(message, default_frame_graph))
{
	BOOST_ASSERT(ui_input_dlg);
}

InputDlgWindow::InputDlgWindow(boost::shared_ptr<const std::wstring> message, boost::shared_ptr<const Graph> frame_graph) :
	WindowBase(frame_graph), ui_input_dlg(new uis::UIInputDlg(message, default_frame_graph))
{
	BOOST_ASSERT(ui_input_dlg);
}

InputDlgWindow::~InputDlgWindow() {
}

boost::optional<boost::shared_ptr<Error> > InputDlgWindow::WindowInitialize(void) {
	OPT_ERROR(WindowBase::WindowInitialize());
	OPT_ERROR(AddUI(ui_input_dlg));
	ui_input_dlg->SetMoveMode(uis::UIBase::MOVE_MODE_CENTER_CENTER);
	OPT_ERROR(ui_input_dlg->Move());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > InputDlgWindow::Resize(unsigned int width, unsigned int height) {
	OPT_ERROR(WindowBase::Resize(width, height));
	OPT_ERROR(ui_input_dlg->Resize(width, height));
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > InputDlgWindow::Draw(void) {
	OPT_ERROR(WindowBase::Draw());
	OPT_ERROR(InputStringEvent());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > InputDlgWindow::InputStringEvent(void) {
	boost::shared_ptr<Event> event(new events::InputStringEvent(ui_input_dlg->GetText()));
	OPT_ERROR(RemoveThisWindow());
	EventNotify::Send(event);
	return boost::none;
}

} // windows

} // wten
