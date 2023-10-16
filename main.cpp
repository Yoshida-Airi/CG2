#include"GameManager.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	GameManager* scene = new GameManager;

	scene->Initialize();

	// ウィンドウの×ボタンが押されるまでループ
	while (WindowAPI::ProcessMessage() == 0)
	{

		scene->Update();

		scene->Draw();

	}

	scene->Finalize();
	
	return 0;
}