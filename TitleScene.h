#pragma once
#include<Windows.h>
#include"WindowAPI.h"
#include"DirectXCommon.h"
#include"MyEngine.h"
#include"Triangle.h"
#include"ImGuiManager.h"
#include"TextureManager.h"
#include"Sprite.h"
#include"Sphere.h"
#include"Model.h"
#include"Input.h"


class TitleScene
{
public:

	void Initialize();

	void Update();

	void Draw();

	void Finalize();

private:

	const wchar_t* kWindowTitle = L"CG2";

	WindowAPI* winApp = WindowAPI::GetInstance();
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	MyEngine* engine = MyEngine::GetInstance();
	ImGuiManager* imGuiManager = ImGuiManager::GetInstance();
	TextureManager* texture = TextureManager::GetInstance();
	Input* input = new Input;

	uint32_t uvTexture;
	uint32_t monsterTexture;

	Sphere* sphere = new Sphere;
	Sprite* sprite = new Sprite;

};

