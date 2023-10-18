#include "GamePlayScene.h"

void GamePlayScene::Initialize()
{
	texture = TextureManager::GetInstance();
	input = Input::GetInstance();

	spriteData = new SpriteData;
	sprite = new Sprite;
	model_ = new Model;

	player_ = new Player;

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

	

	uvTexture = texture->LoadTexture("Resources/uvChecker.png");
	monsterTexture = texture->LoadTexture("Resources/monsterBall.png");



	transform_=
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};
	

	sprite->Initialize(spriteData, uvTexture);

	Vector3 playerPos = { 0.0f,0.0f,0.0f };
	player_->Initialize(model_, playerPos);

}

void GamePlayScene::Update()
{
	input->Update();

	if (input->PushKey(DIK_UP))
	{
		transform_.translate.x += 0.01f;
	}

	if (input->PushKey(DIK_W))
	{
		
	}

	player_->Update();

	

	sprite->Update();



}

void GamePlayScene::Draw()
{

	
	sprite->Draw();

	player_->Draw();
}

void GamePlayScene::Finalize()
{
	delete player_;
	delete model_;
	delete sprite;
	delete spriteData;
	
}
