#include "GamePlayScene.h"

void GamePlayScene::Initialize()
{
	winApp = WindowAPI::GetInstance();
	dxCommon = DirectXCommon::GetInstance();
	engine = MyEngine::GetInstance();
	imGuiManager = ImGuiManager::GetInstance();
	texture = TextureManager::GetInstance();
	input = Input::GetInstance();

	winApp->StartApp(kWindowTitle, kWindowWidth, kWindowHeight);
	dxCommon->Initialize();
	engine->Initialize();
	input->Initialize();


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

	texture->Initialize(kWindowWidth, kWindowHeight);

	uvTexture = texture->LoadTexture("Resources/uvChecker.png");
	monsterTexture = texture->LoadTexture("Resources/monsterBall.png");

	imGuiManager->Initialize();

	transform_=
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};
	
	transform2_ =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};


	model->Initialize("Resources", "cube.Obj");
	model2->Initialize("Resources", "axis.Obj");
	sphere->Initialize(monsterTexture);
	sprite->Initialize(spriteData, uvTexture);

}

void GamePlayScene::Update()
{
	dxCommon->PreDraw();
	engine->PreDraw();
	imGuiManager->Begin();


	if (input->TriggerKey(DIK_UP))
	{
		transform_.translate.x += 0.01f;
	}

	if (input->TriggerKey(DIK_W))
	{
		transform2_.translate.x += 0.01f;
	}


	input->Update();
	model->Update(transform_);
	model2->Update(transform2_);
	sphere->Update();
	sprite->Update();

	imGuiManager->End();
}

void GamePlayScene::Draw()
{

	model->Draw();
	model2->Draw();
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
