#include"MyEngine.h"

/*=====================================*/
/* 　　　　   パブリックメソッド　　　	　 */
/*=====================================*/

MyEngine::~MyEngine()
{

	delete triangle_;


	graphicsPipelineState_->Release();
	signatureBlob_->Release();
	if (errorBlob_)
	{
		errorBlob_->Release();
	}
	rootSignature_->Release();
	pixelShaderBlob_->Release();
	vertexShaderBlob_->Release();

}

/// 初期化
void MyEngine::Initialize(DirectXCommon* dxCommon, WindowAPI* winApp)
{
	dxCommon_ = dxCommon;
	winApp_ = winApp;

	IntializeDXC();//DXCの初期化
	PSO();//パイプラインステートの設定
	CreateViewport();//ビューポートの生成
	CreateScissor();	//シザー矩形の生成


}


/// 描画前処理
void MyEngine::PreDraw()
{
	//コマンドを積む
	SetCommand();
}

/// 描画後処理
void MyEngine::PostDraw()
{

}



/*=====================================*/
/* 　　　　   プライベートメソッド　　　    */
/*=====================================*/


//CompileShader関数
IDxcBlob* MyEngine::CompileShader
(
	//compilerするshaderファイルへのパス
	const std::wstring& filePath,
	//Compilerに使用するprofile
	const wchar_t* profile,
	//初期化で生成したものを3つ
	IDxcUtils* dxcUtils,
	IDxcCompiler3* dxcCompiler,
	IDxcIncludeHandler* includeHandler
)
{
	//1.hlslファイルを読む
	//これからシェーダーをコンパイルする旨をログに出す
	Log(ConvertString(std::format(L"Begin CompileShader,path:{},profile:{}\n", filePath, profile)));
	//hlslファイルを読む
	IDxcBlobEncoding* shaderSource = nullptr;
	HRESULT hr = dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource);
	//読めなかったら止める
	assert(SUCCEEDED(hr));
	//読み込んだファイルの内容を設定する
	DxcBuffer shaderSourceBuffer;
	shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
	shaderSourceBuffer.Size = shaderSource->GetBufferSize();
	shaderSourceBuffer.Encoding = DXC_CP_UTF8;//UTF8の文字コードであることを通知

	//2.compileする
	LPCWSTR arguments[] =
	{
		filePath.c_str(),//コンパイル対象のhlslファイル名
		L"-E",L"main",	 //エントリーポイントの指定。基本的にmain以外にはしない
		L"-T",profile,	 //ShaderProfileの設定
		L"-Od",			 //最適化をはずしておく
		L"-Zpr",		 //メモリアウトは行優先
	};
	//実際にShaderをコンパイルする
	IDxcResult* shaderResult = nullptr;
	hr = dxcCompiler->Compile
	(
		&shaderSourceBuffer,		//読み込んだファイル
		arguments,					//コンパイルオプション
		_countof(arguments),
		includeHandler,				//コンパイルオプションの数
		IID_PPV_ARGS(&shaderResult)	//includeが含まれた諸々
	);
	//コンパイルエラーではなくdxcが起動できないなど致命的な状況
	assert(SUCCEEDED(hr));

	//3.警告・エラーが出ていないか確認する
	//警告・エラーが出てたらログに出して止める
	IDxcBlobUtf8* shaderError = nullptr;
	if (shaderResult != 0)
	{
		shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
		if (shaderError != nullptr && shaderError->GetStringLength() != 0)
		{
			Log(shaderError->GetStringPointer());
			//警告・エラーダメゼッタイ
			assert(false);
		}
	}
	//4.Compile結果を受け取って返す
	//コンパイル結果から実行用のバイナリ部分を取得
	IDxcBlob* shaderBlob = nullptr;
	hr = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
	assert(SUCCEEDED(hr));
	//成功したログを出す
	Log(ConvertString(std::format(L"Compile Succeeded,path:{},profile:{}\n", filePath, profile)));
	//もう使わないリソースを解放
	shaderSource->Release();
	shaderResult->Release();
	//実行用のバイナリを返却
	return shaderBlob;

}



/// DXCの初期化
void MyEngine::IntializeDXC()
{
	hr_ = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils_));
	assert(SUCCEEDED(hr_));
	hr_ = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler_));
	assert(SUCCEEDED(hr_));

	hr_ = dxcUtils_->CreateDefaultIncludeHandler(&includeHandler_);
	assert(SUCCEEDED(hr_));
}

/// パイプラインステートの設定
void MyEngine::PSO()
{
	//ルートシグネチャの生成
	CreateRootSignature();

	//インプットレイヤーアウトの生成
	SetInputLayout();

	//ブレンドステートの設定
	SetBlendState();

	//ラスタライザステートの設定
	SetRasterrizerState();

	//シェーダをコンパイルする 
	ShaderCompile();

	//PSOを生成する
	CreatePSO();
}


