#pragma once
#include"externals/DirectXTex/DirectXTex.h"
#include"ConvertString.h"
#include"DirectXCommon.h"
#include<d3d12.h>

class TextureManager
{
public:

	~TextureManager();

	/// <summary>
	///	初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, int32_t width, int32_t height);


	D3D12_GPU_DESCRIPTOR_HANDLE GetTextureSrvHandleGPU() { return textureSrvHandleGPU_; };


	D3D12_GPU_DESCRIPTOR_HANDLE GetTextureSrvHandleGPU2() { return textureSrvHandleGPU2_; };


private:
	DirectX::TexMetadata metadata_;
	DirectX::TexMetadata metadata2_;

	DirectX::ScratchImage mipImages_;
	DirectX::ScratchImage mipImages2_;

	ID3D12Resource* textureResource_;
	ID3D12Resource* textureResource2_;

	ID3D12Resource* depthStencilResource_;

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc_;
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc2_;


	

	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU_;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_;

	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU2_;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU2_;


	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc_;


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
	/// 深度の書き込みも出来るテクスチャリソースを作る
	/// </summary>
	/// /// <param name="device"></param>
	/// <param name="width">ウィンドウの幅</param>
	/// <param name="height">ウィンドウの高さ</param>
	/// <returns></returns>
	ID3D12Resource* CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height);

	/// <summary>
	/// TextureResourceにデータを転送する
	/// </summary>
	/// <param name="texture"></param>
	/// <param name="mipImages"></param>
	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);


	/// <summary>
	/// SRVの設定と生成
	/// </summary>
	/// <param name="device"></param>
	/// <param name="srvDescriptorHeap"></param>
	void CreateShaderResourceView(ID3D12Device* device, ID3D12DescriptorHeap* srvDescriptorHeap);

	/// <summary>
	///	dsvの設定と設定
	/// </summary>
	void CreateDepthStencilView(ID3D12Device* device, ID3D12DescriptorHeap* dsvDescriptorHeap);


	/// <summary>
	/// CPUハンドルの取得
	/// </summary>
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

	/// <summary>
	/// GPUハンドルの取得
	/// </summary>
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);





};

