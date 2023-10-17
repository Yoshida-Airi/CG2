#include "GameManager.h"

void GameManager::Initialize()
{
	winApp = WindowAPI::GetInstance();
	winApp->StartApp(kWindowTitle, kWindowWidth, kWindowHeight);
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize();
	engine = MyEngine::GetInstance();
	engine->Initialize();

#ifdef _DEBUG
	imGuiManager = ImGuiManager::GetInstance();
	imGuiManager->Initialize();
#endif // _DEBUG


	texture = TextureManager::GetInstance();
	texture->Initialize(kWindowWidth, kWindowHeight);
	input = Input::GetInstance();
	input->Initialize();


	CoInitializeEx(0, COINIT_MULTITHREADED);



	gameScene = new GamePlayScene;
	gameScene->Initialize();
	//title = new GameTitleScene;
	//title->Initialize();
}

void GameManager::Update()
{
	dxCommon->PreDraw();
	engine->PreDraw();

#ifdef _DEBUG
	imGuiManager->Begin();
#endif // _DEBUG

	


	gameScene->Update();
	//title->Update();

#ifdef _DEBUG
	imGuiManager->End();
#endif // _DEBUG

}

void GameManager::Draw()
{
	gameScene->Draw();
	//title->Draw();

#ifdef _DEBUG
	imGuiManager->Draw();
#endif // _DEBUG

	
	engine->PostDraw();
	dxCommon->PostDraw();
}

void GameManager::Finalize()
{
	CoUninitialize();

#ifdef _DEBUG
	D3DResourceLeakChecker leakCheak;
#endif // _DEBUG

	

	gameScene->Finalize();
	/*title->Finalize();*/

	delete engine;
	delete texture;
	delete dxCommon;
	delete winApp;
	delete input;
	delete imGuiManager;

}
