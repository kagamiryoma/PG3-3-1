#include "GameManager.h"
#include "Novice.h"

GameManager::GameManager()
{
	sceneArr_[ktitle] = std::make_unique<TitleScene>();
	sceneArr_[kState] = std::make_unique<StageScene>();
	sceneArr_[kClear] = std::make_unique<ClearScene>();

	for (int i = 0; i < kSceneMax; i++) {
		sceneArr_[i]->SetKeys(keys_, preKeys_);
	}

	currentSceneNo_ = ktitle;
}

GameManager::~GameManager()
{
}

int GameManager::Run()
{
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys_, keys_, 256);
		Novice::GetHitKeyStateAll(keys_);

		preSceneNo_ = currentSceneNo_;
		currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo();

		if (preSceneNo_ != currentSceneNo_) {
			sceneArr_[currentSceneNo_]->Init();
		}

		///
		/// ↓更新処理ここから
		///

		sceneArr_[currentSceneNo_]->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		sceneArr_[currentSceneNo_]->Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys_[DIK_ESCAPE] == 0 && keys_[DIK_ESCAPE] != 0) {
			break;
		}
	}


	return 0;
}
