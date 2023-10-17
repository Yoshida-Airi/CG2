#pragma once
#include"Vector3.h"
#include"Matrix4x4.h"
#include"MathUtilty.h"

class Camera
{
public:
	void Initialize();

	void Update();

	void Draw();

private:
	//X,Y,Z軸周りのローカル回転角
	Vector3 rotation_ = { 0,0,0 };
	//ローカル座標
	Vector3 translation_ = { 0,0,-50 };
	//ビュー行列
	Matrix4x4 viewMatrix;
	//射影行列
	Matrix4x4 projectionMatrix;
};

