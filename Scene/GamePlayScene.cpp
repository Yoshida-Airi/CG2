#include "GamePlayScene.h"

void GamePlayScene::Initialize()
{
	texture = TextureManager::GetInstance();
	input = Input::GetInstance();

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

	

	uvTexture = texture->LoadTexture("Resources/uvChecker.png");
	monsterTexture = texture->LoadTexture("Resources/monsterBall.png");


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
	

	if (input->PushKey(DIK_UP))
	{
		transform_.translate.x += 0.01f;
	}

	if (input->PushKey(DIK_W))
	{
		transform2_.translate.x += 0.01f;
	}



	input->Update();
	model->Update(transform_);
	model2->Update(transform2_);
	sphere->Update();
	sprite->Update();

}

void GamePlayScene::Draw()
{

	model->Draw();
	model2->Draw();
	sphere->Draw();
	sprite->Draw();



}

void GamePlayScene::Finalize()
{
	
	delete sphere;
	delete sprite;
	delete model;
	delete model2;
	delete spriteData;
	
}
