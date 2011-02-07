#include "stdafx.h"

namespace wten {

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

} // anonymous

Graph::Graph(const DxLibGraphHandle& handle) :
	inner_ptr(handle)
{
	boost::optional<boost::tuple<int, int>> size = GetSize();
	BOOST_ASSERT(size);

	boost::tie(width, height) = size.get();
}

boost::optional<boost::tuple<int, int>> Graph::GetSize(void) {
	if(!inner_ptr) {
		return boost::none;
	}
	int x,y;
	const int result = ::GetGraphSize(GetDxLibGraph(inner_ptr), &x, &y);
	if(result == -1) {
		return boost::none;
	}
	return boost::make_tuple(x, y);
}

Graph::Graph(const TCHAR* filename) {
	BOOST_ASSERT(filename != NULL);
	const int handle = ::LoadGraph(filename);

	BOOST_ASSERT(handle != -1);
	inner_ptr = IntToDxLibGraphHandle(handle);

	boost::optional<boost::tuple<int, int>> size = GetSize();
	BOOST_ASSERT(size);

	boost::tie(width, height) = size.get();
}

unsigned int Graph::GetWidth() {
	return width;
}

unsigned int Graph::GetHeight() {
	return height;
}

bool Graph::Draw(unsigned int x, unsigned int y) {
	if(!inner_ptr) {
		return false;
	}
	return (::DrawGraph(x, y, GetDxLibGraph(inner_ptr), TRUE) != -1);
}

bool Graph::DrawEx(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	if(!inner_ptr) {
		return false;
	}
	return (::DrawExtendGraph(x, y, x + w, y + h, GetDxLibGraph(inner_ptr), TRUE) != -1);
}

boost::optional<boost::shared_ptr<Graph>> Graph::Derivation(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	if(!inner_ptr) {
		return boost::none;
	}
	const int handle = ::DerivationGraph(x, y, w, h, GetDxLibGraph(inner_ptr));
	if(handle == -1) {
		return boost::none;
	}
	return boost::shared_ptr<Graph>(new Graph(IntToDxLibGraphHandle(handle)));
}

} // wten

