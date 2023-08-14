#pragma once
#include"externals/DirectXTex/DirectXTex.h"
#include"ConvertString.h"
#include<d3d12.h>

class TextureManager
{
public:

	~TextureManager();

	/// <summary>
	///	初期化
	/// </summary>
	void Initialize();

	void Updata();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();


	void transfertexture(ID3D12Device* device);



private:
	DirectX::TexMetadata metadata_;
	DirectX::ScratchImage mipImages_;
	ID3D12Resource* textureResource_;
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc_;
	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU_;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_;

private:
	/// <summary>
	/// テクスチャデータを読む
	/// </summary>
	/// <param name="filepath"></param>
	/// <returns></returns>
	DirectX::ScratchImage LoadTexture(const std::string& filePath);

	/// <summary>
	/// DirectX12のTextureResourceを作る
	/// </summary>
	/// <param name="device"></param>
	/// <param name="metadata"></param>
	/// <returns></returns>
	ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);


	/// <summary>
	/// TextureResourceにデータを転送する
	/// </summary>
	/// <param name="texture"></param>
	/// <param name="mipImages"></param>
	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);



};

