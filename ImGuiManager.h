#pragma once
#include"WindowAPI.h"
#include"DirectXCommon.h"

#include"externals/imgui/imgui_impl_dx12.h"
#include"externals/imgui/imgui_impl_win32.h"

class ImGuiManager
{
public:
	~ImGuiManager();

	void Initialize(WindowAPI* winApp, DirectXCommon* dxCommon);

	void Begin();

	void End();

private:
	WindowAPI* winApp_;
	DirectXCommon* dxCommon_;
	
	ID3D12DescriptorHeap* srvDescriptorHeap_ = nullptr;



};

