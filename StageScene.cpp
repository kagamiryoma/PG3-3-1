#include "StageScene.h"
#include "Novice.h"

void StageScene::Init()
{
	
}

void StageScene::Update()
{


	if (keys_[DIK_W])
	{
		playerPosY -= speed;
	}

	if (keys_[DIK_S])
	{
		playerPosY += speed;
	}

	if (keys_[DIK_A])
	{
		playerPosX -= speed;
	}

	if (keys_[DIK_D])
	{
		playerPosX += speed;
	}

	if (keys_[DIK_UP])
	{
		playerPosY -= speed;
	}

	if (keys_[DIK_DOWN])
	{
		playerPosY += speed;
	}

	if (keys_[DIK_LEFT])
	{
		playerPosX -= speed;
	}

	if (keys_[DIK_RIGHT])
	{
		playerPosX += speed;
	}

	if (isBulletshot == 0)
	{
		if (keys_[DIK_RETURN] && preKeys_[DIK_RETURN] == 0)
		{
			// 弾の座標とプレイヤーの座標が同じになる
			BulletPosX = playerPosX;
			BulletPosY = playerPosY;
			// 弾を発射する
			isBulletshot = 1;
		}
	}

	if (isEnemyAlive == 1)
	{
		enemyPosX = enemyPosX + enemyspeed;

		if (enemyPosX + enemyRadius >= 1280)
		{
			enemyspeed = -3;
		}
		if (enemyPosX - enemyRadius <= 0)
		{
			enemyspeed = 3;
		}
	}

	if (isBulletshot == 1)
	{
		//　弾を上に飛ばす
		BulletPosY -= BulletSpeed;

		if (BulletPosY <= 0)
		{
			isBulletshot = 0;
		}
	}

	if (playerPosX >= 1280 - playerRadius)
	{
		playerPosX = 1280 - playerRadius;
	}

	if (playerPosX <= playerRadius)
	{
		playerPosX = playerRadius;
	}

	if (playerPosY >= 720 - playerRadius)
	{
		playerPosY = 720 - playerRadius;
	}

	if (playerPosY <= playerRadius)
	{
		playerPosY = playerRadius;
	}

	if (isBulletshot == 1 && isEnemyAlive == 1)
	{
		// 当たり判定を計算する
		int dx = enemyPosX - BulletPosX; // X2 - X1
		int dy = enemyPosY - BulletPosY; // Y2 - Y1
		// 円の中心を計算する(右辺)
		int d = dx * dx + dy * dy;
		//半径と半径を足して２乗する(左辺)
		int r = (enemyRadius + BulletRadius) * (enemyRadius + BulletRadius);


		//　左辺 == 右辺 または 左辺 > 右辺　か
		if (r == d || r > d)
		{
			//当たっている！
			isBulletshot = 0;
			//敵を消す
			isEnemyAlive = 0;

		}
	}

	if (isEnemyAlive == 0)
	{
		//復活用タイマーを1減らす
		respawnTimer--;
		//復活用タイマーが0になったら
		if (respawnTimer <= 0)
		{
			//敵を復活させる
			isEnemyAlive = 1;
			//タイマーを120に戻す
			respawnTimer = 120;
		}
	}

	// スペース押し時、クリアシーンに移行
	if (isEnemyAlive == 0) {
		sceneNo = kClear;
		isEnemyAlive = 1;
	}
}

void StageScene::Draw()
{
	Novice::ScreenPrintf(1280 / 2, 720 / 2, "StageScene");

	Novice::DrawEllipse(playerPosX, playerPosY, playerRadius, playerRadius, 0.0f, RED, kFillModeSolid);
	if (isBulletshot == 1)
	{
		Novice::DrawTriangle(
			BulletPosX,      //　上X
			BulletPosY - 10,      //　上Y
			BulletPosX - 10, //　左下X
			BulletPosY + 20 - 10, //　左下Y
			BulletPosX + 10, //　右下X
			BulletPosY + 20 - 10, //　右下Y
			RED, kFillModeSolid);
	}

	if (isEnemyAlive == 1)
	{
		Novice::DrawEllipse(enemyPosX, enemyPosY, enemyRadius, enemyRadius, 0.0f, 0xFFFFFFFF, kFillModeSolid);
	}
}
