#include "GamePlayScene.h"


void GamePlayScene::Initialize()
{
	winApp->StartApp(kWindowTitle);
	dxCommon->Initialize();
	engine->Initialize();
	input->Initialize();
	texture->Initialize();
	uvTexture = texture->LoadTexture("Resources/uvChecker.png");
	monsterTexture = texture->LoadTexture("Resources/monsterBall.png");
	imGuiManager->Initialize();


	sphere->Initialize();


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


	sphere->Update();

}

void GamePlayScene::Draw()
{

	imGuiManager->End();


	sphere->Draw(uvTexture);



	imGuiManager->Draw();

	engine->PostDraw();
	dxCommon->PostDraw();


}

void GamePlayScene::Finalize()
{
	delete sphere;


	delete imGuiManager;
	delete input;
	delete texture;
	delete engine;
	delete dxCommon;
	delete winApp;
}
