#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include"ConvertString.h"
#include<format>
#include<dxgidebug.h>

#include"WindowAPI.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")

#include<wrl.h>

class DirectXCommon
{
public:

	static DirectXCommon* GetInstance();

	DirectXCommon();
	~DirectXCommon();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();

	/// <summary>
	/// デスクリプタヒープの作成関数
	/// </summary>
	/// <param name="heapType">ヒープのタイプ</param>
	/// <param name="numDescriptors">数</param>
	/// <param name="shaderVisible"></param>
	/// <returns></returns>
	Microsoft::WRL::ComPtr< ID3D12DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);


	ID3D12Device* GetDevice()const { return device_.Get(); };
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList_.Get(); };

	DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc()const { return swapChainDesc_; };
	D3D12_RENDER_TARGET_VIEW_DESC GetRtvDesc()const { return rtvDesc_; };
	ID3D12DescriptorHeap* GetsrvDescriptorHeap()const { return srvDescriptorHeap_.Get(); };
	ID3D12DescriptorHeap* GetDsvDescriptorHeap()const { return dsvDescriptorHeap_.Get(); };

	//静的メンバ変数の宣言と初期化
	static DirectXCommon* instance;

private:

	/// <summary>
	/// DXGIデバイスの初期化
	/// </summary>
	void InitializeDXGIDevice();

	/// <summary>
	/// コマンド関連の初期化
	/// </summary>
	void InitializeCommand();

	/// <summary>
	/// スワップチェーンの生成
	/// </summary>
	void CreateSwapChain();

	/// <summary>
	/// レンダーターゲット生成
	/// </summary>
	void CreateFinalRenderTargets();

	/// <summary>
	/// フェンス生成
	/// </summary>
	void CreateFence();

	/// <summary>
	/// 全画面クリア
	/// </summary>
	void ClearRenderTarget();

	/// <summary>
	/// 深度の書き込みも出来るテクスチャリソースを作る
	/// </summary>
	/// /// <param name="device"></param>
	/// <param name="width">ウィンドウの幅</param>
	/// <param name="height">ウィンドウの高さ</param>
	/// <returns></returns>
	ID3D12Resource* CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height);



private://プライベート変数

	//ウィンドウアプリケーション管理
	WindowAPI* winApp_;


	//Direct3D関連
	Microsoft::WRL::ComPtr< IDXGIFactory7> dxgiFactory_ = nullptr;	//ファクトリー
	Microsoft::WRL::ComPtr< ID3D12Device> device_ = nullptr;	//デバイス
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator_ = nullptr;	//コマンドアロケータ
	Microsoft::WRL::ComPtr< ID3D12GraphicsCommandList> commandList_ = nullptr;	//コマンドリスト
	Microsoft::WRL::ComPtr< ID3D12CommandQueue> commandQueue_ = nullptr;	//コマンドキュー
	Microsoft::WRL::ComPtr< IDXGISwapChain4> swapChain_ = nullptr;	//スワップチェーン
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_ = {};	//スワップチェーンデスク

	Microsoft::WRL::ComPtr< ID3D12DescriptorHeap> rtvDescriptorHeap_ = nullptr;	//ディスクリプタヒープ
	Microsoft::WRL::ComPtr < ID3D12DescriptorHeap> srvDescriptorHeap_ = nullptr;
	Microsoft::WRL::ComPtr < ID3D12DescriptorHeap> dsvDescriptorHeap_ = nullptr;


 	Microsoft::WRL::ComPtr< ID3D12Resource> swapChainResources_[2] = { nullptr };	//スワップチェーンリソース
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_{};	//rtv
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles_[2];//RTVを二つ作るのでディスクリプタを二つ用意
	D3D12_RESOURCE_BARRIER barrier_{};	//トランスフォームバリア
	Microsoft::WRL::ComPtr< ID3D12Fence> fence_ = nullptr;	//フェンス
	uint64_t fenceValue_ = 0;	//フェンスの値
	HANDLE fenceEvent_ = nullptr;
	Microsoft::WRL::ComPtr< IDXGIAdapter4> useAdapter_ = nullptr;


	Microsoft::WRL::ComPtr< ID3D12Debug1> debugController_ = nullptr;

};
