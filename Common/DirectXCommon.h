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

class DirectXCommon
{
public:
	DirectXCommon();
	~DirectXCommon();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WindowAPI* winApp);

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();



	ID3D12Device* GetDevice()const { return device_; };
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList_; };

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


private://プライベート変数

	//ウィンドウアプリケーション管理
	WindowAPI* winApp_;


	//Direct3D関連
	IDXGIFactory7* dxgiFactory_ = nullptr;	//ファクトリー
	ID3D12Device* device_ = nullptr;	//デバイス
	ID3D12CommandAllocator* commandAllocator_ = nullptr;	//コマンドアロケータ
	ID3D12GraphicsCommandList* commandList_ = nullptr;	//コマンドリスト
	ID3D12CommandQueue* commandQueue_ = nullptr;	//コマンドキュー
	IDXGISwapChain4* swapChain_ = nullptr;	//スワップチェーン
	ID3D12DescriptorHeap* rtvDescriptorHeap_ = nullptr;	//ディスクリプタヒープ
	ID3D12Resource* swapChainResources_[2] = { nullptr };	//スワップチェーンリソース
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_{};	//rtv
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles_[2];//RTVを二つ作るのでディスクリプタを二つ用意
	D3D12_RESOURCE_BARRIER barrier_{};	//トランスフォームバリア
	ID3D12Fence* fence_ = nullptr;	//フェンス
	uint64_t fenceValue_ = 0;	//フェンスの値
	HANDLE fenceEvent_ = nullptr;
	IDXGIAdapter4* useAdapter_ = nullptr;


	ID3D12Debug1* debugController_ = nullptr;

};

