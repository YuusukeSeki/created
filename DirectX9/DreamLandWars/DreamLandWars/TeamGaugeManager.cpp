//*****************************************************************************
//
//		�`�[���Q�[�W�}�l�[�W���[
//													Author : Yusuke Seki
//*****************************************************************************
#include "TeamGaugeManager.h"
#include "MainGame.h"
#include "list_LoadTexture_MainGame.h"
#include "TeamGauge.h"


TeamGauge* TeamGaugeManager::m_pTeamGauge_YOURTEAM = nullptr;
TeamGauge* TeamGaugeManager::m_pTeamGauge_ENEMY    = nullptr;

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
TeamGaugeManager::TeamGaugeManager(Object::TYPE type) : Object2D(type)
{
	// �f�[�^�̃N���A
	m_pLabel_YOURTEAM     = nullptr;	// �y���x���z"YOUR TEAM"
	m_pLabel_ENEMY        = nullptr;	// �y���x���z"ENEMY"
	m_pTeamGauge_YOURTEAM = nullptr;	// �y�Q�[�W�z"YOUR TEAM"
	m_pTeamGauge_ENEMY    = nullptr;	// �y�Q�[�W�z"ENEMY"

}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
TeamGaugeManager::~TeamGaugeManager()
{
	// �I������
	Uninit();

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
TeamGaugeManager* TeamGaugeManager::Create(D3DXVECTOR3& position, D3DXVECTOR3& size)
{
	// ���̂̐���
	TeamGaugeManager* pTeamGaugeManager = new TeamGaugeManager;

	// ���̂̏�����
	pTeamGaugeManager->Init(position, size);

	// �������ꂽ�^�C�}�[�̃|�C���^��Ԃ�
	return pTeamGaugeManager;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void TeamGaugeManager::Init(D3DXVECTOR3& position, D3DXVECTOR3& size)
{
	// �f�[�^�̏�����
	{
		// �p���f�[�^�̏�����
		Object2D::Init(position, size);


		// ���x���F"YOUR TEAM"
		size              = D3DXVECTOR3(GetSize().x * 0.1f                               , GetSize().y     * 0.525f, 0.f);
		position          = D3DXVECTOR3(GetPosition().x - GetHalfSize().x + size.x * 0.5f, GetPosition().y * 1.2f, 0.f);
		m_pLabel_YOURTEAM = Object2D::Create(position, size);
		m_pLabel_YOURTEAM->SetColor(0xff0000ff);
		m_pLabel_YOURTEAM->SetTexture(MainGame::GetTexture(List_LoadTexture_MainGame::TEXTURE_NAME::LABEL_YOURTEAM_TEXNAME)->GetTexture());

		// �`�[���Q�[�W�i�����j
		size                  = D3DXVECTOR3(GetSize().x * 0.85f                                                                     , m_pLabel_YOURTEAM->GetSize().y    , 0.f);
		position              = D3DXVECTOR3(m_pLabel_YOURTEAM->GetPosition().x + m_pLabel_YOURTEAM->GetHalfSize().x + size.x * 0.55f, m_pLabel_YOURTEAM->GetPosition().y, 0.f);
		m_pTeamGauge_YOURTEAM = TeamGauge::Create(position, size, Object::GROUP::GROUP_A);
		m_pTeamGauge_YOURTEAM->SetColor(0xff0000ff);
		m_pTeamGauge_YOURTEAM->SetTexture(MainGame::GetTexture(List_LoadTexture_MainGame::TEXTURE_NAME::TEAMGAUGE_TEXNAME)->GetTexture());

		// "ENEMY"
		size           = D3DXVECTOR3(GetSize().x * 0.10f                              , GetSize().y * 0.25f    , 0.f);
		position       = D3DXVECTOR3(GetPosition().x - GetHalfSize().x + size.x * 0.5f, GetPosition().y * 0.75f, 0.f);
		m_pLabel_ENEMY = Object2D::Create(position, size);
		m_pLabel_ENEMY->SetColor(0x00ffffff);
		m_pLabel_ENEMY->SetTexture(MainGame::GetTexture(List_LoadTexture_MainGame::TEXTURE_NAME::LABEL_ENEMY_TEXNAME)->GetTexture());

		// �`�[���Q�[�W�i����j
		size               = D3DXVECTOR3(GetSize().x * 0.85f                                                               , GetSize().y * 0.30f            , 0.f);
		position           = D3DXVECTOR3(m_pLabel_ENEMY->GetPosition().x + m_pLabel_ENEMY->GetHalfSize().x + size.x * 0.55f, m_pLabel_ENEMY->GetPosition().y, 0.f);
		m_pTeamGauge_ENEMY = TeamGauge::Create(position, size, Object::GROUP::GROUP_B);
		m_pTeamGauge_ENEMY->SetColor(0x00ffffff);
		m_pTeamGauge_ENEMY->SetTexture(MainGame::GetTexture(List_LoadTexture_MainGame::TEXTURE_NAME::TEAMGAUGE_TEXNAME)->GetTexture());

	}


}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void TeamGaugeManager::Uninit(void)
{
	// �p���f�[�^�̏I������
	Object2D::Uninit();

}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void TeamGaugeManager::Update(void)
{

}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void TeamGaugeManager::Draw(void)
{
	// �������g�͕`�悵�Ȃ�
	return;

	// �`�揈��
	Object2D::Draw();

}



//=============================================================================
// ����

//=============================================================================
// �ݒ�
