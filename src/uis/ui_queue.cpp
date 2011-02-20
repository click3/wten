#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;
using namespace boost::assign;

namespace {
	typedef boost::tuple<UIQueue::POSITION, boost::shared_ptr<UIBase> > UI_PAIR;

	bool PositionToBool(UIQueue::POSITION pos) {
		if(pos == UIQueue::COL_POSITION_LEFT || pos == UIQueue::COL_POSITION_RIGHT) {
			return true;
		} else {
			return false;
		}
	}

	bool IsColSplit(const std::vector<UI_PAIR>& ui_list) {
		boost::optional<bool> col_split;
		BOOST_FOREACH(UI_PAIR pair, ui_list) {
			UIQueue::POSITION pos;
			boost::shared_ptr<UIBase> ui;
			boost::tie(pos, ui) = pair;
			if(!col_split) {
				col_split = PositionToBool(pos);
			} else {
				BOOST_ASSERT(col_split.get() == PositionToBool(pos));
			}
			BOOST_ASSERT(ui);
			BOOST_ASSERT(ui->GetMoveMode() == UIBase::MOVE_MODE_FREE_FREE);
		}
		return col_split.get();
	}

	struct UIMaxHeight {
		bool operator() (const UI_PAIR& left, const UI_PAIR& right) const {
			opt_error<unsigned int>::type left_value = left.get<1>()->CalcHeight();
			opt_error<unsigned int>::type right_value = right.get<1>()->CalcHeight();
			BOOST_ASSERT(left_value.which() == 1);
			BOOST_ASSERT(right_value.which() == 1);
			return boost::get<unsigned int>(left_value) < boost::get<unsigned int>(right_value);
		}
	};
	struct UIMaxWidth {
		bool operator() (const UI_PAIR& left, const UI_PAIR& right) const {
			opt_error<unsigned int>::type left_value = left.get<1>()->CalcWidth();
			opt_error<unsigned int>::type right_value = right.get<1>()->CalcWidth();
			BOOST_ASSERT(left_value.which() == 1);
			BOOST_ASSERT(right_value.which() == 1);
			return boost::get<unsigned int>(left_value) < boost::get<unsigned int>(right_value);
		}
	};
	struct UISumHeight {
		int operator() (const int value, const UI_PAIR& obj) const {
			opt_error<unsigned int>::type obj_value = obj.get<1>()->CalcHeight();
			if(obj_value.which() == 0) {
				boost::get<boost::shared_ptr<Error> >(obj_value)->Abort();
				BOOST_ASSERT(false);
				return 0;
			}
			return value + boost::get<unsigned int>(obj_value);
		}
	};
	struct UISumWidth {
		int operator() (const int value, const UI_PAIR& obj) const {
			opt_error<unsigned int>::type obj_value = obj.get<1>()->CalcWidth();
			if(obj_value.which() == 0) {
				boost::get<boost::shared_ptr<Error> >(obj_value)->Abort();
				BOOST_ASSERT(false);
				return 0;
			}
			return value + boost::get<unsigned int>(obj_value);
		}
	};
} // anonymous

UIQueue::UIQueue(const std::vector<UI_PAIR>& ui_list) :
	ui_list(ui_list), col_split(IsColSplit(ui_list))
{
	BOOST_ASSERT(ui_list.size() > 0);
}

UIQueue::~UIQueue() {
}

boost::optional<boost::shared_ptr<Error> > UIQueue::SetOwnerWindow(boost::weak_ptr<const windows::WindowBase> window) {
	OPT_ERROR(UIBase::SetOwnerWindow(window));
	BOOST_FOREACH(UI_PAIR pair, ui_list) {
		OPT_ERROR(pair.get<1>()->SetOwnerWindow(window));
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIQueue::Move(void) {
	OPT_ERROR(UIBase::Move());
	return ReloadInnerUI();
}

boost::optional<boost::shared_ptr<Error> > UIQueue::Move(unsigned int x, unsigned int y) {
	OPT_ERROR(UIBase::Move(x, y));
	return ReloadInnerUI();
}

boost::optional<boost::shared_ptr<Error> > UIQueue::Resize(unsigned int width, unsigned int height) {
	OPT_ERROR(UIBase::Resize(width, height));
	return ReloadInnerUI();
}

boost::optional<boost::shared_ptr<Error> > UIQueue::Resize(void) {
	OPT_ERROR(UIBase::Resize());
	return ReloadInnerUI();
}

boost::optional<boost::shared_ptr<Error> > UIQueue::Draw(void) {
	return UIBase::Draw();
}

boost::optional<boost::shared_ptr<Error> > UIQueue::Draw(unsigned int abs_x, unsigned int abs_y) {
	BOOST_FOREACH(UI_PAIR pair, ui_list) {
		OPT_ERROR(pair.get<1>()->Draw(abs_x, abs_y));
	}
}

opt_error<unsigned int>::type UIQueue::CalcWidth() const {
	if(col_split) { // â°ï¿Ç—
		return std::accumulate(ui_list.begin(), ui_list.end(), 0, UISumWidth());
	} else { // ècï¿Ç—
		std::vector<UI_PAIR>::const_iterator it = std::max_element(ui_list.begin(), ui_list.end(), UIMaxWidth());
		BOOST_ASSERT(it != ui_list.end());
		return it->get<1>()->CalcWidth();
	}
}

opt_error<unsigned int>::type UIQueue::CalcHeight() const {
	if(col_split) { // â°ï¿Ç—
		std::vector<UI_PAIR>::const_iterator it = std::max_element(ui_list.begin(), ui_list.end(), UIMaxHeight());
		BOOST_ASSERT(it != ui_list.end());
		return it->get<1>()->CalcHeight();
	} else { // ècï¿Ç—
		return std::accumulate(ui_list.begin(), ui_list.end(), 0, UISumHeight());
	}
}

boost::optional<boost::shared_ptr<Error> > UIQueue::ReloadInnerUI(void) {
	unsigned int x = this->x;
	unsigned int y = this->y;
	bool split = true;
	BOOST_FOREACH(UI_PAIR pair, ui_list) {
		POSITION pos;
		boost::shared_ptr<UIBase> ui;
		boost::tie(pos, ui) = pair;

		if(split && (pos == COL_POSITION_RIGHT || pos == ROW_POSITION_BOTTOM)) {
			if(col_split) {
				unsigned int width;
				OPT_UINT(width, CalcWidth());
				x += this->width - width;
			} else {
				unsigned int height;
				OPT_UINT(height, CalcHeight());
				y += this->height - height;
			}
			split = false;
		}
		ui->Move(x, y);
		if(col_split) {
			unsigned int width;
			OPT_UINT(width, ui->CalcWidth());
			x += width;
		} else {
			unsigned int height;
			OPT_UINT(height, ui->CalcHeight());
			y += height;
		}
	}
	return boost::none;
}

} // uis

} // wten
