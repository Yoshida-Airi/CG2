#include<Windows.h>
#include"WindowAPI.h"
#include"DirectXCommon.h"
#include"MyEngine.h"
#include"Triangle.h"
#include"ImGuiManager.h"
#include"TextureManager.h"
#include"Sprite.h"


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

	const int KmaxTriangle = 2;

	TriangleData triangleData[KmaxTriangle];
	Triangle* triangle[KmaxTriangle];

	SpriteData spriteData;
	Sprite* sprite;

	for (int i = 0; i < KmaxTriangle; i++)
	{
		triangle[i] = new Triangle;
	}

	sprite = new Sprite;

	triangleData[0].vertex[0] = { -0.5f,-0.5f,0.0f,1.0f };
	triangleData[0].vertex[1] = { 0.0f,0.5f,0.0f,1.0f };
	triangleData[0].vertex[2] = { 0.5f,-0.5f,0.0f,1.0f };

	triangleData[1].vertex[0] = { -0.5f,-0.5f,0.5f,1.0f };
	triangleData[1].vertex[1] = { 0.0f,0.0f,0.0f,1.0f };
	triangleData[1].vertex[2] = { 0.5f,-0.5f,-0.5f,1.0f };


	for (int i = 0; i < KmaxTriangle; i++)
	{
		//色
		triangleData[i].color = { 1.0f,1.0f,1.0f,1.0f };
	}

	for (int i = 0; i < KmaxTriangle; i++)
	{
		triangleData[i].transform =
		{
			{1.0f, 1.0f, 1.0f},
			{ 0.0f,0.0f,0.0f },
			{ 0.0f,0.0f,0.0f }
		};
	}

	spriteData.vertex[0] = { 0.0f,360.0f,0.0f,1.0f };
	spriteData.vertex[1] = { 0.0f,0.0f,0.0f,1.0f };
	spriteData.vertex[2] = { 640.0f,360.0f,0.0f,1.0f };
	spriteData.vertex[3] = { 0.0f,0.0f,0.0f,1.0f };
	spriteData.vertex[4] = { 640.0f,0.0f,0.0f,1.0f };
	spriteData.vertex[5] = { 640.0f,360.0f,0.0f,1.0f };

	spriteData.transform =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	CoInitializeEx(0, COINIT_MULTITHREADED);

	texture->Initialize(dxCommon, kWindowWidth, kWindowHeight);

	imGuiManager->Initialize(winApp, dxCommon);



	for (int i = 0; i < KmaxTriangle; i++)
	{
		triangle[i]->Initialize(winApp, dxCommon, engine, triangleData[i], texture);
	}

	sprite->Initialize(winApp, dxCommon, engine, spriteData);

	// ウィンドウの×ボタンが押されるまでループ
	while (WindowAPI::ProcessMessage() == 0)
	{

		/*=====================================*/
		/* 　　　　   メインループ　　    　       */
		/*=====================================*/

		dxCommon->PreDraw();
		engine->PreDraw();
		imGuiManager->Begin();

		for (int i = 0; i < KmaxTriangle; i++)
		{
			triangle[i]->Update();
		}

		sprite->Update();



		imGuiManager->End();

		for (int i = 0; i < KmaxTriangle; i++)
		{
			triangle[i]->Draw();
		}

		sprite->Draw();

		imGuiManager->Draw();
		engine->PostDraw();
		dxCommon->PostDraw();


	}

	CoUninitialize();

	for (int i = 0; i < KmaxTriangle; i++)
	{
		delete triangle[i];
	}

	delete sprite;

	delete texture;
	delete imGuiManager;
	delete engine;
	delete dxCommon;
	delete winApp;

	return 0;
}