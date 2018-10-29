//*****************************************************************************
//
//		���m
//												Autohr : Yusuke Seki
//*****************************************************************************
// base
#include "Soldier.h"
#include "Commander.h"

// fw
#include "collision.h"

// Object
#include "player.h"
#include "tower.h"
#include "castle.h"
#include "SoldierBullet.h"

// resource
#include "MainGame.h"


// Initialize ID
int Soldier::m_cntID = 0;



// �R���X�g���N�^
Soldier::Soldier() : ObjectModel(Object::TYPE::TYPE_MODEL_SOLDIER)
{
	// �f�[�^�̃N���A
	m_bInstance = false;

}

// �f�X�g���N�^
Soldier::~Soldier()
{
	Uninit();

}

// ����
Soldier* Soldier::Create(D3DXVECTOR3& position, const char* modelPass)
{
	Soldier* pSoldier = new Soldier;
	pSoldier->Init(position, modelPass);

	return pSoldier;

}

// ������
void Soldier::Init(D3DXVECTOR3& position, const char* modelPass)
{
	// �f�[�^�̏�����
	ObjectModel::Init(position, modelPass);
	m_searchRange = 45;
	m_breakPower = 10;

	m_ID = m_cntID;

	m_bInstance = false;

	m_cntID++;

}

// �I��
void Soldier::Uninit(void)
{
	ObjectModel::Uninit();

	m_cntID = 0;
}

// �X�V
void Soldier::Update(void)
{
	if (!m_bInstance) return;

	// �G�̓��Ɍ������ēˌ�����
	if (m_pAssaultBasePoint != nullptr)
	{
		// ���ɓ��������玀��
		if (CollisionBasePoint())
		{
			BreakBasePoint();
		}
	}

	// ���m�͈͂ɓG�̋��_�𔭌�������w�����ɕ񍐂���
	else if ((m_pAssaultBasePoint = SearchTower()) != nullptr || (m_pAssaultBasePoint = SearchCastle()) != nullptr)
		m_pParent->ReceiveReport_SearchBasePoint(m_pAssaultBasePoint);

	// ���m�͈͂ɓG�𔭌�������w�����ɕ񍐂���
	else if (SearchEnemy())
		m_pParent->ReceiveReport_SearchEnemy();

}

// �`��
void Soldier::Draw(void)
{
	if (!m_bInstance) return;

	ObjectModel::Draw();

}

// ����
void Soldier::Run(D3DXVECTOR3& vecZ, float velocity)
{
	SetRotateToObj((D3DXVECTOR3(vecZ * velocity) + GetPosition()));
	MovePosition(vecZ * velocity);

}

// �U�������
void Soldier::Attack(float damage, D3DXVECTOR3& vector, float accelerate, Player* pPlayer)
{
	// �_���[�W���󂯂�
	if (Damage(damage)) {
		// ����

		// �v���C���[�̌��j���㏸
		pPlayer->PlusScore_CrushSoldier();

	}
	else {
		// �����Ă�

		// ��΂����
		MovePosition(vector * accelerate);
	}
	
}

// �_���[�W���󂯂�
// damage�F�^����_���[�W��
// �Ԃ�l�F true  ���񂾂�
//			false �����Ă��
bool Soldier::Damage(float damage)
{
	m_life -= damage;

	if (m_life <= 0) {
		m_pParent->ReceiveReport_Death(this);

		m_bInstance = false;
		return true;
	}

	return false;
}

// �ڕW���_��ݒ肷��
void Soldier::SetTargetBasePoint(ObjectModel* pTarget)
{
	m_pAssaultBasePoint = pTarget;
}

// �G�ɍU��������
void Soldier::ShotBullet()
{
	ObjectModel* pTarget = SearchNearEnemy();

	if (pTarget == nullptr)
		return;

	SetRotateToObj(D3DXVECTOR3(pTarget->GetPosition()));
	SoldierBullet::SetBullet(GetPosition(), pTarget, MainGame::GetCamera(0));
	
}

