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
	void Initialize(WindowAPI* winApp, DirectXCommon* dxcommon, MyEngine* engine, TextureManager* texture, SpriteData* data, uint32_t textureHandle);

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
	/// マテリアルのバッファの取得
	/// </summary>
	void MaterialBuffer();

	/// <summary>
	/// wvpのバッファの取得
	/// </summary>
	void WvpBuffer();

	/// <summary>
	/// インデックスバッファ
	/// </summary>
	void IndexBuffer();


private:


	WindowAPI* winApp_;
	DirectXCommon* dxCommon_;
	MyEngine* engine_;
	TextureManager* texture_;

	uint32_t textureHandle_;

	VertexData* vertexData_ = nullptr;
	Material* materialData_ = nullptr;
	TransformationMatrix* transformationMatrixData = nullptr;
	Transform transform_ = {};
	uint32_t* indexData_ = nullptr;
	Transform uvTransform_;
	Matrix4x4 uvTransformMatrix_;

	ID3D12Resource* vertexResource_ = nullptr;	//頂点リソース
	ID3D12Resource* materialResource_ = nullptr;	//マテリアルリソース
	ID3D12Resource* transformationmatrixResource = nullptr;	//トランスフォーメーションマトリックスリソース
	ID3D12Resource* indexResource_ = nullptr;

	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};	//頂点バッファビュー
	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};	//インデックスバッファビュー

};

