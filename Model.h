#pragma once
#include<vector>
#include"Transform.h"
#include<string>
#include<fstream>
#include<sstream>
#include"WindowAPI.h"
#include"DirectXCommon.h"
#include"MyEngine.h"
#include"MathUtilty.h"
#include"Vector4.h"
#include"Matrix4x4.h"
#include"Vector2.h"
#include"TextureManager.h"
#include<numbers>
#include<cmath>
#include<assert.h>

struct MaterialData
{
	std::string textureFilePath;
};

struct ModelData
{
	std::vector<VertexData>vertices;
	MaterialData material;
};



class Model
{
public:

	~Model();

	void Initialize(WindowAPI* winApp, DirectXCommon* dxComon, MyEngine* engine, TextureManager* texture);
	void Update();
	void Draw();

private:

	WindowAPI* winApp_;
	DirectXCommon* dxCommon_;
	MyEngine* engine_;
	TextureManager* texture_;

	uint32_t kClientWidth_ = 0;
	uint32_t kClientHeight_ = 0;

	ModelData modelData_;	//モデル
	ID3D12Resource* vertexResource_;	//頂点リソース
	VertexData* vertexData_ = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};	//頂点バッファ

	ID3D12Resource* wvpResource_;	//wvpリソース
	TransformationMatrix* wvpData_ = nullptr;	//wvpデータ
	D3D12_VERTEX_BUFFER_VIEW wvpBufferView_;

	ID3D12Resource* materialResource_;	//マテリアルリソース
	Material* materialData_ = nullptr;	//マテリアルデータ
	D3D12_VERTEX_BUFFER_VIEW materialBufferView_;

	DirectX::ScratchImage mipImages2 = {};

	Transform transform_ = {};
	Transform cameraTransform_ = {};

	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_;

	/// <summary>
	/// Objファイルを読むための関数
	/// </summary>
	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// mtlファイルを読むための関数
	/// </summary>
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

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

};

