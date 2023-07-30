#include "ImGuiManager.h"

ImGuiManager::~ImGuiManager()
{
	srvDescriptorHeap_->Release();
}

void ImGuiManager::Initialize(WindowAPI* winApp, DirectXCommon* dxCommon)
{
	winApp_ = winApp;
	dxCommon_ = dxCommon;

	srvDescriptorHeap_ = dxCommon_->CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 128, true);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(winApp_->GetHwnd());
	ImGui_ImplDX12_Init(dxCommon_->GetDevice(),
		dxCommon_->GetSwapChainDesc().BufferCount,
		dxCommon_->GetRtvDesc().Format,
		srvDescriptorHeap_,
		srvDescriptorHeap_->GetCPUDescriptorHandleForHeapStart(),
		srvDescriptorHeap_->GetGPUDescriptorHandleForHeapStart());


}


void ImGuiManager::Begin()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::End()
{

}