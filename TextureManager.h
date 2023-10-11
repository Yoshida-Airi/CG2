#pragma once
#include"DirectXCommon.h"
#include"MyEngine.h"
#include"externals/DirectXTex/DirectXTex.h"
#include"externals/DirectXTex/d3dx12.h"
#include<wrl.h>
#include<array>
class TextureManager
{
public:

	struct Texture
	{
		D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU;
		D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU;
		ID3D12Resource* textureResource;
	};
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TextureManager();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="directX"></param>
	/// <param name="engine"></param>
	void Initialize(DirectXCommon* directX, MyEngine* engine);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 画像読み込み
	/// </summary>
	/// <param name="index"></param>
	/// <param name="filePath"></param>
	void LoadTexture(uint32_t index, const std::string& filePath);

	//ゲッター
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle(uint32_t index)
	{
		return textures_.at(index).textureSrvHandleGPU;
	}

private:

	DirectXCommon* dxCommon_;
	MyEngine* engine_;

	static const size_t kMaxSRVCount = 2056;
	std::array<Texture, kMaxSRVCount> textures_;



	//中間リソース
	std::array<ID3D12Resource*, kMaxSRVCount> intermediateResource;

	DirectX::ScratchImage ImageFileOpen(const std::string& filePath);
	ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);

	[[nodiscard]]
	ID3D12Resource* UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);
};
