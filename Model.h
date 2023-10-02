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

struct ModelData
{
	std::vector<VertexData>vertices;
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

	ModelData modelData_;	//モデル
	ID3D12Resource* vertexResource_;	//頂点リソース
	VertexData* vertexData_ = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};	//頂点バッファ

	/// <summary>
	/// Objファイルを読むための関数
	/// </summary>
	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// 頂点のバッファの取得
	/// </summary>
	void VertexBuffer();


};

