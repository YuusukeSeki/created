//*****************************************************************************
//
//		��
//													Autohr : Yusuke Seki
//*****************************************************************************
// base
#include "tower.h"

// fw
#include "collision.h"

// child
#include "Hold.h"
#include "LifeGauge.h"
#include "Icon.h"
#include "Commander.h"

// etc...
#include "player.h"
#include "TeamGaugeManager.h"
#include "TeamGauge.h"

// resource
#include "MainGame.h"
#include "list_LoadTexture_MainGame.h"
#include "Etc_Paramaters.h"



//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Tower::Tower() : ObjectModel(Object::TYPE::TYPE_MODEL_TOWER)
{
	// �����o�ϐ�������
	m_life      = 0;	// �̗�
	m_browRange = 0.f;	// �����͈�

	m_pHold      = nullptr;	// "HOLD"
	m_pLifeGauge = nullptr;	// �̗̓Q�[�W
	m_pIcon      = nullptr;	// �A�C�R��
	
}


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Tower::Tower(Object::TYPE type) : ObjectModel(type)
{
	// �����o�ϐ�������
	m_life      = 0;	// �̗�
	m_browRange = 0.f;	// �����͈�

	m_pHold      = nullptr;	// "HOLD"
	m_pLifeGauge = nullptr;	// �̗̓Q�[�W
	m_pIcon      = nullptr;	// �A�C�R��
	
}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
Tower::~Tower()
{
	Uninit();

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
Tower* Tower::Create(D3DXVECTOR3& position, const char* FileName, Object::GROUP group)
{
	Tower* pTower = new Tower(Object::TYPE::TYPE_MODEL_TOWER);
	pTower->Init(position, FileName, group);

	return pTower;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void Tower::Init(D3DXVECTOR3& position, const char* FileName, Object::GROUP group)
{
	// �f�[�^�̐ݒ�
	ObjectModel::Init(position, FileName);	// �p���f�[�^�̏�����
	m_life      = TOWER_MAX_LIFE;	// �̗�
	m_browRange = GetSize().x * 1.05f;		// �����͈�
	SetGroup(group);
	
	// �F�̐ݒ�
	if      (GetGroup() == Object::GROUP::GROUP_A) SetColor(0xff0000a0);	// �ԐF
	else if (GetGroup() == Object::GROUP::GROUP_B) SetColor(0x0000ffa0);	// �F

	m_cntFrame = 1500;	// ���m�����p�J�E���^�[


	// �|���S���̐���
	m_pLifeGauge = LifeGauge::Create(this, MainGame::GetCamera(0));	// �̗̓Q�[�W
	m_pHold      = Hold::Create(this, MainGame::GetCamera(0));		// "HOLD"
	m_pIcon      = Icon::Create(m_pLifeGauge->GetPosition() + D3DXVECTOR3(0, m_pLifeGauge->GetSize().y * 1.f, 5),
								D3DXVECTOR3(m_pLifeGauge->GetSize().x * 0.3f, m_pLifeGauge->GetSize().x * 0.3f, 0), MainGame::GetCamera(0), group);	// �A�C�R��
	
	m_pIcon->SetTexture(MainGame::GetTexture(List_LoadTexture_MainGame::ICON_CASTLE)->GetTexture());

	
}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void Tower::Uninit(void)
{
	// �p���f�[�^�̏I������
	ObjectModel::Uninit();

}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void Tower::Update(void)
{
	m_cntFrame++;

	if (m_cntFrame >= INTERVAL_CREATE_SOLDIER) {

		Commander::SetCommander(GetPosition(), GetFront(), GetGroup());
		m_cntFrame = 0;

	}

	// "HOLD"�\������
	{
		Player* pPlayer = (Player*)Object::GetLDATA_HEAD(Object::TYPE::TYPE_MODEL_PLAYER);

		if (pPlayer == nullptr) return;

		Player* pCurrent = pPlayer;
		Player* pNext    = (Player*)pCurrent->GetNextPointer();

		for (;;) {

			if (pCurrent->GetGroup() != GetGroup()) {

				float length = Distance3D(pCurrent->GetPosition(), GetPosition());

				if (length <= (m_browRange) * (m_browRange)) m_pHold->SetDrawHold(true);
				else                                                       m_pHold->SetDrawHold(false);

			}

			pCurrent = pNext;

			if (pCurrent == nullptr) break;

			pNext = (Player*)pCurrent->GetNextPointer();

		}

	}


}


//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void Tower::Draw(void)
{
	// �`�揈���͐e���Ɋۓ���
	ObjectModel::Draw();

}


// �̗͂����炷
// true - ���_����ꂽ : false - ���_�����ĂȂ�
bool Tower::BrowTower(float breakPower)
{
	m_life -= breakPower;

	if (m_life < 0)
	{
		breakPower = breakPower + m_life;
	}

	m_pLifeGauge->MoveLife(breakPower);

	TeamGaugeManager::GetTeamGauge_ENEMY()->MoveLife(-breakPower);

	if (m_life <= 0)
	{
		TeamGaugeManager::GetTeamGauge_ENEMY()->MoveLife(-50);

		m_pHold      ->ReleaseThis();	// "HOLD"
		m_pLifeGauge ->Release();		// �̗̓Q�[�W
		m_pIcon      ->Release();		// �A�C�R��

		Release();

		return true;
	}
	return false;

}

// ���W�̈ړ�
void Tower::MovePosition(D3DXVECTOR3& movePosition)
{
	ObjectModel::MovePosition(movePosition);

	m_pHold->MovePosition(movePosition);
	m_pLifeGauge->MovePosition(movePosition);
	m_pIcon->MovePosition(movePosition);

}

// true �Ȃ瓃�������͈͓�
bool Tower::CollisionBrowRange(D3DXVECTOR3& position)
{
	if (Distance3D(GetPosition(), position) <= m_browRange * m_browRange)
		return true;

	return false;

}

