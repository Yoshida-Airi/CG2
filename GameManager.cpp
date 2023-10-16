#include "GameManager.h"

void GameManager::Initialize()
{
	
	scene_ = new GamePlayScene();
	scene_->Initialize();

	/*titleScene_ = new TitleScene();
	titleScene_->Initialize();*/

}

void GameManager::Update()
{
	scene_->Update();
	//titleScene_->Update();
}

void GameManager::Draw()
{
	scene_->Draw();
	//titleScene_->Draw();
}

void GameManager::Finalize()
{
	D3DResourceLeakChecker leakChaker;
	scene_->Finalize();
	//titleScene_->Finalize();

}
