#include "Triangle.h"

/*=====================================*/
/* 　　　　   パブリックメソッド　　　	　 */
/*=====================================*/

Triangle::~Triangle()
{
	vertexResource_->Release();
	materialResource_->Release();
	wvpResource_->Release();
}

void Triangle::Initialize(WindowAPI* winApp, DirectXCommon* direct, MyEngine* engien)
{
	winApp_ = winApp;
	dxCommon_ = direct;
	engine_ = engien;
	

	kClientHeight_ = winApp_->GetHeight();
	kClientWidth_ = winApp_->GetWidth();

	cameraTransform_ =
	{
		{1.0f, 1.0f, 1.0f }, 
		{0.0f, 0.0f, 0.0f },
		{0.0f, 0.0f, -5.0f}
	};

	VertexBuffer();
	MaterialBuffer();
	WvpBuffer();



	

}

void Triangle::Update(const TriangleData& data)
{

	ImGui::Begin("camera");

	float translate[] = { cameraTransform_.translate.x,cameraTransform_.translate.y,cameraTransform_.translate.z };

	ImGui::SliderFloat3("translate", translate, -5.0f, 1.0f);

	cameraTransform_.translate.x = translate[0];
	cameraTransform_.translate.y = translate[1];
	cameraTransform_.translate.z = translate[2];


	float scale[] = { cameraTransform_.scale.x,cameraTransform_.scale.y,cameraTransform_.scale.z };


	ImGui::SliderFloat3("scale", scale, 0.1f, 1.0f);

	cameraTransform_.scale.x = scale[0];
	cameraTransform_.scale.y = scale[1];
	cameraTransform_.scale.z = scale[2];

	float rotate[] = { cameraTransform_.rotate.x,cameraTransform_.rotate.y,cameraTransform_.rotate.z };

	ImGui::SliderFloat3("rotate", rotate, 0.0f, 5.0f);

	cameraTransform_.rotate.x = rotate[0];
	cameraTransform_.rotate.y = rotate[1];
	cameraTransform_.rotate.z = rotate[2];

	ImGui::End();

	//頂点の設定
	vertexData_[0] = data.vertex[0];
	vertexData_[1] = data.vertex[1];
	vertexData_[2] = data.vertex[2];


	//色の設定
	materialData_[0] = data.color;

	transform_ = data.transform;

	*wvpData_ = MakeIdentity4x4();




	//ImGui::Begin("Rotate");

	//ImGui::Checkbox("true", &isRotate);

	//ImGui::End();

	//if (isRotate == true)
	//{
	//	transform_.rotate.y += 0.03f;
	//}

	worldMatrix_ = MakeAffinMatrix(transform_.scale, transform_.rotate, transform_.translate);
	*wvpData_ = worldMatrix_;

	Matrix4x4 cameraMatrix = MakeAffinMatrix(cameraTransform_.scale, cameraTransform_.rotate, cameraTransform_.translate);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kClientWidth_) / float(kClientHeight_), 0.1f, 100.0f);
	//WVPMatrixを作る
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix_, Multiply(viewMatrix, projectionMatrix));
	*wvpData_ = worldViewProjectionMatrix;

}


void Triangle::Draw()
{
	

	//VBVを設定
	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);
	//形状を設定。PS0にせっていしているものとはまた別。同じものを設定する
	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//マテリアルCBufferの場所を設定
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	//wvp用のCbufferの場所を設定
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource_->GetGPUVirtualAddress());
	//描画
	dxCommon_->GetCommandList()->DrawInstanced(3, 1, 0, 0);

}


/*=====================================*/
/* 　　　　   プライベートメソッド　　　    */
/*=====================================*/

void Triangle::VertexBuffer()
{
	vertexResource_ = engine_->CreateBufferResource(sizeof(Vector4) * 3);	//頂点用のデータ

	//リソースの先頭のアドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点3つ分のサイズ
	vertexBufferView_.SizeInBytes = sizeof(Vector4) * 3;
	//1頂点当たりのサイズ
	vertexBufferView_.StrideInBytes = sizeof(Vector4);
	//書き込むためのアドレスを取得
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));
}

void Triangle::MaterialBuffer()
{
	materialResource_ = engine_->CreateBufferResource(sizeof(Vector4));	//マテリアル用のデータ

	//書き込むためのアドレスを取得
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
}

void Triangle::WvpBuffer()
{
	//wvp用のリソースを作る。Matrix4x4　1つ分のサイズを用意する
	wvpResource_ = engine_->CreateBufferResource(sizeof(Matrix4x4));
	//書き込むためのアドレスを取得
	wvpResource_->Map(0, nullptr, reinterpret_cast<void**>(&wvpData_));
	//単位行列を書き込んでおく
	*wvpData_ = MakeIdentity4x4();
}

