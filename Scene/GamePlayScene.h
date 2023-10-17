#pragma once
#include<Windows.h>
#include"Triangle.h"
#include"ImGuiManager.h"
#include"Sprite.h"
#include"Sphere.h"
#include"Model.h"
#include"Input.h"



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
	Sphere* sphere;
	Sprite* sprite;
	Model* model;
	Model* model2;

	uint32_t uvTexture;
	uint32_t monsterTexture;

	Transform transform_;
	Transform transform2_;

};

