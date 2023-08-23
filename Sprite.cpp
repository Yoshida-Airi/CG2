#include "Sprite.h"


Sprite::~Sprite()
{
	vertexResource_->Release();
	transformationmatrixResource->Release();
}


void Sprite::Initialize(WindowAPI* winApp, DirectXCommon* dxcommon, MyEngine* engine)
{
	winApp_ = winApp;
	dxCommon_ = dxcommon;
	engine_ = engine;

	VertexBuffer();
	WvpBuffer();

	vertexData_[0].position = { 0.0f,360.0f,0.0f,1.0f };
	vertexData_[0].texcoord = { 0.0f,1.0f };

	vertexData_[1].position = { 0.0f,0.0f,0.0f,1.0f };
	vertexData_[1].texcoord = { 0.0f,0.0f };

	vertexData_[2].position = { 640.0f,360.0f,0.0f,1.0f };
	vertexData_[2].texcoord = { 1.0f,1.0f };

	vertexData_[3].position = { 0.0f,0.0f,0.0f,1.0f };
	vertexData_[3].texcoord = { 0.0f,0.0f };

	vertexData_[4].position = { 640.0f,0.0f,0.0f,1.0f };
	vertexData_[4].texcoord = { 1.0f,0.0f };

	vertexData_[5].position = { 640.0f,360.0f,0.0f,1.0f };
	vertexData_[5].texcoord = { 1.0f,1.0f };
	
	

	transform_ = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};



}

void Sprite::Update()
{

	Matrix4x4 worldmatrix = MakeAffinMatrix(transform_.scale, transform_.rotate, transform_.translate);
	Matrix4x4 viewMatrix = MakeIdentity4x4();
	Matrix4x4 projectionMatrix = MakeOrthographicmatrix(0.0f, 0.0f, float(winApp_->GetWidth()), float(winApp_->GetHeight()), 0.0f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldmatrix, Multiply(viewMatrix, projectionMatrix));
	*transformationMatrixData = worldViewProjectionMatrix;

}

void Sprite::Draw()
{
	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);	//VBVを設定
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, transformationmatrixResource->GetGPUVirtualAddress());
	
	//描画
	dxCommon_->GetCommandList()->DrawInstanced(6, 1, 0, 0);
}


/*=====================================*/
/* 　　　　   プライベートメソッド　　　    */
/*=====================================*/

void Sprite::VertexBuffer()
{
	//Sprite用の頂点リソースを作る
	vertexResource_ = engine_->CreateBufferResource(sizeof(VertexData) * 6);

	//リソースの先頭のアドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	//使用するリソースサイズは頂点6つ分のサイズ
	vertexBufferView_.SizeInBytes = sizeof(VertexData) * 6;
	//1頂点あたりのサイズ
	vertexBufferView_.StrideInBytes = sizeof(VertexData);

	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));
}

void Sprite::WvpBuffer()
{
	//トランスフォーメーションマトリックス用のリソースを作る
	transformationmatrixResource = engine_->CreateBufferResource(sizeof(Matrix4x4));
	//書き込むためのアドレスを取得
	transformationmatrixResource->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixData));
	//単位行列を書き込んでおく
	*transformationMatrixData = MakeIdentity4x4();
}
