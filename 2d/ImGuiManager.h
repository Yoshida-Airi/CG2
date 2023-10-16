#pragma once
#include"WindowAPI.h"
#include"DirectXCommon.h"

#include"externals/imgui/imgui_impl_dx12.h"
#include"externals/imgui/imgui_impl_win32.h"

class ImGuiManager
{
public:
	~ImGuiManager();

	void Initialize();

	void Begin();

	void End();

	void Draw();

private:
	WindowAPI* winApp_ = WindowAPI::GetInstance();
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	
	ID3D12DescriptorHeap* srvDescriptorHeap_ = nullptr;



};

