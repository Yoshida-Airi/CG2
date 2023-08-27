#pragma once
#include"Vector3.h"
#include"Vector4.h"
#include"Vector2.h"


struct Transform
{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};


struct VertexData
{
	Vector4 position;
	Vector2 texcoord;
};
