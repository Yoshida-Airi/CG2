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
	Sprite* sprite;
	Sphere* sphere;


	sprite = new Sprite;
	sphere = new Sphere;

	
	spriteData->vertex[0] = { 0.0f,360.0f,0.0f,1.0f };
	spriteData->vertex[1] = { 0.0f,0.0f,0.0f,1.0f };
	spriteData->vertex[2] = { 640.0f,360.0f,0.0f,1.0f };
	spriteData->vertex[3] = { 0.0f,0.0f,0.0f,1.0f };
	spriteData->vertex[4] = { 640.0f,0.0f,0.0f,1.0f };
	spriteData->vertex[5] = { 640.0f,360.0f,0.0f,1.0f };

	spriteData->transform =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	CoInitializeEx(0, COINIT_MULTITHREADED);

	texture->Initialize(dxCommon, kWindowWidth, kWindowHeight);

	imGuiManager->Initialize(winApp, dxCommon);



	

	sprite->Initialize(winApp, dxCommon, engine, texture, spriteData);

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
		sprite->Update();


	

		imGuiManager->End();

		

		sphere->Draw();
		sprite->Draw();
		

		imGuiManager->Draw();
		engine->PostDraw();
		dxCommon->PostDraw();


	}

	CoUninitialize();



	delete sphere;
	delete sprite;
	delete texture;
	delete imGuiManager;
	delete engine;
	delete dxCommon;
	delete winApp;

	return 0;
}