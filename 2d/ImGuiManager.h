#pragma once
#include"WindowAPI.h"
#include"DirectXCommon.h"

#include"externals/imgui/imgui_impl_dx12.h"
#include"externals/imgui/imgui_impl_win32.h"

class ImGuiManager
{
public:


	/// <summary>
	/// シングルトン
	/// </summary>
	/// <returns></returns>
	static ImGuiManager* GetInstance()
	{
		if (instance == NULL)
		{
			instance = new ImGuiManager;
		}
		return instance;
	}

	~ImGuiManager();

	void Initialize(WindowAPI* winApp, DirectXCommon* dxCommon);

	void Begin();

	void End();

	void Draw();

private:
	WindowAPI* winApp_;
	DirectXCommon* dxCommon_;
	
	ID3D12DescriptorHeap* srvDescriptorHeap_ = nullptr;

	static ImGuiManager* instance;	//シングルトン


};

