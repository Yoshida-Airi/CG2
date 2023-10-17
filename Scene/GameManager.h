#pragma once
#include"GamePlayScene.h"

class GameManager
{
public:

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

private:
	GamePlayScene* gameScene = nullptr;

};

