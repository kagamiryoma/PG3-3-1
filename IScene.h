#pragma once
enum SceneType {
	ktitle,     // タイトルシーン
	kState,     // ステージシーン
	kClear,     // クリアシーン
	kSceneMax   // シーンの最大数
};

class IScene
{
protected:
	static int sceneNo;
	char* keys_;
	char* preKeys_;
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual ~IScene();

	int GetSceneNo();

	void SetKeys(char* keys, char* preKeys);
};