/// ルートシグネチャの生成
void MyEngine::CreateRootSignature()
{
	descriptionRootSignature_.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	//シリアライズしてバイナリにする
	hr_ = D3D12SerializeRootSignature(&descriptionRootSignature_, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob_, &errorBlob_);
	if (FAILED(hr_))
	{
		Log(reinterpret_cast<char*>(errorBlob_->GetBufferPointer()));
		assert(false);
	}
	//バイナリを元に生成
	hr_ = dxCommon_->GetDevice()->CreateRootSignature(0, signatureBlob_->GetBufferPointer(), signatureBlob_->GetBufferSize(), IID_PPV_ARGS(&rootSignature_));
	assert(SUCCEEDED(hr_));
}

/// InputLayoutの設定
void MyEngine::SetInputLayout()
{
	inputElementDescs_[0].SemanticName = "POSITION";
	inputElementDescs_[0].SemanticIndex = 0;
	inputElementDescs_[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs_[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	inputLayoutDesc_.pInputElementDescs = inputElementDescs_;
	inputLayoutDesc_.NumElements = _countof(inputElementDescs_);
}


/// ブレンドステートの設定
void MyEngine::SetBlendState()
{
	//すべての色要素を書き込む
	blendDesc_.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
}

/// ラスタライザステートの設定
void MyEngine::SetRasterrizerState()
{
	//裏面(時計回り)を表示しない
	rasterizerDesc_.CullMode = D3D12_CULL_MODE_BACK;
	//三角形の中を塗りつぶす
	rasterizerDesc_.FillMode = D3D12_FILL_MODE_SOLID;
}

///	シェーダをコンパイルする 
void MyEngine::ShaderCompile()
{
	//Shaderをコンパイルする
	vertexShaderBlob_ = CompileShader(L"Resources/Shaders/Object3d.VS.hlsl", L"vs_6_0", dxcUtils_, dxcCompiler_, includeHandler_);
	assert(vertexShaderBlob_ != nullptr);

	pixelShaderBlob_ = CompileShader(L"Resources/Shaders/Object3d.PS.hlsl", L"ps_6_0", dxcUtils_, dxcCompiler_, includeHandler_);
	assert(pixelShaderBlob_ != nullptr);
}

/// PSOを生成する
void MyEngine::CreatePSO()
{
	graphicsPipelineStateDesc_.pRootSignature = rootSignature_;	//RootSignature
	graphicsPipelineStateDesc_.InputLayout = inputLayoutDesc_;	//InputLayout
	graphicsPipelineStateDesc_.VS = { vertexShaderBlob_->GetBufferPointer(),vertexShaderBlob_->GetBufferSize() };	//VertexShader
	graphicsPipelineStateDesc_.PS = { pixelShaderBlob_->GetBufferPointer(),pixelShaderBlob_->GetBufferSize() };	//PixelShader
	graphicsPipelineStateDesc_.BlendState = blendDesc_;	//BlendDesc
	graphicsPipelineStateDesc_.RasterizerState = rasterizerDesc_;	//RasterrizerState
	//書き込むRTVの情報
	graphicsPipelineStateDesc_.NumRenderTargets = 1;
	graphicsPipelineStateDesc_.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//利用するトポロジ(形状)のタイプ。三角形
	graphicsPipelineStateDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	//どのように画面に色を打ち込むのかの設定(気にしなくて良い)
	graphicsPipelineStateDesc_.SampleDesc.Count = 1;
	graphicsPipelineStateDesc_.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	hr_ = dxCommon_->GetDevice()->CreateGraphicsPipelineState(&graphicsPipelineStateDesc_, IID_PPV_ARGS(&graphicsPipelineState_));
	assert(SUCCEEDED(hr_));
}



/// ビューポートの生成
void MyEngine::CreateViewport()
{

	//クライアント領域のサイズと一緒にして画面全体に表示
	viewport_.Width = static_cast<float>(winApp_->GetWidth());
	viewport_.Height = static_cast<float>(winApp_->GetHeight());

	viewport_.TopLeftX = 0;
	viewport_.TopLeftY = 0;
	viewport_.MinDepth = 0.0f;
	viewport_.MaxDepth = 1.0f;
}

void MyEngine::CreateScissor()
{
	//基本的にビューポートと同じ矩形が構成されるようにする
	scissorRect_.left = 0;
	scissorRect_.right = winApp_->GetWidth();
	scissorRect_.top = 0;
	scissorRect_.bottom = winApp_->GetHeight();
}

/// 描画する
void MyEngine::SetCommand()
{

	//コマンドを積む
	dxCommon_->GetCommandList()->RSSetViewports(1, &viewport_);	//Viewportを設定
	dxCommon_->GetCommandList()->RSSetScissorRects(1, &scissorRect_);	//Scirssorを設定
	//RootSignatureを設定。PSOに設定しているけど別途設定が必要
	dxCommon_->GetCommandList()->SetGraphicsRootSignature(rootSignature_);
	dxCommon_->GetCommandList()->SetPipelineState(graphicsPipelineState_);	//PSOを設定

}