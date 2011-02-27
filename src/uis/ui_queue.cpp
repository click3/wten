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

	UIQueue::INNER_POSITION CalcInnerPosition(boost::optional<UIQueue::INNER_POSITION> inner_position, bool col_split) {
		if(inner_position) {
			return inner_position.get();
		}
		if(col_split) {
			return UIQueue::INNER_POSITION_TOP;
		} else {
			return UIQueue::INNER_POSITION_LEFT;
		}
	}

	boost::tuple<unsigned int, unsigned int> CalcInnerPosition(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int owner_width, unsigned int owner_height, bool col_split, UIQueue::INNER_POSITION inner_position) {
		unsigned int move_x = x;
		unsigned int move_y = y;
		if(!col_split) {
			BOOST_ASSERT(owner_width >= width);
			switch(inner_position) {
				case UIQueue::INNER_POSITION_LEFT:
					break;
				case UIQueue::INNER_POSITION_RIGHT:
					move_x = x + owner_width - width;
					break;
				case UIQueue::INNER_POSITION_CENTER:
					move_x = x + (owner_width - width) / 2;
					break;
				default:
					BOOST_ASSERT(false);
			}
		} else {
			BOOST_ASSERT(owner_height >= height);
			switch(inner_position) {
				case UIQueue::INNER_POSITION_TOP:
					break;
				case UIQueue::INNER_POSITION_BOTTOM:
					move_y =y + owner_height - height;
					break;
				case UIQueue::INNER_POSITION_CENTER:
					move_y = y + (owner_height - height) / 2;
					break;
				default:
					BOOST_ASSERT(false);
			}
		}
		return boost::make_tuple(move_x, move_y);
	}
} // anonymous

UIQueue::UIQueue(const std::vector<UI_PAIR>& ui_list, boost::optional<INNER_POSITION> inner_position) :
	ui_list(ui_list), col_split(IsColSplit(ui_list)), inner_position(CalcInnerPosition(inner_position, col_split))
{
	BOOST_ASSERT(ui_list.size() > 0);
	if(col_split) {
		BOOST_ASSERT(this->inner_position != INNER_POSITION_LEFT);
		BOOST_ASSERT(this->inner_position != INNER_POSITION_RIGHT);
	} else {
		BOOST_ASSERT(this->inner_position != INNER_POSITION_TOP);
		BOOST_ASSERT(this->inner_position != INNER_POSITION_BOTTOM);
	}
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

boost::optional<boost::shared_ptr<Error> > UIQueue::ClearOwnerWindow(void) {
	OPT_ERROR(UIBase::ClearOwnerWindow());
	BOOST_FOREACH(UI_PAIR pair, ui_list) {
		OPT_ERROR(pair.get<1>()->ClearOwnerWindow());
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
	OPT_ERROR(UIBase::Draw());
	BOOST_FOREACH(UI_PAIR pair, ui_list) {
		boost::shared_ptr<UIBase> ui = pair.get<1>();
		OPT_ERROR(ui->Draw());
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > UIQueue::Draw(unsigned int abs_x, unsigned int abs_y) {
	return boost::none;
}

opt_error<unsigned int>::type UIQueue::CalcWidth() const {
	if(col_split) { // ������
		return std::accumulate(ui_list.begin(), ui_list.end(), 0, UISumWidth());
	} else { // �c����
		std::vector<UI_PAIR>::const_iterator it = std::max_element(ui_list.begin(), ui_list.end(), UIMaxWidth());
		BOOST_ASSERT(it != ui_list.end());
		return GetUIWidth(it->get<1>());
	}
}

opt_error<unsigned int>::type UIQueue::CalcHeight() const {
	if(col_split) { // ������
		std::vector<UI_PAIR>::const_iterator it = std::max_element(ui_list.begin(), ui_list.end(), UIMaxHeight());
		BOOST_ASSERT(it != ui_list.end());
		return GetUIHeight(it->get<1>());
	} else { // �c����
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
	this->width = std::max(this->width, this_min_width);
	this->height = std::max(this->height, this_min_height);

	bool split = true;
	BOOST_FOREACH(UI_PAIR pair, ui_list) {
		POSITION pos;
		boost::shared_ptr<UIBase> ui;
		boost::tie(pos, ui) = pair;

		if(split) {
			if(pos == COL_POSITION_RIGHT || pos == ROW_POSITION_BOTTOM) {
				if(col_split) {
					x += this->width - this_min_width;
				} else {
					y += this->height - this_min_height;
				}
				split = false;
			}
		} else {
			BOOST_ASSERT(pos == COL_POSITION_RIGHT || pos == ROW_POSITION_BOTTOM);
		}
		ui->Resize();
		unsigned int width;
		unsigned int height;
		OPT_PAIR_UINT(width, height, ui->GetSize());
		{
			unsigned int move_x;
			unsigned int move_y;
			boost::tie(move_x, move_y) = CalcInnerPosition(x, y, width, height, this->width, this->height, col_split, inner_position);
			ui->Move(move_x, move_y);
		}
		BOOST_ASSERT(x+width <= this->x + this->width);
		BOOST_ASSERT(y+height <= this->y + this->height);
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
