#pragma once
#include<Windows.h>
#include"Triangle.h"
#include"ImGuiManager.h"
#include"Sprite.h"
#include"Sphere.h"
#include"Model.h"
#include"Input.h"

#include"Player.h"


class GamePlayScene
{
public:

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

private:

	TextureManager* texture = nullptr;
	Input* input = nullptr;

	SpriteData* spriteData = nullptr;
	Sprite* sprite;
	Model* model_ = nullptr;

	uint32_t uvTexture;
	uint32_t monsterTexture;

	Transform transform_;

	Player* player_ = nullptr;



};

