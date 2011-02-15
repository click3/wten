#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

UIImage::UIImage(const boost::shared_ptr<std::string>& filename) :
	UIBase()
{
	BOOST_ASSERT(filename);
	BOOST_ASSERT(!filename->empty());

	image.reset(new Graph(filename));
	BOOST_ASSERT(image);

	boost::optional<boost::shared_ptr<Error> > error = Resize(image->GetWidth(), image->GetHeight());
	if(error) {
		error.get()->Abort();
		BOOST_ASSERT(false);
	}
}

UIImage::~UIImage() {
}

boost::optional<boost::shared_ptr<Error> > UIImage::Draw(void) {
	return UIBase::Draw();
}

boost::optional<boost::shared_ptr<Error> > UIImage::Draw(unsigned int abs_x, unsigned int abs_y) {
	if(!image) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	boost::optional<boost::shared_ptr<Error> > error = image->Draw(abs_x, abs_y);
	if(error) {
		return error.get();
	}
	return boost::none;
}

utility::opt_error<unsigned int>::type UIImage::CalcWidth() {
	if(!image) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return image->GetWidth();
}

utility::opt_error<unsigned int>::type UIImage::CalcHeight() {
	if(!image) {
		return CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	return image->GetHeight();
}

} // uis

} // wten
