#include "GameManager.h"

void GameManager::Initialize()
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

	CoInitializeEx(0, COINIT_MULTITHREADED);
	texture->Initialize(kWindowWidth, kWindowHeight);


	imGuiManager->Initialize();

	gameScene = new GamePlayScene;
	gameScene->Initialize();
}

void GameManager::Update()
{
	dxCommon->PreDraw();
	engine->PreDraw();

	imGuiManager->Begin();

	gameScene->Update();



	imGuiManager->End();
}

void GameManager::Draw()
{
	gameScene->Draw();

	imGuiManager->Draw();
	engine->PostDraw();
	dxCommon->PostDraw();
}

void GameManager::Finalize()
{
	D3DResourceLeakChecker leakCheak;
	CoUninitialize();

	gameScene->Finalize();

	delete engine;
	delete texture;
	delete dxCommon;
	delete winApp;
	delete input;
	delete imGuiManager;

}
