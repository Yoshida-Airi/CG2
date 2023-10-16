#include "TitleScene.h"

void TitleScene::Initialize()
{
	winApp->StartApp(kWindowTitle);
	dxCommon->Initialize();
	engine->Initialize();
	input->Initialize();
	texture->Initialize();
	uvTexture = texture->LoadTexture("Resources/uvChecker.png");
	monsterTexture = texture->LoadTexture("Resources/monsterBall.png");
	imGuiManager->Initialize();

	SpriteData* spriteData = new SpriteData;
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


	sphere->Initialize();
	sprite->Initialize(spriteData, monsterTexture);



}

void TitleScene::Update()
{
	dxCommon->PreDraw();
	engine->PreDraw();
	imGuiManager->Begin();

	if (input->TriggerKey(DIK_0))
	{
		OutputDebugStringA("Hit\n");
	}

	input->Update();


	sphere->Update();
	sprite->Update();
}

void TitleScene::Draw()
{

	imGuiManager->End();


	sphere->Draw(uvTexture);
	sprite->Draw();


	imGuiManager->Draw();

	engine->PostDraw();
	dxCommon->PostDraw();


}

void TitleScene::Finalize()
{
	delete sphere;
	delete sprite;

	delete imGuiManager;
	delete input;
	delete texture;
	delete engine;
	delete dxCommon;
	delete winApp;
}
