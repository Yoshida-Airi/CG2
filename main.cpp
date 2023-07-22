#include<Windows.h>
#include"WindowAPI.h"
#include"DirectX.h"
#include"Engine.h"

#include"Triangle.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	WindowAPI* window = new WindowAPI;
	DirectX* direct = new DirectX;
	Engine* engine = new Engine;

	Vector4 data1[3];
	Vector4 data2[3];
	Vector4 data3[3];



	for (int i = 0; i < 3; i++)
	{

		data1[i] = { -0.2f,-0.2f + (i * -0.5f),0.0f,2.0f };
		data2[i] = { 0.0f,0.2f + (i * -0.5f),0.0f,2.0f };
		data3[i] = { 0.2f,-0.2f + (i * -0.5f),0.0f,2.0f };
	}


	//アプリケーションの開始
	window->StartApp();
	direct->Initialize(window->GetHwnd());

	for (int i = 0; i < 3; i++)
	{
		//三角形描画
		engine->Initialize(data1[i], data2[i], data3[i]);
	}

	/*=====================================*/
	/* 　　　　   メインループ　　    　       */
	/*=====================================*/

	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		//Windowsにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			engine->Run();


				//三角形描画
				engine->DrawTriangle();


			engine->RunEnd();

		}
	}

	window->EndApp();
	engine->End();
	direct->End();




	return 0;

}