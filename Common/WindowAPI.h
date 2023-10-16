#pragma once
#include <windows.h>
#include<cstdint>
#include<d3d12.h>
#include<dxgidebug.h>

#include"externals/imgui/imgui.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class WindowAPI
{
public:

	/*=====================================*/
	/* 　　　　   パブリックメソッド　　　	　 */
	/*=====================================*/

	/// <summary>
	/// コンストラクタ
	/// </summary>
	WindowAPI();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~WindowAPI();

	/// <summary>
	/// アプリケーションの開始
	/// </summary>
	void StartApp(const wchar_t* title);

	/// <summary>
	/// メッセージの処理
	/// </summary>
	/// <returns>終了かどうか</returns>
	static bool ProcessMessage();

	//ゲッター
	HWND GetHwnd() const { return hwnd_; }
	int32_t GetWidth() const { return Width_; };
	int32_t GetHeight() const { return Height_; };
	WNDCLASS GetWinCLASS()const { return wc_; };

public:
	//アプリケーションの開始
	static const uint32_t kWindowWidth = 1280;
	static const uint32_t kWindowHeight = 720;




	/*=====================================*/
	/* 　　　　   プライベート変数    　       */
	/*=====================================*/
private:
	//タイトル
	const wchar_t* Title_ = nullptr;

	HWND hwnd_ = nullptr;			//ウィンドウハンドル
	int32_t Width_ = 0;		//ウィンドウの横幅
	int32_t Height_ = 0;	//ウィンドウの縦幅

	RECT wrc_ = {};

	//ウィンドウクラスの登録(設定をWindowsに伝える)
	WNDCLASS wc_ = {};


private:
	/*=====================================*/
	/* 　　　　   プライベートメソッド　　　     */
	/*=====================================*/

	//初期化
	bool Initialize(const wchar_t* title);
	//ウィンドウクラスを登録
	bool InitializeWindow(const wchar_t* title);

	//ウィンドウプロシージャ
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


};