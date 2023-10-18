#include "Player.h"

/// <summary>
/// 初期化
/// </ summary>
void Player::Initialize(Model* model, Vector3 position)
{
	assert(model);
	model_ = model;
	
	input_ = Input::GetInstance();

	transform_ =
	{
		{1.0,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		position
	};

	speed_ = { 0.2,0.2f };
	

}

/// <summary>
/// 初期化
/// </ summary>
void Player::Update()
{
	move = { 0, 0, 0 };
	

	move.x += speed_.x;
	move.y += speed_.y;

	model_->Update(transform_);


}

/// <summary>
/// 初期化
/// </ summary>
void Player::Draw()
{
	model_->Draw();
}
