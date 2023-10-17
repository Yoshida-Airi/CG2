#include "GameManager.h"

void GameManager::Initialize()
{
	gameScene = new GamePlayScene;
	gameScene->Initialize();
}

void GameManager::Update()
{
	gameScene->Update();
}

void GameManager::Draw()
{
	gameScene->Draw();
}

void GameManager::Finalize()
{
	gameScene->Finalize();
}
