#pragma once


/// <summary>
/// �V���O���g���N���X�I������
/// </summary>
class SingletonFainalizer
{
public:
	/// <summary>
	/// ���̃N���X�̊֐��𗘗p���邽�߂̐錾
	/// </summary>
	using FinalizerFunc = void(*)();

	// �V���O���g���N���X�̏I���������ɉ�������C���X�^���X�̓o�^
	static void AddFinalizer(FinalizerFunc func);
	// �V���O���g���N���X�̏I������
	static void Fainalize();
};

