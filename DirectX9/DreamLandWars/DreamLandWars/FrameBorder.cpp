//*****************************************************************************
//
//		�g��
//													Author : Yusuke Seki
//*****************************************************************************
#include "FrameBorder.h"
#include "timer.h"
#include "TeamGaugeManager.h"
#include "TeamLevel.h"
#include "MainGame.h"
#include "list_LoadTexture_MainGame.h"


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
FrameBorder::FrameBorder(Object::TYPE type) : Object2D(type)
{
	// �f�[�^�̃N���A
	m_pTimer     = nullptr;	// �y�q�z�^�C�}�[
	m_pTeamGaugeManager = nullptr;	// �y�q�z�`�[���Q�[�W
	m_pTeamLevel = nullptr;	// �y�q�z�`�[�����x��

}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
FrameBorder::~FrameBorder()
{
	// �I������
	Uninit();

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
FrameBorder* FrameBorder::Create(D3DXVECTOR3& position, D3DXVECTOR3& size)
{
	// ���̂̐���
	FrameBorder* pFrameBorder = new FrameBorder;

	// ���̂̏�����
	pFrameBorder->Init(position, size);

	// �������ꂽ�g���̃|�C���^��Ԃ�
	return pFrameBorder;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void FrameBorder::Init(D3DXVECTOR3& position, D3DXVECTOR3& size)
{
	// �f�[�^�̏�����
	{
		// �p���f�[�^�̏�����
		Object2D::Init(position, size);

		// �^�C�}�[�̐���
		size     = D3DXVECTOR3(GetSize().x * 0.25f, GetSize().y * 0.6f, 0.f);
		position = D3DXVECTOR3(GetPosition().x - GetHalfSize().x + GetSize().x * 0.01f, GetPosition().y * 1.1f, 0.f);
		m_pTimer = Timer::Create(position, size);
		m_pTimer->SetTexture_Number(MainGame::GetTexture(List_LoadTexture_MainGame::TEXTURE_NAME::NUMBER_TEXNAME)->GetTexture());
		m_pTimer->SetTexture_Colon(MainGame::GetTexture(List_LoadTexture_MainGame::TEXTURE_NAME::COLON_TEXNAME)->GetTexture());
		m_pTimer->SetTimer(7, 0);

		// �`�[���Q�[�W�̐���
		size                = D3DXVECTOR3(GetSize().x * 0.6f, GetSize().y * 0.65f, 0.f);
		position            = D3DXVECTOR3(GetPosition().x - GetHalfSize().x + GetSize().x * 0.02f + GetSize().x * 0.25f + size.x * 0.5f, GetPosition().y * 1.1f, 0.f);
		m_pTeamGaugeManager = TeamGaugeManager::Create(position, size);

		// �`�[�����x���̐���
		//size         = D3DXVECTOR3((GetSize().x * 0.2f), (GetSize().y * 0.6f), 0.f);
		//position     = D3DXVECTOR3((m_pTeamGauge->GetPosition().x + m_pTeamGauge->GetHalfSize().x + size.x * 0.5f), m_pTeamGauge->GetPosition().y , 0.f);
		//m_pTeamLevel = TeamLevel::Create(position, size);

	}


}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void FrameBorder::Uninit(void)
{
	// �p���f�[�^�̏I������
	Object2D::Uninit();

}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void FrameBorder::Update(void)
{
	// �^�C�}�[
	m_pTimer->Update();
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void FrameBorder::Draw(void)
{
	// �`�揈��
	Object2D::Draw();

}



//=============================================================================
// ����

//=============================================================================
// �ݒ�
