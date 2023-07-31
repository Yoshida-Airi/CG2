#pragma once
#include"WindowAPI.h"
#include"DirectXCommon.h"
#include"MyEngine.h"
#include"MathUtilty.h"
#include"Vector4.h"
#include"Matrix4x4.h"
#include"Transform.h"
#include"ImGuiManager.h"

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
	/// <param name="direct"></param>
	void Initialize(WindowAPI* winApp, DirectXCommon* direct, MyEngine* engine);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(const TriangleData& data);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="a">左下</param>
	/// <param name="b">上</param>
	/// <param name="c">右下</param>
	void Draw();

	

private://プライベート変数

	WindowAPI* winApp_;
	DirectXCommon* dxCommon_;
	MyEngine* engine_;
	ImGuiManager* imGuiManager_;

	uint32_t kClientWidth_ = 0;
	uint32_t kClientHeight_ = 0;

	ID3D12Resource* vertexResource_;	//頂点リソース
	ID3D12Resource* materialResource_;	//マテリアルリソース
	ID3D12Resource* wvpResource_;	//wvpリソース

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;
	D3D12_VERTEX_BUFFER_VIEW materialBufferView_;
	D3D12_VERTEX_BUFFER_VIEW wvpBufferView_;

	Vector4* vertexData_ = nullptr;	//頂点データ
	Vector4* materialData_ = nullptr;	//マテリアルデータ
	Matrix4x4* wvpData_ = nullptr;	//wvpデータ

	Transform transform_;
	Matrix4x4 worldMatrix_;

	Transform cameraTransform_;

	bool isRotate = false;

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
