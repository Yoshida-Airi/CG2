#pragma once

#include<cassert>
#include<dxgidebug.h>
#include<dxcapi.h>

#include"DirectXCommon.h"
#include"WindowAPI.h"
#include"ConvertString.h"

#pragma comment(lib,"dxcompiler.lib")


class MyEngine
{
public:

	~MyEngine();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, WindowAPI* winApp);

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();


	ID3D12Resource* CreateBufferResource(size_t sizeInBytes);

private://プライベート変数

	//ウィンドウアプリケーション管理
	WindowAPI* winApp_;
	DirectXCommon* dxCommon_;


	HRESULT hr_;
	IDxcUtils* dxcUtils_ = nullptr;
	IDxcCompiler3* dxcCompiler_ = nullptr;
	IDxcIncludeHandler* includeHandler_ = nullptr;

	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature_{};	//RootSignature作成
	ID3D12RootSignature* rootSignature_ = nullptr;	//バイナリを元に生成
	ID3DBlob* signatureBlob_ = nullptr;//シリアライズしてバイナリにする
	ID3DBlob* errorBlob_ = nullptr;

	D3D12_INPUT_ELEMENT_DESC inputElementDescs_[2] = {};//InputLayout
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc_{};

	D3D12_BLEND_DESC blendDesc_{};//BlendStateの設定

	D3D12_RASTERIZER_DESC rasterizerDesc_{};//RasiterzerStateの設定

	IDxcBlob* vertexShaderBlob_;
	IDxcBlob* pixelShaderBlob_;

	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};	//DepthStensilStateの設定

	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc_{};	//PSO
	ID3D12PipelineState* graphicsPipelineState_ = nullptr;	//実際に生成

	D3D12_RESOURCE_DESC vertexResourceDesc_{};	//頂点リソースの設定
	ID3D12Resource* vertexResource_;	//実際に頂点リソースを作る
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};//頂点バッファビューを作成する

	D3D12_VIEWPORT viewport_{};	//ビューポート
	D3D12_RECT scissorRect_{};//シザー矩形



private://プライベート関数

	//コンパイルシェーダー関数
	IDxcBlob* CompileShader
	(//compilerするshaderファイルへのパス
		const std::wstring& filePath,
		//Compilerに使用するprofile
		const wchar_t* profile,
		//初期化で生成したものを3つ
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler
	);

	/// <summary>
	/// DXCの初期化
	/// </summary>
	void IntializeDXC();

	/// <summary>
	/// パイプラインステートの設定
	/// </summary>
	void PSO();

	/// <summary>
	/// ルートシグネチャの生成
	/// </summary>
	void CreateRootSignature();


	/// <summary>
	/// InputLayoutの設定
	/// </summary>
	void SetInputLayout();

	/// <summary>
	/// ブレンドステートの設定
	/// </summary>
	void SetBlendState();

	/// <summary>
	/// ラスタライザステートの設定
	/// </summary>
	void SetRasterrizerState();

	/// <summary>
	///	シェーダをコンパイルする 
	/// </summary>
	void ShaderCompile();

	/// <summary>
	/// DepthStencilStateの設定を行なう
	/// </summary>
	void SetDepthStencilState();

	/// <summary>
	/// PSOを生成する
	/// </summary>
	void CreatePSO();

	/// <summary>
	/// ビューポートの生成
	/// </summary>
	void CreateViewport();


	/// <summary>
	/// シザー矩形の生成
	/// </summary>
	void CreateScissor();

	/// <summary>
	/// コマンドを積む
	/// </summary>
	void SetCommand();

};