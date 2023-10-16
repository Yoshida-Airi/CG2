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

struct TriangleData
{
	Vector4 vertex[3];
	Vector4 color;
	Transform  transform;
};

class Triangle
{
public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Triangle();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="winApp"></param>
	/// <param name="direct"></param>
	/// <param name="engine"></param>
	/// <param name="data"></param>
	/// <param name="texture"></param>
	void Initialize(WindowAPI* winApp, DirectXCommon* direct, MyEngine* engine, const TriangleData& data, TextureManager* texture);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


private://プライベート変数

	WindowAPI* winApp_;
	DirectXCommon* dxCommon_;
	MyEngine* engine_;
	TextureManager* texture_;

	uint32_t kClientWidth_ = 0;
	uint32_t kClientHeight_ = 0;

	Microsoft::WRL::ComPtr < ID3D12Resource> vertexResource_;	//頂点リソース
	Microsoft::WRL::ComPtr < ID3D12Resource> materialResource_;	//マテリアルリソース
	Microsoft::WRL::ComPtr < ID3D12Resource> wvpResource_;	//wvpリソース

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;
	D3D12_VERTEX_BUFFER_VIEW materialBufferView_;
	D3D12_VERTEX_BUFFER_VIEW wvpBufferView_;

	VertexData* vertexData_ = nullptr;
	Vector4* materialData_ = nullptr;	//マテリアルデータ
	Matrix4x4* wvpData_ = nullptr;	//wvpデータ

	Transform transform_;
	Matrix4x4 worldMatrix_;

	Transform cameraTransform_;

	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_;

private://プライベート関数

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
