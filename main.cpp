#include<Windows.h>
#include"WindowAPI.h"
#include"DirectXCommon.h"
#include"MyEngine.h"
#include"Triangle.h"

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



	const int KmaxTriangle = 10;

	TriangleData triangleData[KmaxTriangle];
	Triangle* triangle[KmaxTriangle];

	for (int i = 0; i < KmaxTriangle; i++)
	{
		triangle[i] = new Triangle;
	}

	//頂点
	triangleData[0].vertex[0] = { -0.2f,-0.2f,0.0f,2.0f };
	triangleData[0].vertex[1] = { 0.0f,0.2f,0.0f,2.0f };
	triangleData[0].vertex[2] = { 0.2f,-0.2f,0.0f,2.0f };

	triangleData[1].vertex[0] = { 0.2f,-0.2f ,0.0f,2.0f };
	triangleData[1].vertex[1] = { 0.4f,0.2f ,0.0f,2.0f };
	triangleData[1].vertex[2] = { 0.6f,-0.2f ,0.0f,2.0f };

	triangleData[2].vertex[0] = { 0.6f,-0.2f,0.0f,2.0f };
	triangleData[2].vertex[1] = { 0.8f,0.2f,0.0f,2.0f };
	triangleData[2].vertex[2] = { 1.0f,-0.2f,0.0f,2.0f };

	triangleData[3].vertex[0] = { 1.0f,-0.2f,0.0f,2.0f };
	triangleData[3].vertex[1] = { 1.2f,0.2f,0.0f,2.0f };
	triangleData[3].vertex[2] = { 1.4f,-0.2f,0.0f,2.0f };

	triangleData[4].vertex[0] = { -0.2f,-0.7f,0.0f,2.0f };
	triangleData[4].vertex[1] = { 0.0f,-0.3f,0.0f,2.0f };
	triangleData[4].vertex[2] = { 0.2f,-0.7f,0.0f,2.0f };

	triangleData[5].vertex[0] = { 0.2f,-0.7f,0.0f,2.0f };
	triangleData[5].vertex[1] = { 0.4f,-0.3f,0.0f,2.0f };
	triangleData[5].vertex[2] = { 0.6f,-0.7f,0.0f,2.0f };

	triangleData[6].vertex[0] = { 0.6f,-0.7f,0.0f,2.0f };
	triangleData[6].vertex[1] = { 0.8f,-0.3f,0.0f,2.0f };
	triangleData[6].vertex[2] = { 1.0f,-0.7f,0.0f,2.0f };

	triangleData[7].vertex[0] = { 1.0f,-0.7f,0.0f,2.0f };
	triangleData[7].vertex[1] = { 1.2f,-0.3f,0.0f,2.0f };
	triangleData[7].vertex[2] = { 1.4f,-0.7f,0.0f,2.0f };

	triangleData[8].vertex[0] = { -0.2f,0.3f,0.0f,2.0f };
	triangleData[8].vertex[1] = { 0.0f,0.7f,0.0f,2.0f };
	triangleData[8].vertex[2] = { 0.2f,0.3f,0.0f,2.0f };

	triangleData[9].vertex[0] = { 0.2f,0.3f,0.0f,2.0f };
	triangleData[9].vertex[1] = { 0.4f,0.7f,0.0f,2.0f };
	triangleData[9].vertex[2] = { 0.6f,0.3f,0.0f,2.0f };

	for (int i = 0; i < KmaxTriangle; i++)
	{
		//色
		triangleData[i].color = { 1.0f,0.0f,0.0f,1.0f };
	}



	for (int i = 0; i < KmaxTriangle; i++)
	{
		triangle[i]->Initialize(dxCommon, engine, triangleData[i]);
	}




	// ウィンドウの×ボタンが押されるまでループ
	while (WindowAPI::ProcessMessage() == 0)
	{

		/*=====================================*/
		/* 　　　　   メインループ　　    　       */
		/*=====================================*/

		dxCommon->PreDraw();
		engine->PreDraw();


		for (int i = 0; i < KmaxTriangle; i++)
		{
			triangle[i]->Draw();
		}

		engine->PostDraw();
		dxCommon->PostDraw();


	}

	for (int i = 0; i < KmaxTriangle; i++)
	{
		delete triangle[i];
	}
	delete engine;
	delete dxCommon;
	delete winApp;

	return 0;
}