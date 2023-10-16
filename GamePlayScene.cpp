#include "GamePlayScene.h"

void GamePlayScene::Initialize()
{
	winApp = new WindowAPI;
	dxCommon = new DirectXCommon;
	engine = new MyEngine;
	imGuiManager = new ImGuiManager;
	texture = new TextureManager;
	input = new Input;

	winApp->StartApp(kWindowTitle, kWindowWidth, kWindowHeight);
	dxCommon->Initialize(winApp);
	engine->Initialize(dxCommon, winApp);
	input->Initialize(winApp);


	spriteData = new SpriteData;
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

	uvTexture = texture->LoadTexture("Resources/uvChecker.png");
	monsterTexture = texture->LoadTexture("Resources/monsterBall.png");

	imGuiManager->Initialize(winApp, dxCommon);

	model->Initialize(winApp, dxCommon, engine, texture, "Resources", "cube.Obj");
	model2->Initialize(winApp, dxCommon, engine, texture, "Resources", "axis.Obj");
	sphere->Initialize(winApp, dxCommon, engine, texture, monsterTexture);
	sprite->Initialize(winApp, dxCommon, engine, texture, spriteData, uvTexture);

}

void GamePlayScene::Update()
{
	dxCommon->PreDraw();
	engine->PreDraw();
	imGuiManager->Begin();


	if (input->TriggerKey(DIK_0))
	{
		OutputDebugStringA("Hit\n");
	}

	input->Update();
	model->Update();
	model2->Update();
	sphere->Update();
	sprite->Update();

	imGuiManager->End();
}

void GamePlayScene::Draw()
{

	/*model->Draw();
	model2->Draw();*/
	sphere->Draw();
	sprite->Draw();

	imGuiManager->Draw();
	engine->PostDraw();
	dxCommon->PostDraw();

}

void GamePlayScene::Finalize()
{
	D3DResourceLeakChecker leakCheak;

	CoUninitialize();

	delete sphere;
	delete sprite;
	delete model;
	delete model2;

	delete spriteData;

	delete input;
	delete imGuiManager;
	delete engine;
	delete texture;
	delete dxCommon;
	delete winApp;

}
