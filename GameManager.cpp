#include "GameManager.h"

void GameManager::Initialize()
{
	winApp->StartApp(kWindowTitle);
	dxCommon->Initialize();
	engine->Initialize();
	input->Initialize();
	texture->Initialize(engine);
	uint32_t uvTexture = texture->LoadTexture("Resources/uvChecker.png");
	uint32_t monsterTexture = texture->LoadTexture("Resources/monsterBall.png");
	imGuiManager->Initialize();


	sphere->Initialize(engine, texture, uvTexture, monsterTexture);


}

void GameManager::Update()
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

void GameManager::Draw()
{

	imGuiManager->End();


	sphere->Draw();



	imGuiManager->Draw();

	engine->PostDraw();
	dxCommon->PostDraw(); 


}

void GameManager::Finalize()
{
	delete sphere;


	delete imGuiManager;
	delete input;
	delete texture;
	delete engine;
	delete dxCommon;
	delete winApp;
}
