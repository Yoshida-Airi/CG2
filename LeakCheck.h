#pragma once
#include<Windows.h>
#include<wrl.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<dxgidebug.h>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")

struct D3DResourceLeakChecker
{
	~D3DResourceLeakChecker()
	{
		//リソースリークチェック
		Microsoft::WRL::ComPtr< IDXGIDebug1> debug;
		if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug))))
		{
			debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
			debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
			debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
			debug->Release();
		}
	}
};