#pragma once
#include"WindowAPI.h"
#include"DirectXCommon.h"
#include"MyEngine.h"
#include"MathUtilty.h"
#include"Vector4.h"
#include"Matrix4x4.h"
#include"Vector2.h"
#include"Transform.h"
#include"TextureManager.h"

#include<numbers>
#include<cmath>
#include<assert.h>

#include"Transform.h"

class Sphere
{
public:

	~Sphere();

	void Initialize(uint32_t textureHandle);

	void Update();

	void Draw();

private:

	WindowAPI* winApp_;
	DirectXCommon* dxCommon_;
	MyEngine* engine_;
	TextureManager* texture_;

	uint32_t textureHandle_;

	uint32_t kClientWidth_ = 0;
	uint32_t kClientHeight_ = 0;

	Microsoft::WRL::ComPtr < ID3D12Resource>vertexResource_;	//頂点リソース
	Microsoft::WRL::ComPtr < ID3D12Resource> materialResource_;	//マテリアルリソース
	Microsoft::WRL::ComPtr < ID3D12Resource> wvpResource_;	//wvpリソース
	Microsoft::WRL::ComPtr < ID3D12Resource> lightResource_ = nullptr;

	VertexData* vertexData_ = nullptr;
	Material* materialData_ = nullptr;	//マテリアルデータ
	TransformationMatrix* wvpData_ = nullptr;	//wvpデータ
	DirectionalLight* lightData_ = nullptr;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;
	D3D12_VERTEX_BUFFER_VIEW materialBufferView_;
	D3D12_VERTEX_BUFFER_VIEW wvpBufferView_;


	//分割数
	const uint32_t kSubdivision = 16;

	//経度分割1つ分の角度
	const float kLonEvery = static_cast<float>(std::numbers::pi) * 2.0f / float(kSubdivision);
	//緯度分割1つ分の角度
	const float kLatEvery = static_cast<float>(std::numbers::pi) / float(kSubdivision);

	uint32_t latIndex = 0;
	uint32_t lonIndex = 0;

	//球の全ての頂点
	const uint32_t totalVertex = 1536;

	bool useMonsterBall = true;
	

	Transform transform_ = {};
	Transform cameraTransform_ = {};

	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU2_;


private:
	/// <summary>
	/// 頂点のバッファの取得
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
	/// ライトのバッファの取得
	/// </summary>
	void LightBuffer();
};

