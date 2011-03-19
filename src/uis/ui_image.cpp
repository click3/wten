#include "stdafx.h"

namespace wten { namespace uis {

using namespace utility;

UIImage::UIImage(boost::shared_ptr<const std::wstring> filename) :
	image(new Graph(filename))
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
	image(image)
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

boost::optional<boost::shared_ptr<Error> > UIImage::Draw(void) {
	return UIBase::Draw();
}

boost::optional<boost::shared_ptr<Error> > UIImage::Draw(unsigned int abs_x, unsigned int abs_y) {
	BOOST_ASSERT(image);
	boost::optional<boost::shared_ptr<Error> > error = image->Draw(abs_x, abs_y);
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
