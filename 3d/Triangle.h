#pragma once
#include"WindowAPI.h"
#include"DirectXCommon.h"
#include"Vector4.h"

struct TriangleData
{
	Vector4 vertex[3];
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
	void Initialize(DirectXCommon* direct, const TriangleData& position);


	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="a">左下</param>
	/// <param name="b">上</param>
	/// <param name="c">右下</param>
	void Draw();

	/// <summary>
	/// 頂点
	/// </summary>
	void VertexData();


	ID3D12Resource* vertexResource();


private://プライベート変数

	DirectXCommon* dxCommon_;

	ID3D12Resource* vertexResource_;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;


	Vector4* vertexData_;

private://プライベート関数



};

