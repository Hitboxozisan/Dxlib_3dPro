#include <mutex>
#include <cassert>
#include "SingletonFainalizer.h"


namespace
{
	// ����������s����C���X�^���X�̍ő吔
	constexpr int finalizersSizeMax = 256;
	std::mutex Mutex;
	// ��������ɓo�^����Ă���C���X�^���X�̐�
	int finalizerNum = 0;
	// ��������p�̊֐�
	SingletonFainalizer::FinalizerFunc finalizerFunc[finalizersSizeMax];
}

void SingletonFainalizer::AddFinalizer(FinalizerFunc func)
{
	//  �r��������s��
	std::lock_guard<std::mutex> lock(Mutex);
	//  �o�^�ł���C���X�^���X���𒴂�����G���[���o��
	assert(finalizerNum < finalizersSizeMax);
	//  �C���X�^���X����������ɓo�^
	finalizerFunc[finalizerNum++] = func;
}

void SingletonFainalizer::Fainalize()
{
	//  �r��������s��
	std::lock_guard<std::mutex> lock(Mutex);
	//  �o�^����Ă���C���X�^���X��S�ĉ������
	for (int i = finalizerNum - 1; i >= 0; --i) {
		(*finalizerFunc[i])();
	}
	finalizerNum = 0;
}
