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
/// �Q�[���V�[��
/// </summary>
class GameScene
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // �ÓI�����o�ϐ�
	static const int debugTextTexNumber = 0;

public: // �����o�֐�

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private: // �����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;

	// �����蔻�� ��
	Sphere sphere;
	// �����蔻�� ����
	Plane plane;

	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
	
	//Sprite* �ϐ��� = new Sprite();
	//XMFLOAT2 �ϐ��� = Sprite�̕ϐ���->GetPosition();

	Object3d* skydome = nullptr;
	Object3d* sphere1 = nullptr;
	Object3d* sphere2 = nullptr;
	Object3d* floor = nullptr;

	Model* skydomeModel = nullptr;
	Model* sphere1Model = nullptr;
	Model* sphere2Model = nullptr;
	Model* floorModel = nullptr;

	// �����������ǂ���
	int isHit = 0;
};

