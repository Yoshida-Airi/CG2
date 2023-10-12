#include<Windows.h>
#include"WindowAPI.h"
#include"DirectXCommon.h"
#include"MyEngine.h"
#include"Triangle.h"
#include"ImGuiManager.h"
#include"TextureManager.h"
#include"Sprite.h"
#include"Sphere.h"
#include"Model.h"

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
	Sprite* sprite;
	Model* model;
	Model* model2;

	sphere = new Sphere;
	sprite = new Sprite;
	model = new Model;
	model2 = new Model;
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

	texture->Initialize(dxCommon, engine, kWindowWidth, kWindowHeight);

	uint32_t uvTexture= texture->LoadTexture("Resources/uvChecker.png");
	uint32_t monsterTexture = texture->LoadTexture("Resources/monsterBall.png");

	imGuiManager->Initialize(winApp, dxCommon);

	model->Initialize(winApp, dxCommon, engine, texture, "Resources", "cube.Obj");
	model2->Initialize(winApp, dxCommon, engine, texture, "Resources", "plane.Obj");
	sphere->Initialize(winApp, dxCommon, engine, texture, uvTexture,monsterTexture);
	sprite->Initialize(winApp, dxCommon, engine, texture, spriteData, uvTexture);
	
	

	// ウィンドウの×ボタンが押されるまでループ
	while (WindowAPI::ProcessMessage() == 0)
	{

		/*=====================================*/
		/* 　　　　   メインループ　　    　       */
		/*=====================================*/

		dxCommon->PreDraw();
		engine->PreDraw();
		imGuiManager->Begin();


		model->Update();
		model2->Update();
		sphere->Update();
		sprite->Update();
		
		imGuiManager->End();

		
		/*model->Draw();*/
		model2->Draw();
		sphere->Draw();
		sprite->Draw();
		
		imGuiManager->Draw();
		engine->PostDraw();
		dxCommon->PostDraw();


	}

	CoUninitialize();


	delete sphere;
	delete sprite;
	delete model;
	delete model2;

	delete spriteData;

	delete texture;
	delete imGuiManager;
	delete engine;
	delete dxCommon;
	delete winApp;

	return 0;
}