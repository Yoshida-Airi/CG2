#pragma once
#define DIRECTINPUT_VERSION 0x0800	//DirectInputのバージョン指定
#include<dinput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include<cassert>

#include"WindowAPI.h"

class Input
{
public:
	void Initialize(WindowAPI* winApp);

	void Update();

	/*void Draw();*/

	bool IsPressKey(uint8_t key);	//キーを押した状態か
	bool IsTriggerKey(uint8_t key);	//キーを押した瞬間か
	bool IsReleaseKey(uint8_t key); //キーを離した瞬間か
	
	/// <summary>
	/// キーの押下をチェック
	/// </summary>
	/// <param name="keyNumber">キー番号</param>
	/// <returns>押されているか</returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// キーのトリガーをチェック
	/// </summary>
	/// <param name="keyNumber">キー番号</param>
	/// <returns>トリガーかどうか</returns>
	bool TriggerKey(BYTE keyNumber);

private:

	WindowAPI* winApp_;

	IDirectInput8* directInput = nullptr;
	IDirectInputDevice8* keyboard = nullptr;	//キーボードデバイス
	BYTE key[256] = {};
	BYTE keyPre[256] = {};	//前回の全キーの状態
};