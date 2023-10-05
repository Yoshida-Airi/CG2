#pragma once
#include"externals/DirectXTex/d3dx12.h"
#include"externals/DirectXTex/DirectXTex.h"
#include"ConvertString.h"
#include"DirectXCommon.h"
#include"MyEngine.h"

#include<d3d12.h>
#include<vector>

#pragma comment(lib,"d3d12.lib")

class TextureManager
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TextureManager();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, MyEngine* engine);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	D3D12_GPU_DESCRIPTOR_HANDLE GetTextureSrvHandleGPU()const { return textureSrvHandleGPU_; }

private:

	DirectXCommon* dxCommon_;
	MyEngine* engine_;

	DirectX::ScratchImage mipImages_;
	ID3D12Resource* textureResource_;
	ID3D12Resource* intermediateResource_;

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc_{};
	ID3D12DescriptorHeap* srvDescriptoHeap_;

	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU_ = {};
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_ = {};

private:

	/// <summary>
	/// Textureデータを読む
	/// </summary>
	/// <param name="filePath">テクスチャ</param>
	/// <returns>テクスチャデータ</returns>
	DirectX::ScratchImage LoadTexture(const std::string& filePath);

	/// <summary>
	/// ダイレクトX12のテクスチャリソースを作る
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="meradata"></param>
	/// <returns>テクスチャリソース</returns>
	ID3D12Resource* CreateTextureResource(DirectX::TexMetadata& metadata);

	/// <summary>
	/// TextureResource2データを転送する
	/// </summary>
	/// <param name="texture">画像</param>
	/// <param name="mipImages">ミップマップ</param>
	ID3D12Resource* UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	/// <summary>
	/// シェーダーリソース
	/// </summary>
	void CreateShaderResourceView(const DirectX::TexMetadata& metadata);

};