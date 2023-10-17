#pragma once
#include"WindowAPI.h"
#include"DirectXCommon.h"

#include"externals/imgui/imgui_impl_dx12.h"
#include"externals/imgui/imgui_impl_win32.h"

class ImGuiManager
{
public:

	static ImGuiManager* GetInstance();

	~ImGuiManager();

	void Initialize();

	void Begin();

	void End();

	void Draw();

	static ImGuiManager* instance;

private:
	WindowAPI* winApp_;
	DirectXCommon* dxCommon_;
	
	ID3D12DescriptorHeap* srvDescriptorHeap_ = nullptr;



};

