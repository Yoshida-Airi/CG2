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

void Triangle::Initialize(WindowAPI* winApp, DirectXCommon* direct, MyEngine* engien,const TriangleData& data)
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



	//頂点の設定
	vertexData_[0] = data.vertex[0];
	vertexData_[1] = data.vertex[1];
	vertexData_[2] = data.vertex[2];


	//色の設定
	materialData_[0] = data.color;

	transform_ = data.transform;

	*wvpData_ = MakeIdentity4x4();

}

void Triangle::Update()
{
	
	ImGui::Begin("triangle");

	float color[] = { materialData_[0].x,materialData_[0].y,materialData_[0].z,materialData_[0].w};

	ImGui::ColorEdit4("color", color);


	materialData_[0].x = color[0];
	materialData_[0].y = color[1];
	materialData_[0].z = color[2];
	materialData_[0].w = color[3];

	float translate[] = { transform_.translate.x,transform_.translate.y,transform_.translate.z};


	ImGui::SliderFloat3("translate", translate, -1.0f, 1.0f);

	transform_.translate.x = translate[0];
	transform_.translate.y = translate[1];
	transform_.translate.z = translate[2];

	float scale[] = { transform_.scale.x,transform_.scale.y,transform_.scale.z };


	ImGui::SliderFloat3("scale", scale, 0.0f, 10.0f);

	transform_.scale.x = scale[0];
	transform_.scale.y = scale[1];
	transform_.scale.z = scale[2];

	float rotate[] = { transform_.rotate.x,transform_.rotate.y,transform_.rotate.z };

	ImGui::SliderFloat3("rotate", rotate, -1.0f, 1.0f);

	transform_.rotate.x = rotate[0];
	transform_.rotate.y = rotate[1];
	transform_.rotate.z = rotate[2];


	ImGui::End();


	ImGui::Begin("Rotate");

	ImGui::Checkbox("true", &isRotate);

	ImGui::End();

	if (isRotate == true)
	{
		transform_.rotate.y += 0.03f;
	}

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

