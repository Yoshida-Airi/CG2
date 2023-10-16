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

struct D3DResourceLeakChecker
{
	~D3DResourceLeakChecker()
	{
		//リソースリークチェック
		Microsoft::WRL::ComPtr< IDXGIDebug1> debug;
		if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug))))
		{
			debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
			debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
			debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
			debug->Release();
		}
	}
};

class GamePlayScene
{
public:

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

private:

	const wchar_t* kWindowTitle = L"CG2";

	//アプリケーションの開始
	const uint32_t kWindowWidth = 1280;
	const uint32_t kWindowHeight = 720;

	WindowAPI* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	MyEngine* engine = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	TextureManager* texture = nullptr;
	Input* input = nullptr;

	SpriteData* spriteData = nullptr;
	Sphere* sphere;
	Sprite* sprite;
	Model* model;
	Model* model2;

	uint32_t uvTexture;
	uint32_t monsterTexture;

};

