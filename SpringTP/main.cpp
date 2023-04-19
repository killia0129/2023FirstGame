#include"DxLib.h"
#include"Camera.h"
#include"SpringBase.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init()==-1)
	{
		return -1;
	}
	ChangeWindowMode(false);
	SetUseLighting(false);
	SetGraphMode(1920, 1080, 32);
	SetDrawScreen(DX_SCREEN_BACK);
	SetCameraNearFar(1.0f, 499.0f);
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), VGet(0.0f, 0.0f, 250.0f));

	//デバッグ用
	SpringBase* spring = new SpringBase(VGet(0, -100, -100), VGet(0, -1, 0), 30.f, 5.f, 0.0f, 0.0f, 0.0f);
	Camera* camera = new Camera(ZERO_POS);

	while (!CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClearDrawScreen();
		camera->Update(0.16f);
		spring->Draw();
		ScreenFlip();
	}
}