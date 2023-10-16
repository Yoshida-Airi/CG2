#include"GameManager.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	GameManager* game = new GameManager;
	game->Initialize();
	// ウィンドウの×ボタンが押されるまでループ
	while (WindowAPI::ProcessMessage() == 0)
	{
		game->Update();
		game->Draw();
	}
	game->Finalize();
}