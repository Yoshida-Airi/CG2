#pragma once
#include"Vector3.h"
#include"Vector4.h"
#include"Vector2.h"
#include"Matrix4x4.h"
#include<stdint.h>

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
	Vector3 normal;
};

struct Material
{
	Vector4 color;
	int32_t enableLighting;
	float padding[3];
	Matrix4x4 uvTransform;
};

struct TransformationMatrix
{
	Matrix4x4 WVP;
	Matrix4x4 World;
};

struct DirectionalLight
{
	Vector4 color;
	Vector3 direction;
	float intensity;
};

