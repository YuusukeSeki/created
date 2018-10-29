//*****************************************************************************
//
//		�`�[���Q�[�W
//													Author : Yusuke Seki
//*****************************************************************************
#include "TeamGauge.h"
#include "MainGame.h"
#include "list_LoadTexture_MainGame.h"
#include "Effect3D.h"

#include "Etc_Paramaters.h"


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
TeamGauge::TeamGauge(Object::TYPE type) : Object2D(type)
{
	// �f�[�^�̃N���A
	m_life      = 0;	// ���݂̃`�[���Q�[�W��
	m_initWidth = 0.f;	// �|���S���̏�����

}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
TeamGauge::~TeamGauge()
{
	// �I������
	Uninit();

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
TeamGauge* TeamGauge::Create(D3DXVECTOR3& position, D3DXVECTOR3& size, Object::GROUP group)
{
	// ���̂̐���
	TeamGauge* pTeamGauge = new TeamGauge;

	// ���̂̏�����
	pTeamGauge->Init(position, size, group);

	// �������ꂽ�^�C�}�[�̃|�C���^��Ԃ�
	return pTeamGauge;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void TeamGauge::Init(D3DXVECTOR3& position, D3DXVECTOR3& size, Object::GROUP group)
{
	// �f�[�^�̏�����
	{
		// �p���f�[�^�̏�����
		Object2D::Init(position, size);

		// ���݂̃`�[���Q�[�W��
		m_life = TEAMGAUGE_MAX_LIFE;

		// �|���S���̏�����
		m_initWidth = size.x;

		// �����w�c
		SetGroup(group);

	}

}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void TeamGauge::Uninit(void)
{
	// �p���f�[�^�̏I������
	Object2D::Uninit();

}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void TeamGauge::Update(void)
{

}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void TeamGauge::Draw(void)
{
	// �`�揈��
	Object2D::Draw();

}



//=============================================================================
// ����
// �Q�[�W�ʂ̑�������
void TeamGauge::MoveLife(float moveLife)
{
	// �Q�[�W�ʂ�0�ȉ��Ŗ�����
	if (m_life <= 0) return;

	// ���݂̃Q�[�W�ʂ̍X�V
	m_life += moveLife;

	// �ő�l����̊����̎Z�o
	float percentage = m_life / TEAMGAUGE_MAX_LIFE;

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

// true �Ȃ畉��
bool TeamGauge::Lose() {

	// �y���菈���z�c���Q�[�W�ʂ̗L��
	if (m_life <= 0) return true;	// ����
	return false;					// �L��

}


