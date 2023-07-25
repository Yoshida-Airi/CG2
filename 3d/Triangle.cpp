#include "Triangle.h"

/*=====================================*/
/* 　　　　   パブリックメソッド　　　	　 */
/*=====================================*/


void Triangle::Initialize(DirectXCommon* direct)
{
	dxCommon_ = direct;

}

void Triangle::Draw(Vector4* position, ID3D12Resource* resource)
{

	VertexData(position, resource);

	//VBVを設定
	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);
	//形状を設定。PS0にせっていしているものとはまた別。同じものを設定する
	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//描画
	dxCommon_->GetCommandList()->DrawInstanced(3, 1, 0, 0);
}

void Triangle::End()
{
	vertexResource_->Release();
}


/*=====================================*/
/* 　　　　   プライベートメソッド　　　    */
/*=====================================*/

void Triangle::VertexData(Vector4* position, ID3D12Resource* resource)
{
	//リソースの先頭のアドレスから使う
	vertexBufferView_.BufferLocation = resource->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点3つ分のサイズ
	vertexBufferView_.SizeInBytes = sizeof(Vector4) * 3;
	//1頂点当たりのサイズ
	vertexBufferView_.StrideInBytes = sizeof(Vector4);
	//書き込むためのアドレスを取得
	resource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));



	vertexData_[0] = position[0];
	vertexData_[1] = position[1];
	vertexData_[2] = position[2];


}

