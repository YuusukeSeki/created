//*****************************************************************************
//
//		�X�J�C�h�[��
//													Autohr : Yusuke Seki
//*****************************************************************************
#include "SkyDome.h"


// �R���X�g���N�^
SkyDome::SkyDome() : ObjectModel(Object::TYPE::TYPE_MODEL_SKYDOME)
{

}

// �R���X�g���N�^
SkyDome::SkyDome(Object::TYPE type) : ObjectModel(type)
{

}

// �f�X�g���N�^
SkyDome::~SkyDome()
{
	Uninit();

}


// ��������
SkyDome* SkyDome::Create(D3DXVECTOR3& position, const char* FileName)
{
	// �������̊m��
	SkyDome* pSkyDome = new SkyDome;

	// ����������
	pSkyDome->Init(position, FileName);

	// ���������X�J�C�h�[����Ԃ�
	return pSkyDome;

}

// ����������
void SkyDome::Init(D3DXVECTOR3& position, const char* FileName)
{
	// �p���f�[�^�̏���������
	ObjectModel::Init(position, FileName);

}

// �I������
void SkyDome::Uninit(void)
{
	// �p���f�[�^�̏I������
	ObjectModel::Uninit();
	
}

// �X�V����
void SkyDome::Update(void)
{
}

// �`�揈��
void SkyDome::Draw(void)
{
	// �`��
	ObjectModel::Draw();

}

