#include "GameManager.h"

void GameManager::Initialize()
{
	winApp->StartApp(kWindowTitle);
	dxCommon->Initialize(winApp);
}

void GameManager::Update()
{
	dxCommon->PreDraw();
}

void GameManager::Draw()
{
	dxCommon->PostDraw(); 
}

void GameManager::Finalize()
{
	delete dxCommon;
	delete winApp;
}
