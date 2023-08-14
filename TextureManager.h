#pragma once
#include"externals/DirectXTex/DirectXTex.h"

class TextureManager
{
public:
	/// <summary>
	///	初期化
	/// </summary>
	void Initialize();

	void Updata();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();
};

