#include<Windows.h>
#include"WindowAPI.h"
#include"DirectXCommon.h"
#include"MyEngine.h"
#include"Triangle.h"
#include"ImGuiManager.h"
#include"TextureManager.h"
#include"Sprite.h"
#include"Sphere.h"

const wchar_t* kWindowTitle = L"CG2";

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	WindowAPI* winApp = new WindowAPI;
	DirectXCommon* dxCommon = new DirectXCommon;
	MyEngine* engine = new MyEngine;
	ImGuiManager* imGuiManager = new ImGuiManager;
	TextureManager* texture = new TextureManager;


	//アプリケーションの開始
	const uint32_t kWindowWidth = 1280;
	const uint32_t kWindowHeight = 720;

	winApp->StartApp(kWindowTitle, kWindowWidth, kWindowHeight);
	dxCommon->Initialize(winApp);
	engine->Initialize(dxCommon, winApp);

	
	SpriteData* spriteData = new SpriteData;
	Sphere* sphere;



	sphere = new Sphere;

	
	
	CoInitializeEx(0, COINIT_MULTITHREADED);

	texture->Initialize(dxCommon, kWindowWidth, kWindowHeight);

	imGuiManager->Initialize(winApp, dxCommon);


	sphere->Initialize(winApp, dxCommon, engine,texture);

	// ウィンドウの×ボタンが押されるまでループ
	while (WindowAPI::ProcessMessage() == 0)
	{

		/*=====================================*/
		/* 　　　　   メインループ　　    　       */
		/*=====================================*/

		dxCommon->PreDraw();
		engine->PreDraw();
		imGuiManager->Begin();



		sphere->Update();
		
		imGuiManager->End();

		

		sphere->Draw();
	
		imGuiManager->Draw();
		engine->PostDraw();
		dxCommon->PostDraw();


	}

	CoUninitialize();



	delete sphere;
	delete texture;
	delete imGuiManager;
	delete engine;
	delete dxCommon;
	delete winApp;

	return 0;
}