// ���m�̓��I��������
Soldier* Soldier::SetSoldier(D3DXVECTOR3& position, D3DXVECTOR3& front, const char* modelPass, Object::GROUP group, Commander* pCommnader)
{
	// ���̎�����T��
	Soldier* pSoldier = (Soldier*)Object::GetLDATA_HEAD(Object::TYPE::TYPE_MODEL_SOLDIER);

	// �P������Ă��Ȃ������琶������
	if (pSoldier == nullptr) {
		// ��������
		pSoldier = Soldier::Create(position, modelPass);
		pSoldier->SetSoldier_private(position, front, group, pCommnader);

		return pSoldier;
	}

	// ����Ă����疢�g�p�̈��T��
	Soldier* pCurrent = (Soldier*)pSoldier;
	Soldier* pNext = (Soldier*)pSoldier->GetNextPointer();
	for (;;) {
		// ���g�p�Ȃ畺�m�����������ďI��
		if (!pCurrent->GetInstance()) {
			pCurrent->SetSoldier_private(position, front, group, pCommnader);
			return pCurrent;
		}

		// ���g�p�̈悪������Ȃ���΁A�V������������
		if (pNext == nullptr) {
			// ��������
			pNext = Soldier::Create(position, modelPass);
			pNext->SetSoldier_private(position, front, group, pCommnader);

			return pNext;
		}

		// �|�C���^�����炷
		pCurrent = pNext;
		pNext = (Soldier*)pCurrent->GetNextPointer();

	}

}

// ���̕��m���E��
void Soldier::KillMe()
{
	Damage(m_maxLife);
}


//=============================================================================
//	private �֐�
// ���m�̐ݒ菈��
void Soldier::SetSoldier_private(D3DXVECTOR3& position, D3DXVECTOR3& front, Object::GROUP group, Commander* pCommnader)
{
	// �ʒu
	SetPosition(position);

	// ����
	SetFront(front);

	// �����O���[�v
	SetGroup(group);

	// �����̎w����
	m_pParent = pCommnader;

	// �F�A����
	if (group == Object::GROUP_A) {
		SetColor(0xff0000ff);
		SetRotate(D3DXVECTOR3(0, 0, 0));
	}
	else if (group == Object::GROUP_B) {
		SetColor(0x0000ffff);
		SetRotate(D3DXVECTOR3(0, D3DXToRadian(180), 0));
	}

	// �̗͂̍ő�l
	m_maxLife = 100;

	// ���݂̗̑�
	m_life    = m_maxLife;

	// �����������_
	m_pAssaultBasePoint = nullptr;

	// �g�p�t���OON
	m_bInstance = true;
	
}

// ���G
// �Ԃ�l�F true  ����
//			false ���Ȃ���
bool Soldier::SearchEnemy()
{
	if (SearchEnemy_Soldier() || SearchEnemy_Cast()) return true;

	return false;
}

// ���G�i���m�j
// �Ԃ�l�F true  ����
//			false ���Ȃ���
bool Soldier::SearchEnemy_Soldier()
{
	Soldier* pSoldier = (Soldier*)Object::GetLDATA_HEAD(TYPE_MODEL_SOLDIER);

	if (pSoldier == nullptr) return false;

	Soldier* pCurrent = pSoldier;
	Soldier* pNext = (Soldier*)pSoldier->GetNextPointer();

	for (;;) {

		if (pCurrent->GetGroup() != GetGroup() && pCurrent->GetInstance())
			if (Collision_SphereToSphere(GetPosition(), m_searchRange, pCurrent->GetPosition(), pCurrent->GetRadius())) return true;

		pCurrent = pNext;

		if (pCurrent == nullptr) return false;

		pNext = (Soldier*)pCurrent->GetNextPointer();

	}

}

// ���G�i�L���X�g�j
// �Ԃ�l�F true  ����
//			false ���Ȃ���
bool Soldier::SearchEnemy_Cast()
{
	Player* pPlayer = (Player*)Object::GetLDATA_HEAD(TYPE_MODEL_PLAYER);

	if (pPlayer == nullptr) return false;

	Player* pCurrent = pPlayer;
	Player* pNext = (Player*)pPlayer->GetNextPointer();

	for (;;) {

		if(pCurrent->GetGroup() != GetGroup())
			if (Collision_SphereToSphere(GetPosition(), m_searchRange, pCurrent->GetPosition(), pCurrent->GetRadius())) return true;

		pCurrent = pNext;

		if (pCurrent == nullptr) return false;

		pNext = (Player*)pCurrent->GetNextPointer();

	}

}

