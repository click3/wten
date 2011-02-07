#include "stdafx.h"

#include <stdio.h>

using namespace wten;

//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ){
int main() {
	boost::shared_ptr<WTen> game;
	{
		boost::shared_ptr<Scene> scene(reinterpret_cast<Scene*>(new scenes::DebugScene()));
		game.reset(new WTen(scene));
	}
	boost::optional<boost::shared_ptr<Error> > result = game->DoStart();
	if(result) {
		result.get()->Abort();
		return 1;
	}

	return 0;
}

