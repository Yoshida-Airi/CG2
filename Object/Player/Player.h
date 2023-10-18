#pragma once
#include"Model.h"
#include"Vector3.h"
#include"Input.h"
#include<cassert>
#include"Transform.h"

class Player
{
public:
	~Player();

	/// <summary>
	/// 初期化
	/// </ summary>
	void Initialize(Model* model,Vector3 position);
	
	/// <summary>
	/// 初期化
	/// </ summary>
	void Update();

	/// <summary>
	/// 初期化
	/// </ summary>
	void Draw();

private:

	Model* model_ = nullptr;
	Input* input_ = nullptr;
	Vector2 speed_ = {};
	Transform transform_;

	Vector3 move;
};