// ���G�i���j
// �Ԃ�l�F true  ����
//			false ���Ȃ���
Tower* Soldier::SearchTower()
{
	Tower* pTower = (Tower*)Object::GetLDATA_HEAD(TYPE_MODEL_TOWER);

	if (pTower == nullptr)
		return nullptr;

	Tower* pCurrent = pTower;
	Tower* pNext = (Tower*)pTower->GetNextPointer();

	for (;;) {

		if (pCurrent->GetGroup() != GetGroup())
			if (Collision_SphereToSphere(GetPosition(), m_searchRange, pCurrent->GetPosition(), pCurrent->GetRadius()))
				return pCurrent;

		pCurrent = pNext;

		if (pCurrent == nullptr)
			return nullptr;

		pNext = (Tower*)pCurrent->GetNextPointer();

	}

}

// ���G�i��j
// �Ԃ�l�F true  ����
//			false ���Ȃ���
Castle* Soldier::SearchCastle()
{
	Castle* pCastle = (Castle*)Object::GetLDATA_HEAD(TYPE_MODEL_CASTLE);

	if (pCastle == nullptr)
		return nullptr;

	Castle* pCurrent = pCastle;
	Castle* pNext = (Castle*)pCastle->GetNextPointer();

	for (;;) {

		if (pCurrent->GetGroup() != GetGroup())
			if (Collision_SphereToSphere(GetPosition(), m_searchRange, pCurrent->GetPosition(), pCurrent->GetRadius()))
				return pCurrent;

		pCurrent = pNext;

		if (pCurrent == nullptr)
			return nullptr;

		pNext = (Castle*)pCurrent->GetNextPointer();

	}

}

// ��ԋ߂��G��T��
// �Ԃ�l�F	��ԋ߂��G�̃|�C���^
ObjectModel* Soldier::SearchNearEnemy()
{
	Soldier *pCurrentA = (Soldier*)Object::GetLDATA_HEAD(Object::TYPE_MODEL_SOLDIER);

	if (pCurrentA == nullptr)
		return nullptr;

	Soldier *pNextA = (Soldier*)pCurrentA->GetNextPointer();
	Soldier *pTargetA = nullptr;

	float minA, minB;
	minA = minB = 99999999.f;

	// ��ԋ߂����m��T��
	for (;;) {
		if (pCurrentA->GetGroup() != GetGroup() && pCurrentA->GetInstance()) {
			float buf = Distance3D(GetPosition(), pCurrentA->GetPosition());

			if (buf < minA) {
				minA = buf;
				pTargetA = pCurrentA;
			}
		}

		pCurrentA = pNextA;

		if (pCurrentA == nullptr)
			break;

		pNextA = (Soldier*)pCurrentA->GetNextPointer();

	}

	
	Player *pCurrentB = (Player*)Object::GetLDATA_HEAD(Object::TYPE_MODEL_PLAYER);

	if (pCurrentB == nullptr)
		return nullptr;

	Player *pNextB = (Player*)pCurrentB->GetNextPointer();
	Player *pTargetB = nullptr;

	// ���m�����߂��L���X�g��T��
	for (;;) {
		if (pCurrentB->GetGroup() != GetGroup()) {
			float buf = Distance3D(GetPosition(), pCurrentB->GetPosition());

			if (buf < minB) {
				minB = buf;
				pTargetB = pCurrentB;
			}
		}

		pCurrentB = pNextB;

		if (pCurrentB == nullptr)
			break;

		pNextB = (Player*)pCurrentB->GetNextPointer();

	}

	if (minA < minB)
		return (ObjectModel*)pTargetA;
	else
		return (ObjectModel*)pTargetB;

}

// ���_�Ƃ̓����蔻��
bool Soldier::CollisionBasePoint()
{
	if (Collision_SphereToSphere(GetPosition(), 0.00001f, m_pAssaultBasePoint->GetPosition(), m_pAssaultBasePoint->GetRadius() - m_pAssaultBasePoint->GetRadius() * 0.3f))
		return true;

	return false;
}

// ���_������
void Soldier::BreakBasePoint()
{
	if (m_pAssaultBasePoint->GetType() == Object::TYPE::TYPE_MODEL_CASTLE)
	{
		//dynamic_cast<Castle*>(m_pAssaultBasePoint)->
	}
	else
	{
		// ��ꂽ��w�����ɕ񍐂���
		if (dynamic_cast<Tower*>(m_pAssaultBasePoint)->BrowTower(m_breakPower))
		{
			m_pParent->ReceiveReport_BreakBasePoint();
			return;
		}
	}

	// Death
	Damage(m_maxLife);

}

