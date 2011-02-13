#include "stdafx.h"

using namespace wten;

//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ){
int main() {
	::setlocale(LC_ALL, _T(""));

	boost::shared_ptr<WTen> game;
	{
		boost::shared_ptr<Scene> scene = scenes::SceneBase::CreateScene();
		game.reset(new WTen(scene));
	}
	boost::optional<boost::shared_ptr<Error> > result = game->DoStart();
	game.reset();
	if(result) {
		result.get()->Abort();
		return 1;
	}

	return 0;
}

