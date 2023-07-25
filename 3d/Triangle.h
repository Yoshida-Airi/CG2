#pragma once
#include"WindowAPI.h"
#include"DirectXCommon.h"
#include"Vector4.h"

class Triangle
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="direct"></param>
	void Initialize(DirectXCommon* direct);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="a">左下</param>
	/// <param name="b">上</param>
	/// <param name="c">右下</param>
	void Draw(Vector4* position, ID3D12Resource* resource);

	/// <summary>
	/// 解放
	/// </summary>
	void End();


	/// <summary>
	/// 頂点
	/// </summary>
	void VertexData(Vector4* position, ID3D12Resource* resource);

private://プライベート変数

	DirectXCommon* dxCommon_;

	Vector4* vertexData_;

	ID3D12Resource* vertexResource_;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;



private://プライベート関数



};

