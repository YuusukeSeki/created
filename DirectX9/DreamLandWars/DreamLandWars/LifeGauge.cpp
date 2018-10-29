//*****************************************************************************
//
//		�̗̓Q�[�W�i���_�j
//													Author : Yusuke Seki
//*****************************************************************************
#include "LifeGauge.h"
#include "MainGame.h"
#include "list_LoadTexture_MainGame.h"
#include "Effect3D.h"
#include "tower.h"
#include "camera.h"



//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
LifeGauge::LifeGauge() : ObjectBillboard(TYPE_3D_BILLBOARD_LIFEGAUGE)
{
	// �f�[�^�̃N���A
	m_pParent = nullptr;	// �e���f��

	m_initLife  = 0;	// ���݂̃`�[���Q�[�W��
	m_initWidth = 0.f;	// �|���S���̏�����

	m_pBG = nullptr;	// �w�i

}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
LifeGauge::~LifeGauge()
{
	// �I������
	Uninit();

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
LifeGauge* LifeGauge::Create(ObjectModel* pObjModel, Camera* pCamera)
{
	// ���̂̐���
	LifeGauge* pLifeGauge = new LifeGauge;

	// ���̂̏�����
	pLifeGauge->Init(pObjModel, pCamera);

	// �������ꂽ�^�C�}�[�̃|�C���^��Ԃ�
	return pLifeGauge;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void LifeGauge::Init(ObjectModel* pObjModel, Camera* pCamera)
{
	// �f�[�^�̏�����
	{
		// �e�̎擾
		m_pParent = pObjModel;
		Tower* pTower = (Tower*)m_pParent;

		// �p���f�[�^�̏�����
		ObjectBillboard::Init(m_pParent->GetPosition(), D3DXVECTOR3(m_pParent->GetSize().x, m_pParent->GetSize().x * 0.25f, 0), pCamera);
		MovePosition(D3DXVECTOR3(0, m_pParent->GetSize().y * 1.15f, 0));

		// �����̗͂̐ݒ�
		m_initLife = pTower->GetLife();

		// �|���S���̏������̐ݒ�
		m_initWidth = GetSize().x;

		// �����w�c
		SetGroup(pTower->GetGroup());

		if      (GetGroup() == Object::GROUP::GROUP_A) SetColor(0xff0000b0);
		else if (GetGroup() == Object::GROUP::GROUP_B) SetColor(0x00ffffb0);

		// �w�i�̐���
		//m_pBG = ObjectBillboard::Create(GetPosition() + pCamera->GetVecZ() * 0.001f, GetSize() * 1.1f, pCamera);
		//m_pBG->SetColor(0x00000080);

	}

}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void LifeGauge::Uninit(void)
{
	// �p���f�[�^�̏I������
	ObjectBillboard::Uninit();

}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void LifeGauge::Update(void)
{
	//m_pBG->SetPosition(GetPosition());


}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void LifeGauge::Draw(void)
{
	// �`�揈��
	ObjectBillboard::Draw();

}

// �Q�[�W�ʂ̑�������
void LifeGauge::MoveLife(float moveLife)
{
	Tower* pTower = (Tower*)m_pParent;

	float life = pTower->GetLife();

	// �Q�[�W�ʂ�0�ȉ��Ŗ�����
	if (life <= 0) return;

	// ���݂̃Q�[�W�ʂ̍X�V
	life += moveLife;

	// �ő�l����̊����̎Z�o
	float percentage = (float)life / m_initLife;

	// �Q�[�W�̒��S�_�Ƒ傫���̍X�V
	D3DXVECTOR3 size = GetSize();
	size.x = m_initWidth * percentage;
	D3DXVECTOR3 position = GetPosition();
	position.x -= (GetSize().x - size.x) * 0.5f;
	SetPosition(position);
	SetSize(size);

	// �Q�[�W��UV�T�C�Y�̍X�V
	D3DXVECTOR2 UVsize = GetUV_Size();
	UVsize.x = 1.0f * percentage;
	SetUV_Size(UVsize);

}

