#include "stdafx.h"

namespace wten {

using namespace utility;
using namespace boost::assign;

namespace {

std::vector<GraphImpl*> graph_list;

boost::tuple<unsigned int, unsigned int> GetGraphSize(const DxLibGraphHandle handle) {
	opt_error<boost::tuple<unsigned int, unsigned int> >::type opt_size = DxLibWrapper::GetGraphSize(handle);
	if(opt_size.which() == 0) {
		boost::shared_ptr<Error> error = boost::get<boost::shared_ptr<Error> >(opt_size);
		error->Abort();
		BOOST_ASSERT(false);
		return 0;
	}
	return boost::get<boost::tuple<unsigned int, unsigned int> >(opt_size);
}

unsigned int GetGraphWidth(const DxLibGraphHandle handle) {
	return GetGraphSize(handle).get<0>();
}

unsigned int GetGraphHeight(const DxLibGraphHandle handle) {
	return GetGraphSize(handle).get<1>();
}

} // anonymous

GraphImpl::GraphImpl(boost::shared_ptr<const std::wstring> filename) :
	filename(filename), source_filename(), x1(0), y1(0), x2(0), y2(0)
{
	BOOST_ASSERT(filename);
	BOOST_ASSERT(!filename->empty());
	BOOST_ASSERT(!source_filename);
}

GraphImpl::GraphImpl(boost::shared_ptr<const std::wstring> source_filename, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) :
	filename(), source_filename(source_filename), x1(x1), y1(y1), x2(x2), y2(y2)
{
	BOOST_ASSERT(!filename);
	BOOST_ASSERT(source_filename);
}

GraphImpl::GraphImpl(const GraphImpl& obj) :
	filename(obj.filename), source_filename(obj.source_filename), x1(obj.x1), y1(obj.y1), x2(obj.x2), y2(obj.y2)
{
	if(filename) {
		BOOST_ASSERT(!filename->empty());
		BOOST_ASSERT(!source_filename);
	} else {
		BOOST_ASSERT(source_filename);
	}
}

GraphImpl::~GraphImpl(void) {
	if(handle) {
		std::vector<GraphImpl*>::iterator it = std::find(graph_list.begin(), graph_list.end(), this);
		if(it != graph_list.end()) {
			graph_list.erase(it);
		}
		boost::optional<boost::shared_ptr<Error> > error = DxLibWrapper::DeleteGraph(handle.get());
		if(error) {
			error.get()->Abort();
			BOOST_ASSERT(false);
		}
	}
}

std::size_t GraphImpl::GetHash(void) const {
	boost::hash<std::wstring> hasher;
	wchar_t text_char[1024];
	WSPRINTF(text_char, L"%s\n%s\t%d\t%d\t%d\t%d", (filename ? filename->c_str() : L""), (source_filename ? source_filename->c_str() : L""),  x1, y1, x2, y2);
	return hasher(text_char);
}

void GraphImpl::ClearHandle(void) {
	handle = boost::none;
}

boost::shared_ptr<const std::wstring> GraphImpl::GetFilename(void) const {
	return filename;
}

DxLibGraphHandle GraphImpl::GetHandle(void) const {
	if(!handle) {
		const_cast<GraphImpl*>(this)->handle = const_cast<GraphImpl*>(this)->LoadGraph();
		graph_list.push_back(const_cast<GraphImpl*>(this));
	}
	return handle.get();
}

unsigned int GraphImpl::GetWidth(void) const {
	return GetGraphWidth(GetHandle());
}

unsigned int GraphImpl::GetHeight(void) const {
	return GetGraphHeight(GetHandle());
}

bool GraphImpl::operator==(const GraphImpl &obj) const {
	return this->filename == obj.filename && 
		this->source_filename == obj.source_filename &&
		this->x1 == obj.x1 &&
		this->y1 == obj.y1 &&
		this->x2 == obj.x2 &&
		this->y2 == obj.y2;
}

DxLibGraphHandle GraphImpl::LoadGraph() {
	opt_error<DxLibGraphHandle>::type opt_handle;
	if(filename) {
		opt_handle = DxLibWrapper::LoadGraph(filename);
	} else if(source_filename) {
		boost::flyweight<GraphImpl> source(source_filename);
		opt_handle = DxLibWrapper::DerivationGraph(source.get().GetHandle(), x1, y1, x2, y2);
	} else {
		opt_handle = CREATE_ERROR(ERROR_CODE_INTERNAL_ERROR);
	}
	if(opt_handle.which() == 0) {
		boost::shared_ptr<Error> error = boost::get<boost::shared_ptr<Error> >(opt_handle);
		error->Abort();
		BOOST_ASSERT(false);
	}
	return boost::get<DxLibGraphHandle>(opt_handle);
}


std::size_t hash_value(const GraphImpl &obj) {
	return obj.GetHash();
}

Graph::Graph(boost::shared_ptr<const std::wstring> source_filename, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) :
	boost::flyweight<GraphImpl>(source_filename, x1, y1, x2, y2)
{
}

Graph::Graph(boost::shared_ptr<const std::wstring> filename) :
	boost::flyweight<GraphImpl>(filename)
{
}

unsigned int Graph::GetWidth() const {
	return get().GetWidth();
}
unsigned int Graph::GetHeight() const {
	return get().GetHeight();
}

boost::optional<boost::shared_ptr<Error> > Graph::Draw(unsigned int x, unsigned int y) const {
	return DxLibWrapper::DrawGraph(x, y, get().GetHandle());
}

boost::optional<boost::shared_ptr<Error> > Graph::Draw(unsigned int x, unsigned int y, bool turn, double rate, double angle, unsigned int center_x, unsigned int center_y) const {
	return DxLibWrapper::DrawRotaGraph2(x, y, turn, rate, angle, center_x, center_y, get().GetHandle());
}

boost::optional<boost::shared_ptr<Error> > Graph::DrawEx(unsigned int x, unsigned int y, unsigned int w, unsigned int h) const {
	return DxLibWrapper::DrawExtendGraph(x, y, w, h, get().GetHandle());
}

utility::opt_error<boost::shared_ptr<Graph> >::type Graph::Derivation(unsigned int x, unsigned int y, unsigned int w, unsigned int h) const {
	return boost::shared_ptr<Graph>(new Graph(get().GetFilename(), x, y, w, h));
}

//static
boost::optional<boost::shared_ptr<Error> > Graph::AllGraphReload(void) {
	OPT_ERROR(DxLibWrapper::InitGraph());
	BOOST_FOREACH(GraphImpl *handle, graph_list) {
		BOOST_ASSERT(handle);
		handle->ClearHandle();
	}
	graph_list.clear();
	return boost::none;
}

} // wten
