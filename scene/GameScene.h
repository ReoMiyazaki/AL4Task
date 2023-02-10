#pragma once

#include "CollisionPrimitive.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Audio.h"
#include <string>


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;

	// 当たり判定 球
	Sphere sphere;
	// 当たり判定 平面
	Plane plane;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	//Sprite* 変数名 = new Sprite();
	//XMFLOAT2 変数名 = Spriteの変数名->GetPosition();

	Object3d* skydome = nullptr;
	Object3d* sphere1 = nullptr;
	Object3d* sphere2 = nullptr;
	Object3d* floor = nullptr;

	Model* skydomeModel = nullptr;
	Model* sphere1Model = nullptr;
	Model* sphere2Model = nullptr;
	Model* floorModel = nullptr;

	// 当たったかどうか
	int isHit = 0;
};

