#include "Player.h"
#include "Player.h"

Player::~Player()
{
}

/// <summary>
/// 初期化
/// </ summary>
void Player::Initialize(Model* model, Vector3 position)
{
	assert(model);
	model_ = model;
	
	input_ = Input::GetInstance();

	model_->Initialize("Resources", "cube.obj");

	transform_ =
	{
		{1.0,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		position
	};

	speed_ = { 0.2f,0.2f };
	

}

/// <summary>
/// 初期化
/// </ summary>
void Player::Update()
{

	
	if (input_->PushKey(DIK_W))
	{
		transform_.translate.z += speed_.x;
	}
	else if (input_->PushKey(DIK_S))
	{
		transform_.translate.z -= speed_.x;
	}
	else if (input_->PushKey(DIK_D))
	{

		transform_.translate.x += speed_.y;
	}
	else if (input_->PushKey(DIK_A))
	{

		transform_.translate.x -= speed_.y;
	}


	

	model_->Update(transform_);


}

/// <summary>
/// 初期化
/// </ summary>
void Player::Draw()
{
	model_->Draw();
}
