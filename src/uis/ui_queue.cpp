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

	unsigned int GetUIWidth(boost::shared_ptr<const UIBase> ui) {
		opt_error<unsigned int>::type calc = ui->CalcWidth();
		BOOST_ASSERT(calc.which() == 1);
		opt_error<boost::tuple<unsigned int, unsigned int> >::type size = ui->GetSize();
		BOOST_ASSERT(size.which() == 1);
		return std::max(
			boost::get<unsigned int>(calc),
			boost::get<boost::tuple<unsigned int, unsigned int> >(size).get<0>()
		);
	}

	unsigned int GetUIHeight(boost::shared_ptr<const UIBase> ui) {
		opt_error<unsigned int>::type calc = ui->CalcHeight();
		BOOST_ASSERT(calc.which() == 1);
		opt_error<boost::tuple<unsigned int, unsigned int> >::type size = ui->GetSize();
		BOOST_ASSERT(size.which() == 1);
		return std::max(
			boost::get<unsigned int>(calc),
			boost::get<boost::tuple<unsigned int, unsigned int> >(size).get<1>()
		);
	}

	struct UIMaxHeight {
		bool operator() (const UI_PAIR& left, const UI_PAIR& right) const {
			return GetUIHeight(left.get<1>()) < GetUIHeight(right.get<1>());
		}
	};
	struct UIMaxWidth {
		bool operator() (const UI_PAIR& left, const UI_PAIR& right) const {
			return GetUIWidth(left.get<1>()) < GetUIWidth(right.get<1>());
		}
	};
	struct UISumHeight {
		int operator() (const int value, const UI_PAIR& obj) const {
			return value + GetUIHeight(obj.get<1>());
		}
	};
	struct UISumWidth {
		int operator() (const int value, const UI_PAIR& obj) const {
			return value + GetUIWidth(obj.get<1>());
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
	BOOST_FOREACH(UI_PAIR pair, ui_list) {
		boost::shared_ptr<UIBase> ui = pair.get<1>();
		OPT_ERROR(ui->Draw());
	}
	return UIBase::Draw();
}

boost::optional<boost::shared_ptr<Error> > UIQueue::Draw(unsigned int abs_x, unsigned int abs_y) {
	return boost::none;
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
	unsigned int this_min_width;
	OPT_UINT(this_min_width, CalcWidth());
	unsigned int this_min_height;
	OPT_UINT(this_min_height, CalcHeight());

	bool split = true;
	BOOST_FOREACH(UI_PAIR pair, ui_list) {
		POSITION pos;
		boost::shared_ptr<UIBase> ui;
		boost::tie(pos, ui) = pair;

		if(split && (pos == COL_POSITION_RIGHT || pos == ROW_POSITION_BOTTOM)) {
			if(col_split) {
				x += this->width - this_min_width;
			} else {
				y += this->height - this_min_height;
			}
			split = false;
		}
		ui->Move(x, y);
		ui->Resize();
		unsigned int width;
		unsigned int height;
		OPT_PAIR_UINT(width, height, ui->GetSize());
		if(col_split) {
			x += width;
		} else {
			y += height;
		}
	}
	return boost::none;
}

} // uis

} // wten
