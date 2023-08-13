#pragma once
#include"externals/DirectXTex/DirectXTex.h"
#include"ConvertString.h"
#include"DirectXCommon.h"

#include<d3d12.h>

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
	void Initialize(DirectXCommon* dxCommon);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

private:

	DirectXCommon* dxCommon_;

	DirectX::ScratchImage mipImages_;
	ID3D12Resource* textureResource_;
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc_{};
	ID3D12DescriptorHeap* srvDescriptoHeap_;

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
	ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& meradata);

	/// <summary>
	/// TextureResource2データを転送する
	/// </summary>
	/// <param name="texture">画像</param>
	/// <param name="mipImages">ミップマップ</param>
	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	/// <summary>
	/// シェーダーリソース
	/// </summary>
	void CreateShaderResourceView(const DirectX::TexMetadata& metadata);

};

