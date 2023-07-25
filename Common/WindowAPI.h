#pragma once
#include <windows.h>
#include<cstdint>
#include<d3d12.h>
#include<dxgidebug.h>

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
	void StartApp(const wchar_t* title, int32_t width, int32_t height);

	/// <summary>
	/// メッセージの処理
	/// </summary>
	/// <returns>終了かどうか</returns>
	static bool ProcessMessage();

	//ゲッター
	HWND GetHwnd() const { return hwnd_; }
	int32_t GetWidth() const { return Width_; };
	int32_t GetHeight() const { return Height_; };

private:
	/*=====================================*/
	/* 　　　　   プライベート変数    　       */
	/*=====================================*/

	//タイトル
	const wchar_t* Title_ = nullptr;
	HINSTANCE hInst_ = {};	//インスタンスハンドル
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
	bool Initialize(const wchar_t* title, int32_t width, int32_t height);
	//ウィンドウクラスを登録
	bool InitializeWindow(const wchar_t* title, int32_t width, int32_t height);

	//ウィンドウプロシージャ
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


};