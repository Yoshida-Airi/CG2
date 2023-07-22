#pragma once
#include"DirectX.h"
#include"Vector4.h"

class MyEngine;

class Triangle
{

public:
	void Initialize(DirectX* direct, const Vector4& a, const Vector4& b, const Vector4& c);

	void Draw();

	void End();


private:
	MyEngine* engine_;

	DirectX* direct_;

	Vector4* vertexData_;

	ID3D12Resource* vertexResource_;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;

private:
	void SetVertex();



};
