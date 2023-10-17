#include"WindowAPI.h"

/*=====================================*/
/* 　　　　   パブリックメソッド　　　 　    */
/*=====================================*/

WindowAPI* WindowAPI::GetInstance()
{
	if (instance == NULL)
	{
		instance = new WindowAPI;
	}
	return instance;
}

//コンストラクタ
WindowAPI::WindowAPI()
{

}

//デストラクタ
WindowAPI::~WindowAPI()
{
	CloseWindow(hwnd_);
}

//開始
void WindowAPI::StartApp(const wchar_t* title, int32_t width, int32_t height)
{
	Initialize(title, width, height);
}



bool WindowAPI::ProcessMessage()
{
	
	MSG msg{}; // メッセージ

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // メッセージがある？
	{
		TranslateMessage(&msg); // キー入力メッセージの処理
		DispatchMessage(&msg);  // ウィンドウプロシージャにメッセージを送る
	}

	if (msg.message == WM_QUIT) // 終了メッセージが来たらループを抜ける
	{
		return true;
	}

	return false;
};


/*=====================================*/
/* 　　　　   プライベートメソッド　　　    */
/*=====================================*/

//ウィンドウプロシージャ
LRESULT CALLBACK WindowAPI::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
	{
		return true;
	}


	//メッセージに応じてゲーム固有の処理を行う
	switch (msg)
	{
		//ウィンドウが破壊された
	case WM_DESTROY:
		//OSに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}
	//標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

//ウィンドウの初期化
bool WindowAPI::Initialize(const wchar_t* title, int32_t width, int32_t height)
{
	if (!InitializeWindow(title, width, height))
	{
		return false;
	}
	return true;
}



//ウィンドウクラスの登録(初期化)
bool WindowAPI::InitializeWindow(const wchar_t* title, int32_t width, int32_t height)
{
	Title_ = title;
	Width_ = width;
	Height_ = height;

	//ウィンドウクラスの登録(設定をWindowsに伝える)
	//ウィンドウプロシージャ
	wc_.lpfnWndProc = WindowProc;
	//ウィンドウクラス名(なんでも良い)
	wc_.lpszClassName = L"CG2WindowClass";
	//インスタンスハンドル
	wc_.hInstance = GetModuleHandle(nullptr);
	//カーソル
	wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);

	//ウィンドウの登録
	RegisterClass(&wc_);

	//ウィンドウサイズを表す構造体にクライアント領域を入れる
	wrc_ = { 0,0,Width_,Height_ };

	//クライアント領域をもとに実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc_, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウの生成
	hwnd_ = CreateWindow
	(
		wc_.lpszClassName,		//利用するクラス名
		Title_,					//タイトルバーの文字(何でも良い)
		WS_OVERLAPPEDWINDOW,	//よく見るウィンドウスタイル
		CW_USEDEFAULT,			//表示X座標(Windowsに任せる)
		CW_USEDEFAULT,			//表示Y座標(WindowsOSに任せる)
		wrc_.right - wrc_.left,	//ウィンドウ横幅
		wrc_.bottom - wrc_.top,	//ウィンドウ縦幅
		nullptr,				//親ウィンドウハンドル
		nullptr,				//メニューハンドル
		wc_.hInstance,			//インスタンスハンドル
		nullptr					//オプション
	);



	if (hwnd_ == nullptr)
	{
		return false;
	}

	//ウィンドウを表示する
	ShowWindow(hwnd_, SW_SHOW);


	return true;

}

//静的メンバ変数の宣言と初期化
WindowAPI* WindowAPI::instance = NULL;
