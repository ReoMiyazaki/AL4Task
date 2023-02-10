#include "GameScene.h"

#include "Affine.h"
#include "Collision.h"
#include "CollisionPrimitive.h"
#include <sstream>
#include <iomanip>
#include <cassert>
#include <random>

using namespace DirectX;

//乱数生成装置
std::random_device seed_gen;
std::mt19937_64 engine(seed_gen());
std::uniform_real_distribution<float>distX(-20.0f, 20.0f);
std::uniform_real_distribution<float>distZ(0.0f, 100.0f);

GameScene::GameScene() {}

GameScene::~GameScene() {
	//3Dオブジェクト解放
	delete skydome;
	delete sphere1;
	delete sphere2;
	delete floor;

	//3Dモデル解放
	delete skydomeModel;
	delete sphere1;
	delete sphere2;
	delete floor;

	//オーディオ解放
	audio->Finalize();
	delete audio;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	// OBJからモデルデータを読み込み
	{
		skydomeModel = Model::LoadFromOBJ("skydome");
		/*sphere1Model = Model::LoadFromOBJ("sphere1");
		sphere2Model = Model::LoadFromOBJ("sphere1");
		floorModel = Model::LoadFromOBJ("floor");*/
	}
	//3Dオブジェクト生成
	{
		skydome = Object3d::Create();
		/*sphere1 = Object3d::Create();
		sphere2 = Object3d::Create();
		floor = Object3d::Create();*/
	}
	// オブジェクトにモデルを紐づける
	{
		skydome->SetModel(skydomeModel);
		/*sphere1->SetModel(sphere1Model);
		sphere2->SetModel(sphere2Model);
		floor->SetModel(floorModel);*/
	}
	// 3Dオブジェクトの位置を指定
	{
		/*sphere1->SetPosition({ 0,0,0 });
		sphere2->SetPosition({ 0,0,0 });
		floor->SetPosition({ 0,0,0 });*/
	}
	// 3Dオブジェクトの大きさを指定
	{
		skydome->SetScale({ 10000, 10000, 10000 });
		//floor->SetScale({ 50,1,50 });
	}
	// 当たり判定関係
	{
		// 弾の初期値を設定
		sphere.center = XMVectorSet(0, 2, 0, 1);	// 中心点座標
		sphere.radius = 1.0f;	// 半径
		// 平面の初期値を設定
		plane.normal = XMVectorSet(0, 2, 0, 1);	// 法線ベクトル
		plane.distance = 0.0f;	// 原点(0,0,0)からの距離
	}

	audio = new Audio();
	audio->Initialize();
}

void GameScene::Update() {
	skydome->Update();
	/*sphere1->Update();
	sphere2->Update();
	floor->Update();*/

	XMVECTOR moveX = XMVectorSet(0.01f, 0, 0, 0);
	XMVECTOR moveY = XMVectorSet(0, 0.01f, 0, 0);

	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// 移動後の座標を計算
		if (input->PushKey(DIK_RIGHT)) { sphere.center += moveX; }
		else if (input->PushKey(DIK_LEFT)) { sphere.center -= moveX; }
		if (input->PushKey(DIK_UP)) { sphere.center += moveY; }
		else if (input->PushKey(DIK_DOWN)) { sphere.center -= moveY; }
	}

	Collision::CheckSphere2Plane(sphere, plane);

	// stringstreamで変数の値を埋め込んで整形する
	std::ostringstream spherestr;
	spherestr << "Sphere:("
		<< std::fixed << std::setprecision(2)	// 小数点以下2桁まで
		<< sphere.center.m128_f32[0] << ","		// x
		<< sphere.center.m128_f32[1] << ","		// y
		<< sphere.center.m128_f32[2] << ")";	// z

}

void GameScene::Draw() {

	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// <summary>

	//3Dオブジェクトの描画
	skydome->Draw();
	/*sphere1->Draw();
	sphere2->Draw();
	floor->Draw();*/

	//3Dオブジェクト描画後処理
	Object3d::PostDraw();
}