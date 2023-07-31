#include<Windows.h>
#include"WindowAPI.h"
#include"DirectXCommon.h"
#include"MyEngine.h"
#include"Triangle.h"
#include"ImGuiManager.h"

const wchar_t* kWindowTitle = L"CG2";

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	WindowAPI* winApp = new WindowAPI;
	DirectXCommon* dxCommon = new DirectXCommon;
	MyEngine* engine = new MyEngine;
	ImGuiManager* imGuiManager = new ImGuiManager;

	//アプリケーションの開始
	const uint32_t kWindowWidth = 1280;
	const uint32_t kWindowHeight = 720;

	winApp->StartApp(kWindowTitle, kWindowWidth, kWindowHeight);
	dxCommon->Initialize(winApp);
	engine->Initialize(dxCommon, winApp);

	const int KmaxTriangle = 3;

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


	triangleData[1].vertex[0] = { -0.2f,-0.7f,0.0f,2.0f };
	triangleData[1].vertex[1] = { 0.0f,-0.3f,0.0f,2.0f };
	triangleData[1].vertex[2] = { 0.2f,-0.7f,0.0f,2.0f };


	triangleData[2].vertex[0] = { -0.2f,0.3f,0.0f,2.0f };
	triangleData[2].vertex[1] = { 0.0f,0.7f,0.0f,2.0f };
	triangleData[2].vertex[2] = { 0.2f,0.3f,0.0f,2.0f };

	//triangleData[3].vertex[0] = { 0.2f,-0.2f ,0.0f,2.0f };
	//triangleData[3].vertex[1] = { 0.4f,0.2f ,0.0f,2.0f };
	//triangleData[3].vertex[2] = { 0.6f,-0.2f ,0.0f,2.0f };


	//triangleData[4].vertex[0] = { 0.2f,-0.7f,0.0f,2.0f };
	//triangleData[4].vertex[1] = { 0.4f,-0.3f,0.0f,2.0f };
	//triangleData[4].vertex[2] = { 0.6f,-0.7f,0.0f,2.0f };


	//triangleData[5].vertex[0] = { 0.2f,0.3f,0.0f,2.0f };
	//triangleData[5].vertex[1] = { 0.4f,0.7f,0.0f,2.0f };
	//triangleData[5].vertex[2] = { 0.6f,0.3f,0.0f,2.0f };

	//triangleData[6].vertex[0] = { 0.6f,-0.2f,0.0f,2.0f };
	//triangleData[6].vertex[1] = { 0.8f,0.2f,0.0f,2.0f };
	//triangleData[6].vertex[2] = { 1.0f,-0.2f,0.0f,2.0f };


	//triangleData[7].vertex[0] = { 0.6f,-0.7f,0.0f,2.0f };
	//triangleData[7].vertex[1] = { 0.8f,-0.3f,0.0f,2.0f };
	//triangleData[7].vertex[2] = { 1.0f,-0.7f,0.0f,2.0f };

	//triangleData[8].vertex[0] = { 1.0f,-0.2f,0.0f,2.0f };
	//triangleData[8].vertex[1] = { 1.2f,0.2f,0.0f,2.0f };
	//triangleData[8].vertex[2] = { 1.4f,-0.2f,0.0f,2.0f };


	//triangleData[9].vertex[0] = { 1.0f,-0.7f,0.0f,2.0f };
	//triangleData[9].vertex[1] = { 1.2f,-0.3f,0.0f,2.0f };
	//triangleData[9].vertex[2] = { 1.4f,-0.7f,0.0f,2.0f };


	for (int i = 0; i < KmaxTriangle; i++)
	{
		//色
		triangleData[i].color = { 1.0f,0.0f,0.0f,1.0f };
	}

	for (int i = 0; i < KmaxTriangle; i++)
	{
		triangleData[i].transform =
		{
			{2.0f, 2.0f, 2.0f},
			{ 0.0f,0.0f,0.0f },
			{ 0.0f,0.0f,0.0f }
		};
	}

	for (int i = 0; i < KmaxTriangle; i++)
	{
		triangle[i]->Initialize(winApp, dxCommon, engine);
	}

	imGuiManager->Initialize(winApp, dxCommon);

	bool isRotate1 = false;
	bool isRotate2 = false;
	bool isRotate3 = false;


	// ウィンドウの×ボタンが押されるまでループ
	while (WindowAPI::ProcessMessage() == 0)
	{

		/*=====================================*/
		/* 　　　　   メインループ　　    　       */
		/*=====================================*/

		dxCommon->PreDraw();
		engine->PreDraw();
		imGuiManager->Begin();

		ImGui::Begin("Setting");
	
		

		ImGui::End();


		ImGui::Begin("triangle2");

		float color[] = { triangleData[0].color.x,triangleData[0].color.y,triangleData[0].color.z,triangleData[0].color.z };

		ImGui::ColorEdit4("color", color);


		triangleData[0].color.x = color[0];
		triangleData[0].color.y = color[1];
		triangleData[0].color.z = color[2];
		triangleData[0].color.w = color[3];

		float translate[] = { triangleData[0].transform.translate.x,triangleData[0].transform.translate.y,triangleData[0].transform.translate.z };

		ImGui::SliderFloat3("translate", translate, -1.0f, 1.0f);

		triangleData[0].transform.translate.x = translate[0];
		triangleData[0].transform.translate.y = translate[1];
		triangleData[0].transform.translate.z = translate[2];


		float scale[] = { triangleData[0].transform.scale.x,triangleData[0].transform.scale.y,triangleData[0].transform.scale.z };


		ImGui::SliderFloat3("scale", scale, 0.0f, 5.0f);

		triangleData[0].transform.scale.x = scale[0];
		triangleData[0].transform.scale.y = scale[1];
		triangleData[0].transform.scale.z = scale[2];

		float rotate[] = { triangleData[0].transform.rotate.x,triangleData[0].transform.rotate.y,triangleData[0].transform.rotate.z };

		ImGui::SliderFloat3("rotate", rotate, -1.0f, 1.0f);

		triangleData[0].transform.rotate.x = rotate[0];
		triangleData[0].transform.rotate.y = rotate[1];
		triangleData[0].transform.rotate.z = rotate[2];


		ImGui::End();



		ImGui::Begin("triangle3");

		float color2[] = { triangleData[1].color.x,triangleData[1].color.y,triangleData[1].color.z,triangleData[1].color.z };

		ImGui::ColorEdit4("color", color2);


		triangleData[1].color.x = color2[0];
		triangleData[1].color.y = color2[1];
		triangleData[1].color.z = color2[2];
		triangleData[1].color.w = color2[3];

		float translate2[] = { triangleData[1].transform.translate.x,triangleData[1].transform.translate.y,triangleData[1].transform.translate.z };

		ImGui::SliderFloat3("translate", translate2, -1.0f, 1.0f);

		triangleData[1].transform.translate.x = translate2[0];
		triangleData[1].transform.translate.y = translate2[1];
		triangleData[1].transform.translate.z = translate2[2];


		float scale2[] = { triangleData[1].transform.scale.x,triangleData[1].transform.scale.y,triangleData[1].transform.scale.z };


		ImGui::SliderFloat3("scale", scale2, 0.0f, 5.0f);

		triangleData[1].transform.scale.x = scale2[0];
		triangleData[1].transform.scale.y = scale2[1];
		triangleData[1].transform.scale.z = scale2[2];

		float rotate2[] = { triangleData[1].transform.rotate.x,triangleData[1].transform.rotate.y,triangleData[1].transform.rotate.z };

		ImGui::SliderFloat3("rotate", rotate2, -1.0f, 1.0f);

		triangleData[1].transform.rotate.x = rotate2[0];
		triangleData[1].transform.rotate.y = rotate2[1];
		triangleData[1].transform.rotate.z = rotate2[2];


		ImGui::End();

		ImGui::Begin("triangle1");

		float color3[] = { triangleData[2].color.x,triangleData[2].color.y,triangleData[2].color.z,triangleData[2].color.z };

		ImGui::ColorEdit4("color", color3);


		triangleData[2].color.x = color3[0];
		triangleData[2].color.y = color3[1];
		triangleData[2].color.z = color3[2];
		triangleData[2].color.w = color3[3];

		float translate3[] = { triangleData[2].transform.translate.x,triangleData[2].transform.translate.y,triangleData[2].transform.translate.z };

		ImGui::SliderFloat3("translate", translate3, -1.0f, 1.0f);

		triangleData[2].transform.translate.x = translate3[0];
		triangleData[2].transform.translate.y = translate3[1];
		triangleData[2].transform.translate.z = translate3[2];


		float scale3[] = { triangleData[2].transform.scale.x,triangleData[2].transform.scale.y,triangleData[2].transform.scale.z };


		ImGui::SliderFloat3("scale", scale3, 0.0f, 5.0f);

		triangleData[2].transform.scale.x = scale3[0];
		triangleData[2].transform.scale.y = scale3[1];
		triangleData[2].transform.scale.z = scale3[2];

		float rotate3[] = { triangleData[2].transform.rotate.x,triangleData[2].transform.rotate.y,triangleData[2].transform.rotate.z };

		ImGui::SliderFloat3("rotate", rotate3, -1.0f, 1.0f);

		triangleData[2].transform.rotate.x = rotate3[0];
		triangleData[2].transform.rotate.y = rotate3[1];
		triangleData[2].transform.rotate.z = rotate3[2];


		ImGui::End();


		

		ImGui::Begin("Rotate");

		ImGui::Checkbox("triangle1", &isRotate1);
		ImGui::Checkbox("triangle2", &isRotate2);
		ImGui::Checkbox("triangle3", &isRotate3);

		ImGui::End();



		if (isRotate1 == true)
		{
			triangleData[2].transform.rotate.y += 0.03f;
		}

		if (isRotate2 == true)
		{
			triangleData[0].transform.rotate.y += 0.03f;
		}

		if (isRotate3 == true)
		{
			triangleData[1].transform.rotate.y += 0.03f;
		}

		for (int i = 0; i < KmaxTriangle; i++)
		{

			triangle[i]->Update(triangleData[i]);

		}

		
	


		for (int i = 0; i < KmaxTriangle; i++)
		{
			

			triangle[i]->Draw();
		}

		imGuiManager->End();
		imGuiManager->Draw();
		engine->PostDraw();
		dxCommon->PostDraw();


	}

	for (int i = 0; i < KmaxTriangle; i++)
	{
		delete triangle[i];
	}

	delete imGuiManager;
	delete engine;
	delete dxCommon;
	delete winApp;

	return 0;
}