#include "TextureManager.h"


TextureManager::~TextureManager()
{
	textureResource_->Release();
	textureResource2_->Release();
	depthStencilResource_->Release();
}

void TextureManager::Initialize(DirectXCommon* dxCommon, int32_t width, int32_t height)
{
	mipImages_ = LoadTexture("resources/uvChecker.png");
	metadata_ = mipImages_.GetMetadata();
	textureResource_ = CreateTextureResource(dxCommon->GetDevice(), metadata_);

	mipImages2_ = LoadTexture("resources/monsterBall.png");
	metadata2_ = mipImages2_.GetMetadata();
	textureResource2_ = CreateTextureResource(dxCommon->GetDevice(), metadata2_);


	depthStencilResource_ = CreateDepthStencilTextureResource(dxCommon->GetDevice(), width, height);

	UploadTextureData(textureResource_, mipImages_);
	UploadTextureData(textureResource2_, mipImages2_);

	CreateShaderResourceView(dxCommon->GetDevice(), dxCommon->GetsrvDescriptorHeap());
	CreateDepthStencilView(dxCommon->GetDevice(), dxCommon->GetDsvDescriptorHeap());

}



DirectX::ScratchImage TextureManager::LoadTexture(const std::string& filePath)
{
	// テクスチャファイルを読んでプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = ConvertString(filePath);
	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));

	// ミニマップの生成
	DirectX::ScratchImage mipImages{};
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(hr));

	// ミニマップ付きのデータを返す
	return mipImages;
}


ID3D12Resource* TextureManager::CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata)
{
	// metadataをもとにResourceの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = UINT(metadata.width);
	resourceDesc.Height = UINT(metadata.height);
	resourceDesc.MipLevels = UINT16(metadata.mipLevels);
	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);
	resourceDesc.Format = metadata.format;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);

	// 利用するHeapの設定
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;

	// Resourceの生成
	ID3D12Resource* resource = nullptr;
	HRESULT hr = device->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&resource)
	);
	assert(SUCCEEDED(hr));
	return resource;
}


ID3D12Resource* TextureManager::CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height)
{
	//生成するResourceの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = width;		//Textureの幅
	resourceDesc.Height = height;	//Textureの高さ
	resourceDesc.MipLevels = 1;		//mipmapの数
	resourceDesc.DepthOrArraySize = 1;	//奥行き　or　配列Textureの配列数
	resourceDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;	//DepthStencilとして利用可能なフォーマット
	resourceDesc.SampleDesc.Count = 1;		//サンプリングカウント　1固定
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;	//2次元
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;	//DepthStencilとして使う通知

	//利用するHeapの設定
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;	//VRAM上に作る

	//深度値のクリア設定
	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;	//1.0f(最大値)でクリア
	depthClearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;	//フォーマット。resourceと合わせる

	//Resourceの生成
	ID3D12Resource* resource = nullptr;
	HRESULT hr = device->CreateCommittedResource(
		&heapProperties,	//Heaoの設定
		D3D12_HEAP_FLAG_NONE,	//heapの特殊な設定。
		&resourceDesc,	//Resourceの設定
		D3D12_RESOURCE_STATE_DEPTH_WRITE,	//深度値を書き込む状態にしておく
		&depthClearValue,	//Clear最適値
		IID_PPV_ARGS(&resource)	//作成するResourceポインタへのポインタ
	);
	assert(SUCCEEDED(hr));

	return resource;
}

void TextureManager::UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages)
{
	// Meta情報を取得
	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
	// 全MipMapについて
	for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel) {
		// MipMapLevelを指定して各Imageを取得
		const DirectX::Image* img = mipImages.GetImage(mipLevel, 0, 0);
		// Textureに転送
		HRESULT hr = texture->WriteToSubresource(
			UINT(mipLevel),
			nullptr,
			img->pixels,
			UINT(img->rowPitch),
			UINT(img->slicePitch)
		);
		assert(SUCCEEDED(hr));
	}
}


void TextureManager::CreateShaderResourceView(ID3D12Device* device, ID3D12DescriptorHeap* srvDescriptorHeap)
{
	// metaDataをもとにSRVの設定
	srvDesc_.Format = metadata_.format;
	srvDesc_.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc_.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	//2Dテクスチャ
	srvDesc_.Texture2D.MipLevels = UINT(metadata_.mipLevels);

	// SRVを作成するDescriptorHeapの場所を決める
	textureSrvHandleCPU_ = GetCPUDescriptorHandle(srvDescriptorHeap, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV), 1);
	textureSrvHandleGPU_ = GetGPUDescriptorHandle(srvDescriptorHeap, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV), 1);

	// SRVの生成
	device->CreateShaderResourceView(textureResource_, &srvDesc_, textureSrvHandleCPU_);

	srvDesc2_.Format = metadata2_.format;
	srvDesc2_.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc2_.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc2_.Texture2D.MipLevels = UINT(metadata2_.mipLevels);

	textureSrvHandleCPU2_ = GetCPUDescriptorHandle(srvDescriptorHeap, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV), 2);
	textureSrvHandleGPU2_ = GetGPUDescriptorHandle(srvDescriptorHeap, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV), 2);

	device->CreateShaderResourceView(textureResource2_, &srvDesc2_, textureSrvHandleCPU2_);


}


void TextureManager::CreateDepthStencilView(ID3D12Device* device, ID3D12DescriptorHeap* dsvDescriptorHeap)
{
	dsvDesc_.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;	//Format。基本的にはResourceに合わせる
	dsvDesc_.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;	//2dTexture
	//DSVHeapの先頭にDSVを作る
	device->CreateDepthStencilView(depthStencilResource_, &dsvDesc_, dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
}


/// <summary>
/// CPUハンドルの取得
/// </summary>
D3D12_CPU_DESCRIPTOR_HANDLE TextureManager::GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += (descriptorSize * index);
	return handleCPU;
}

/// <summary>
/// GPUハンドルの取得
/// </summary>
D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index)
{
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += (descriptorSize * index);
	return handleGPU;
}