#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

UIImage::UIImage(boost::shared_ptr<const std::wstring> filename) :
	image(new Graph(filename)), turn(false), rate(1.0), angle(0), center_x(image->GetWidth() / 2), center_y(image->GetHeight() / 2)
{
	BOOST_ASSERT(filename);
	BOOST_ASSERT(!filename->empty());
	BOOST_ASSERT(image);

	boost::optional<boost::shared_ptr<Error> > error = Resize(image->GetWidth(), image->GetHeight());
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

UIImage::UIImage(boost::shared_ptr<const Graph> image) :
	image(image), turn(false), rate(1.0), angle(0), center_x(image->GetWidth() / 2), center_y(image->GetHeight() / 2)
{
	BOOST_ASSERT(image);

	boost::optional<boost::shared_ptr<Error> > error = Resize(image->GetWidth(), image->GetHeight());
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

UIImage::~UIImage() {
}

boost::shared_ptr<const Graph> UIImage::GetImage(void) const {
	return image;
}

bool UIImage::IsTurn(void) const {
	return turn;
}

void UIImage::SetTurn(bool flag) {
	turn = flag;
}

double UIImage::GetRate(void) const {
	return rate;
}

void UIImage::SetRate(double rate) {
	this->rate = rate;
}

double UIImage::GetAngle(void) const {
	return angle;
}

void UIImage::SetAngle(bool angle) {
	this->angle = angle;
}

boost::tuple<unsigned int, unsigned int> UIImage::GetCenter(void) const {
	return boost::make_tuple(center_x, center_y);
}

void UIImage::SetCenter(unsigned int center_x, unsigned int center_y) {
	this->center_x = center_x;
	this->center_y = center_y;
}

boost::optional<boost::shared_ptr<Error> > UIImage::Draw(void) {
	return UIBase::Draw();
}

boost::optional<boost::shared_ptr<Error> > UIImage::Draw(unsigned int abs_x, unsigned int abs_y) {
	BOOST_ASSERT(image);
	boost::optional<boost::shared_ptr<Error> > error = image->Draw(abs_x + center_x, abs_y + center_y, turn, rate, angle, center_x, center_y);
	if(error) {
		return error.get();
	}
	return boost::none;
}

utility::opt_error<unsigned int>::type UIImage::CalcWidth() const {
	BOOST_ASSERT(image);
	return image->GetWidth();
}

utility::opt_error<unsigned int>::type UIImage::CalcHeight() const {
	BOOST_ASSERT(image);
	return image->GetHeight();
}

} // uis

} // wten
