#pragma once
#include"WindowAPI.h"
#include"DirectXCommon.h"
#include"MyEngine.h"
#include"TextureManager.h"

#include"MathUtilty.h"

#include"Transform.h"
#include"Vector4.h"
#include"Matrix4x4.h"



struct SpriteData
{
	Vector4 vertex[6];
	Transform  transform;
};

class Sprite
{
public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sprite();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WindowAPI* winApp, DirectXCommon* dxcommon, MyEngine* engine);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();


private:
	
	/// <summary>
	/// 頂点バッファ
	/// </summary>
	void VertexBuffer();


	/// <summary>
	/// wvpのバッファの取得
	/// </summary>
	void WvpBuffer();

private:


	WindowAPI* winApp_;
	DirectXCommon* dxCommon_;
	MyEngine* engine_;
	TextureManager* texture_;

	VertexData* vertexData_ = nullptr;
	Matrix4x4* transformationMatrixData = nullptr;
	Transform transform_ = {};

	ID3D12Resource* vertexResource_ = nullptr;	//頂点リソース
	ID3D12Resource* transformationmatrixResource = nullptr;	//トランスフォーメーションマトリックスリソース

	

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};	//頂点バッファビュー


};

