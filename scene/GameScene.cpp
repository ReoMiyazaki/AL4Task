#include "GameScene.h"

#include "Affine.h"
#include "Collision.h"
#include "CollisionPrimitive.h"
#include <sstream>
#include <iomanip>
#include <cassert>
#include <random>

using namespace DirectX;

//�����������u
std::random_device seed_gen;
std::mt19937_64 engine(seed_gen());
std::uniform_real_distribution<float>distX(-20.0f, 20.0f);
std::uniform_real_distribution<float>distZ(0.0f, 100.0f);

GameScene::GameScene() {}

GameScene::~GameScene() {
	//3D�I�u�W�F�N�g���
	delete skydome;
	delete sphere1;
	delete sphere2;
	delete floor;

	//3D���f�����
	delete skydomeModel;
	delete sphere1;
	delete sphere2;
	delete floor;

	//�I�[�f�B�I���
	audio->Finalize();
	delete audio;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//�X�v���C�g���ʕ����̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	// OBJ���烂�f���f�[�^��ǂݍ���
	{
		skydomeModel = Model::LoadFromOBJ("skydome");
		/*sphere1Model = Model::LoadFromOBJ("sphere1");
		sphere2Model = Model::LoadFromOBJ("sphere1");
		floorModel = Model::LoadFromOBJ("floor");*/
	}
	//3D�I�u�W�F�N�g����
	{
		skydome = Object3d::Create();
		/*sphere1 = Object3d::Create();
		sphere2 = Object3d::Create();
		floor = Object3d::Create();*/
	}
	// �I�u�W�F�N�g�Ƀ��f����R�Â���
	{
		skydome->SetModel(skydomeModel);
		/*sphere1->SetModel(sphere1Model);
		sphere2->SetModel(sphere2Model);
		floor->SetModel(floorModel);*/
	}
	// 3D�I�u�W�F�N�g�̈ʒu���w��
	{
		/*sphere1->SetPosition({ 0,0,0 });
		sphere2->SetPosition({ 0,0,0 });
		floor->SetPosition({ 0,0,0 });*/
	}
	// 3D�I�u�W�F�N�g�̑傫�����w��
	{
		skydome->SetScale({ 10000, 10000, 10000 });
		//floor->SetScale({ 50,1,50 });
	}
	// �����蔻��֌W
	{
		// �e�̏����l��ݒ�
		sphere.center = XMVectorSet(0, 2, 0, 1);	// ���S�_���W
		sphere.radius = 1.0f;	// ���a
		// ���ʂ̏����l��ݒ�
		plane.normal = XMVectorSet(0, 2, 0, 1);	// �@���x�N�g��
		plane.distance = 0.0f;	// ���_(0,0,0)����̋���
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

	// �I�u�W�F�N�g�ړ�
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// �ړ���̍��W���v�Z
		if (input->PushKey(DIK_RIGHT)) { sphere.center += moveX; }
		else if (input->PushKey(DIK_LEFT)) { sphere.center -= moveX; }
		if (input->PushKey(DIK_UP)) { sphere.center += moveY; }
		else if (input->PushKey(DIK_DOWN)) { sphere.center -= moveY; }
	}

	Collision::CheckSphere2Plane(sphere, plane);

	// stringstream�ŕϐ��̒l�𖄂ߍ���Ő��`����
	std::ostringstream spherestr;
	spherestr << "Sphere:("
		<< std::fixed << std::setprecision(2)	// �����_�ȉ�2���܂�
		<< sphere.center.m128_f32[0] << ","		// x
		<< sphere.center.m128_f32[1] << ","		// y
		<< sphere.center.m128_f32[2] << ")";	// z

}

void GameScene::Draw() {

	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());
	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// <summary>

	//3D�I�u�W�F�N�g�̕`��
	skydome->Draw();
	/*sphere1->Draw();
	sphere2->Draw();
	floor->Draw();*/

	//3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
}