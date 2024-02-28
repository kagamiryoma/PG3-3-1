#pragma once
#include "IScene.h"
class StageScene : public IScene
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;

	int playerPosX = 640;
	int playerPosY = 360;
	int playerRadius = 20;
	int speed = 5;

	int BulletPosX = 0;
	int BulletPosY = 0;
	int BulletSpeed = 5;
	int isBulletshot = 0; //弾を発射しているかフラグ
	int BulletRadius = 10; //弾の半径

	int enemyPosX = 640;
	int enemyPosY = 32;
	int enemyRadius = 20;
	int enemyspeed = 3;
	int isEnemyAlive = 1; // 0;生存していない 1;生存している

	//復活用タイマー
	int respawnTimer = 120;
};

