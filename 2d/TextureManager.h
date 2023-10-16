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
		Microsoft::WRL::ComPtr< ID3D12Resource> textureResource;
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
	void Initialize(DirectXCommon* directX, MyEngine* engine, int32_t width, int32_t height);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 画像読み込み
	/// </summary>
	/// <param name="index"></param>
	/// <param name="filePath"></param>
	uint32_t LoadTexture(const std::string& filePath);

	//ゲッター
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle(uint32_t index)
	{
		return textures_.at(index).textureSrvHandleGPU;
	}

private:

	DirectXCommon* dxCommon_;
	MyEngine* engine_;

	static const size_t kMaxTextureCount = 2056;
	std::array<Texture, kMaxTextureCount> textures_;

	bool IsusedTexture[kMaxTextureCount];

	//中間リソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, kMaxTextureCount> intermediateResource;

	uint32_t descriptorSizeSRV;
	

	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc_;
	Microsoft::WRL::ComPtr< ID3D12Resource> depthStencilResource_;


private:



	DirectX::ScratchImage ImageFileOpen(const std::string& filePath);
	Microsoft::WRL::ComPtr< ID3D12Resource> CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);

	[[nodiscard]]
	Microsoft::WRL::ComPtr< ID3D12Resource> UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);
	
	/// <summary>
	/// 深度の書き込みも出来るテクスチャリソースを作る
	/// </summary>
	/// /// <param name="device"></param>
	/// <param name="width">ウィンドウの幅</param>
	/// <param name="height">ウィンドウの高さ</param>
	/// <returns></returns>
	Microsoft::WRL::ComPtr< ID3D12Resource> CreateDepthStencilTextureResource(Microsoft::WRL::ComPtr< ID3D12Device> device, int32_t width, int32_t height);

	void CreateDepthStencilView(ID3D12Device* device, ID3D12DescriptorHeap* dsvDescriptorHeap);


};