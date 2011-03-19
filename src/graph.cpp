#include "stdafx.h"

namespace wten {

using namespace utility;

namespace {

int GetDxLibGraph(const DxLibGraphHandle& handle) {
	return reinterpret_cast<int>(handle.get());
}
void CloseDxLibGraphHandle(const void* handle) {
	const int result = ::DeleteGraph(reinterpret_cast<int>(handle));
	BOOST_ASSERT(result == 0);
}

DxLibGraphHandle IntToDxLibGraphHandle(int handle) {
	return DxLibGraphHandle(reinterpret_cast<void*>(handle), &CloseDxLibGraphHandle);
}

boost::tuple<unsigned int, unsigned int> GetGraphSize(DxLibGraphHandle handle) {
	BOOST_ASSERT(handle);
	int x,y;
	const int result = ::GetGraphSize(GetDxLibGraph(handle), &x, &y);
	BOOST_ASSERT(result != -1);
	BOOST_ASSERT(x >= 0);
	BOOST_ASSERT(y >= 0);
	return boost::make_tuple(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
}

unsigned int GetGraphWidth(DxLibGraphHandle handle) {
	return GetGraphSize(handle).get<0>();
}

unsigned int GetGraphHeight(DxLibGraphHandle handle) {
	return GetGraphSize(handle).get<1>();
}

DxLibGraphHandle GetGraphHandle(boost::shared_ptr<const std::wstring> filename) {
	BOOST_ASSERT(filename);
	BOOST_ASSERT(!filename->empty());
	const int handle = ::LoadGraph(filename->c_str());

	BOOST_ASSERT(handle != -1);
	DxLibGraphHandle result = IntToDxLibGraphHandle(handle);
	return result;
}

} // anonymous

Graph::Graph(DxLibGraphHandle handle) :
	inner_ptr(handle), width(GetGraphWidth(inner_ptr)), height(GetGraphHeight(inner_ptr))
{
	BOOST_ASSERT(handle);
	BOOST_ASSERT(width > 0);
	BOOST_ASSERT(height > 0);
}

Graph::Graph(boost::shared_ptr<const std::wstring> filename) :
	inner_ptr(GetGraphHandle(filename)), width(GetGraphWidth(inner_ptr)), height(GetGraphHeight(inner_ptr))
{
	BOOST_ASSERT(inner_ptr);
	BOOST_ASSERT(width > 0);
	BOOST_ASSERT(height > 0);
}

unsigned int Graph::GetWidth() const {
	return width;
}

unsigned int Graph::GetHeight() const {
	return height;
}

boost::optional<boost::shared_ptr<Error> > Graph::Draw(unsigned int x, unsigned int y) const {
	BOOST_ASSERT(inner_ptr);
	BOOST_ASSERT(x <= INT_MAX);
	BOOST_ASSERT(y <= INT_MAX);
	const int result = ::DrawGraph(static_cast<int>(x), static_cast<int>(y), GetDxLibGraph(inner_ptr), TRUE);
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > Graph::Draw(unsigned int x, unsigned int y, bool turn, double rate, double angle, unsigned int center_x, unsigned int center_y) const {
	BOOST_ASSERT(inner_ptr);
	BOOST_ASSERT(x <= INT_MAX);
	BOOST_ASSERT(y <= INT_MAX);
	BOOST_ASSERT(center_x <= width);
	BOOST_ASSERT(center_y <= height);
	const int result = ::DrawRotaGraph2(static_cast<int>(x), static_cast<int>(y), static_cast<int>(center_x), static_cast<int>(center_y), rate, angle, GetDxLibGraph(inner_ptr), TRUE, (turn ? TRUE : FALSE));
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

boost::optional<boost::shared_ptr<Error> > Graph::DrawEx(unsigned int x, unsigned int y, unsigned int w, unsigned int h) const {
	BOOST_ASSERT(inner_ptr);
	BOOST_ASSERT(x + w <= INT_MAX);
	BOOST_ASSERT(y + h <= INT_MAX);
	const int result = ::DrawExtendGraph(static_cast<int>(x), static_cast<int>(y), static_cast<int>(x + w), static_cast<int>(y + h), GetDxLibGraph(inner_ptr), TRUE);
	if(result == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::none;
}

opt_error<boost::shared_ptr<Graph> >::type Graph::Derivation(unsigned int x, unsigned int y, unsigned int w, unsigned int h) const {
	BOOST_ASSERT(inner_ptr);
	BOOST_ASSERT(x <= INT_MAX);
	BOOST_ASSERT(y <= INT_MAX);
	BOOST_ASSERT(w <= INT_MAX);
	BOOST_ASSERT(h <= INT_MAX);
	const int handle = ::DerivationGraph(static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h), GetDxLibGraph(inner_ptr));
	if(handle == -1) {
		return CREATE_ERROR(ERROR_CODE_DXLIB_INTERNAL_ERROR);
	}
	return boost::shared_ptr<Graph>(new Graph(IntToDxLibGraphHandle(handle)));
}

} // wten

