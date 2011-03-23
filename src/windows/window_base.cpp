#include "stdafx.h"

namespace wten {

namespace windows {

using namespace utility;

WindowBase::WindowBase(boost::shared_ptr<const std::wstring> default_frame_filename) :
	x(0),	y(0),	width(DEFAULT_SCREEN_SIZE_X),	height(DEFAULT_SCREEN_SIZE_Y), default_frame_graph(new Graph(default_frame_filename))
{
}

WindowBase::WindowBase(boost::shared_ptr<const Graph> default_frame_graph) :
	x(0),	y(0),	width(DEFAULT_SCREEN_SIZE_X),	height(DEFAULT_SCREEN_SIZE_Y), default_frame_graph(default_frame_graph)
{
}

WindowBase::~WindowBase() {
}

boost::optional<boost::shared_ptr<Error> > WindowBase::WindowInitialize(void) {
	OPT_ERROR(ClearUI());
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowBase::OnForeground(void) {
	return boost::none;
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type WindowBase::GetPoint(void) const {
	return boost::make_tuple<unsigned int, unsigned int>(x, y);
}

opt_error<boost::tuple<unsigned int, unsigned int> >::type WindowBase::GetSize(void) const {
	return boost::make_tuple<unsigned int, unsigned int>(width, height);
}

boost::optional<boost::shared_ptr<Error> > WindowBase::Move(unsigned int x, unsigned int y) {
	this->x = x;
	this->y = y;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowBase::Resize(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowBase::Draw(void) {
	unsigned int max_width;
	unsigned int max_height;
	OPT_PAIR_UINT(max_width, max_height, DxLibWrapper::GetWindowSize());

	if(x+width > max_width || y+height > max_height) {
		return CREATE_ERROR(ERROR_CODE_OUTSIDE_RANGE);
	}

	OPT_ERROR(DxLibWrapper::DrawBox(x, y, x+width, y+height, Color(0,0,0)));

	BOOST_FOREACH(boost::shared_ptr<UI> ui, ui_stack) {
		OPT_ERROR(ui->Draw());
	}
	return boost::none;
}

opt_error<boost::optional<boost::shared_ptr<Event> > >::type WindowBase::NotifyEvent(boost::shared_ptr<Event> event) {
	return event;
}

boost::optional<boost::shared_ptr<Error> > WindowBase::AddUI(boost::shared_ptr<UI> ui) {
	ui_stack.push_back(ui);
	boost::shared_ptr<WindowBase> this_ptr = shared_from_this();
	BOOST_ASSERT(this_ptr);
	OPT_ERROR(ui->SetOwnerWindow(this_ptr));
	return boost::none;
}

opt_error<bool>::type WindowBase::RemoveUI(boost::shared_ptr<UI> ui) {
	std::vector<boost::shared_ptr<UI> >::iterator it = std::find(ui_stack.begin(), ui_stack.end(), ui);
	if(it == ui_stack.end()) {
		return false;
	}
	ui_stack.erase(it);
	return true;
}

boost::optional<boost::shared_ptr<Error> > WindowBase::ClearUI(void) {
	BOOST_FOREACH(boost::shared_ptr<UI> ui, ui_stack) {
		OPT_ERROR(ui->ClearOwnerWindow());
	}
	ui_stack.clear();
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowBase::RemoveThisWindow(void) {
	boost::shared_ptr<WindowBase> this_ptr = shared_from_this();
	BOOST_ASSERT(this_ptr);
	boost::shared_ptr<events::PopWindowEvent> event(new events::PopWindowEvent(this_ptr));
	EventNotify::Send(event);
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowBase::AddUI(boost::shared_ptr<uis::UIBase> ui, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	BOOST_ASSERT(ui);

	ui->SetMoveMode(move_mode);
	OPT_ERROR(AddUI(ui));
	OPT_ERROR(ui->Move(x, y));
	if(width == 0 && height == 0) {
		OPT_ERROR(ui->Resize());
	} else {
		OPT_ERROR(ui->Resize(width, height));
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > WindowBase::AddBoxUI(uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	boost::shared_ptr<uis::UIBase> ui(new uis::UIBox(default_frame_graph));
	return AddUI(ui, move_mode, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > WindowBase::AddImageUI(boost::shared_ptr<const std::wstring> image_filename, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y) {
	boost::shared_ptr<uis::UIBase> ui(new uis::UIImage(image_filename));
	return AddUI(ui, move_mode, x, y, 0, 0);
}

boost::optional<boost::shared_ptr<Error> > WindowBase::AddTextUI(boost::shared_ptr<const std::wstring> text, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	boost::shared_ptr<uis::UIBase> ui(new uis::UIStringBox(default_frame_graph, text));
	return AddUI(ui, move_mode, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > WindowBase::AddPTStatusUI(boost::shared_ptr<const PTData> pt_data, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	boost::shared_ptr<uis::UIBase> ui(new uis::UIPTStatus(default_frame_graph, pt_data));
	return AddUI(ui, move_mode, x, y, width, height);
}

boost::optional<boost::shared_ptr<Error> > WindowBase::AddCharStatusUI(boost::shared_ptr<const PTData> pt_data, unsigned int char_index, uis::UIBase::MOVE_MODE move_mode, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	boost::shared_ptr<uis::UIBase> ui(new uis::UICharStatus(default_frame_graph, pt_data, char_index));
	return AddUI(ui, move_mode, x, y, width, height);
}

} // windows

} // wten
