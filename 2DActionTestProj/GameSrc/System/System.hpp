#pragma once
#include <DxLib.h>
#include <memory>
#include <assert.h>
#include "../Utility/FPS.hpp"
#include "../Utility/Utility.hpp"
//Dxlibの初期化とシステムのチェックを行います
class System
{
private:
	void SystemInit()
	{
		//ウィンドウがノンアクティブ時は実行しない
		SetAlwaysRunFlag(false);
		//ログ消し
		SetOutApplicationLogValidFlag(false);
		//縦横比維持
		SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
		//ウインドウタイトルを変更
		SetMainWindowText("Game");
		//画面サイズ変更
		SetGraphMode(SCREEN_WIDIH, SCREEN_HEIGHT,32);
		//ウィンドウモード変更
		ChangeWindowMode(WinMessageBox::IsFullScreen());
		//XAudio2を使用する(オーディオインターフェースを使用したときに、フルスクルーン時に正しく音が再生されなくなった(要検証))
		SetEnableXAudioFlag(true);
		//初期化
		DxLib_Init();
		assert(DxLib_IsInit());
		//裏画面設定
		SetDrawScreen(DX_SCREEN_BACK);
	}
	bool Processloop()
	{
		if (ScreenFlip() != 0) return false;
		if (ProcessMessage() != 0) return false;
		if (ClearDrawScreen() != 0) return false;
		return true;
	}
public:
	static FPS& GetFPS()
	{
		static std::unique_ptr<FPS> instance = std::make_unique<FPS>();
		return *instance;
	}
	static constexpr int
		SCREEN_WIDIH = 1560,
		SCREEN_HEIGHT = 960;
	System()
	{
		SystemInit();
	}

	~System()
	{
		DxLib_End();
	}

	bool IsOk()
	{
		GetFPS().UpDate();
		return Processloop();
	}
};