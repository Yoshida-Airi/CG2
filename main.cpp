#include<Windows.h>
#include"WindowAPI.h"
#include"DirectXCommon.h"
#include"MyEngine.h"

const wchar_t* kWindowTitle = L"CG2";

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	WindowAPI* winApp = new WindowAPI;
	DirectXCommon* dxCommon = new DirectXCommon;
	MyEngine* engine = new MyEngine;

	//アプリケーションの開始
	const uint32_t kWindowWidth = 1280;
	const uint32_t kWindowHeight = 720;

	winApp->StartApp(kWindowTitle, kWindowWidth, kWindowHeight);
	dxCommon->Initialize(winApp);
	engine->Initialize(dxCommon, winApp);

	const int kMaxTriangle = 10;


	Vector4 data[kMaxTriangle][kMaxTriangle] = { 0 };
	ID3D12Resource* resource[kMaxTriangle] = { nullptr };



	for (int i = 0; i < kMaxTriangle; i++)
	{
		resource[i] = engine->VertexResource();
	}

	data[0][0] = { -0.2f,-0.2f,0.0f,2.0f };
	data[0][1] = { 0.0f,0.2f,0.0f,2.0f };
	data[0][2] = { 0.2f,-0.2f,0.0f,2.0f };

	data[1][0] = { 0.2f,-0.2f ,0.0f,2.0f };
	data[1][1] = { 0.4f,0.2f ,0.0f,2.0f };
	data[1][2] = { 0.6f,-0.2f ,0.0f,2.0f };

	data[2][0] = { 0.6f,-0.2f,0.0f,2.0f };
	data[2][1] = { 0.8f,0.2f,0.0f,2.0f };
	data[2][2] = { 1.0f,-0.2f,0.0f,2.0f };

	data[3][0] = { 1.0f,-0.2f,0.0f,2.0f };
	data[3][1] = { 1.2f,0.2f,0.0f,2.0f };
	data[3][2] = { 1.4f,-0.2f,0.0f,2.0f };

	data[4][0] = { -0.2f,-0.7f,0.0f,2.0f };
	data[4][1] = { 0.0f,-0.3f,0.0f,2.0f };
	data[4][2] = { 0.2f,-0.7f,0.0f,2.0f };

	data[5][0] = { 0.2f,-0.7f,0.0f,2.0f };
	data[5][1] = { 0.4f,-0.3f,0.0f,2.0f };
	data[5][2] = { 0.6f,-0.7f,0.0f,2.0f };

	data[6][0] = { 0.6f,-0.7f,0.0f,2.0f };
	data[6][1] = { 0.8f,-0.3f,0.0f,2.0f };
	data[6][2] = { 1.0f,-0.7f,0.0f,2.0f };

	data[7][0] = { 1.0f,-0.7f,0.0f,2.0f };
	data[7][1] = { 1.2f,-0.3f,0.0f,2.0f };
	data[7][2] = { 1.4f,-0.7f,0.0f,2.0f };

	data[8][0] = { -0.2f,0.3f,0.0f,2.0f };
	data[8][1] = { 0.0f,0.7f,0.0f,2.0f };
	data[8][2] = { 0.2f,0.3f,0.0f,2.0f };

	data[9][0] = { 0.2f,0.3f,0.0f,2.0f };
	data[9][1] = { 0.4f,0.7f,0.0f,2.0f };
	data[9][2] = { 0.6f,0.3f,0.0f,2.0f };

	// ウィンドウの×ボタンが押されるまでループ
	while (WindowAPI::ProcessMessage() == 0)
	{

		/*=====================================*/
		/* 　　　　   メインループ　　    　       */
		/*=====================================*/

		dxCommon->PreDraw();
		engine->PreDraw();

		for (int i = 0; i < kMaxTriangle; i++)
		{
			engine->DrawTriangle(data[i], resource[i]);
		}

		engine->PostDraw();
		dxCommon->PostDraw();


	}

	for (int i = 0; i < kMaxTriangle; i++)
	{
		resource[i]->Release();
	}


	delete engine;
	delete dxCommon;
	delete winApp;

	return 0;
}