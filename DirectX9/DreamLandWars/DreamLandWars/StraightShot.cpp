//*****************************************************************************
//	
//		�o���b�g
//													Autohr : Yusuke Seki
//*****************************************************************************
#include "StraightShot.h"
#include "player.h"
#include "soldier.h"
#include "collision.h"
#include "MainGame.h"



//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
StraightShot::StraightShot(Object::TYPE type) : Bullet3D(type)
{
	// �f�[�^�̃N���A
	m_uninitPos       = D3DXVECTOR3(0, 0, 0);
	m_vecInitToUninit = D3DXVECTOR3(0, 0, 0);

}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
StraightShot::~StraightShot()
{
	Uninit();
}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
StraightShot* StraightShot::Create(D3DXVECTOR3& position, D3DXVECTOR3& size)
{
	// ���̂𐶐�
	StraightShot* pStraightShot = new StraightShot(Object::TYPE::TYPE_3D_STRAIGHTSHOT);

	// ������
	pStraightShot->Init(position, size);

	return pStraightShot;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void StraightShot::Init(D3DXVECTOR3& position, D3DXVECTOR3& size)
{
	// �f�[�^�̏�����
	Bullet3D::Init(position, size);				// �p���f�[�^�̏�����
	m_uninitPos       = D3DXVECTOR3(0, 0, 0);	// �I���n�_
	m_vecInitToUninit = D3DXVECTOR3(0, 0, 0);	// ���˒n�_

}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void StraightShot::Uninit(void)
{
	Bullet3D::Uninit();
}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void StraightShot::Update(void)
{
	// ���g�p�ŏ�������
	if (!Bullet3D::GetInstance()) return;

	// �e�̈ړ�
	MovePosition(GetVecZ() * GetMove());

	// ���m�A�v���C���[�A�ǂƂ̓����蔻��
	if (CollisionSoldier() || CollisionPlayer() || CollisionWall()) {
		// �g�p���t���OOFF
		Bullet3D::SetInstance(false);
	}
	
	// �����n�_�𒴂���������i���ρj
	{
		// ���ݒn�_�Ə����n�_�̒P�ʃx�N�g�����Z�o
		D3DXVECTOR3 vec = m_uninitPos - GetPosition();
		D3DXVec3Normalize(&vec, &vec);

		// ���ς����A�����n�_�𒴂��Ă�����o���b�g������
		float result = D3DXVec3Dot(&vec, &m_vecInitToUninit);
		if (result <= 0) Bullet3D::SetInstance(false);
	}

}


//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void StraightShot::Draw(void)
{
	Bullet3D::Draw();

}


//	SS�̔���
void StraightShot::SetStraightShot(Player& player)
{
	// ���̎�����T��
	StraightShot* pStraightShot = (StraightShot*)Object::GetLDATA_HEAD(Object::TYPE::TYPE_3D_STRAIGHTSHOT);

	// �P������Ă��Ȃ������琶������
	if (pStraightShot == nullptr) {
		// ��������
		pStraightShot = StraightShot::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(10, 10, 0));

		// �ݒ菈��
		pStraightShot->SetStraightShot_Private(player);

		return;
	}

	// ����Ă����疢�g�p��SS��T��
	StraightShot* pCurrent = (StraightShot*)pStraightShot;
	StraightShot* pNext = (StraightShot*)pStraightShot->GetNextPointer();
	for (;;) {
		// ���g�p�Ȃ�ݒ肵�ďI��
		if (!pCurrent->GetInstance()) {
			pCurrent->SetStraightShot_Private(player);
			break;
		}

		// ���g�pSS��������Ȃ���΁A�V������������
		if (pNext == nullptr) {
			// ��������
			pNext = StraightShot::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(10, 10, 0));

			// �ݒ菈��
			pNext->SetStraightShot_Private(player);

			break;
		}

		// �|�C���^�����炷
		pCurrent = pNext;
		pNext = (StraightShot*)pCurrent->GetNextPointer();

	}

}


//=============================================================================
//	private methods
//	SS�̐ݒ�
void StraightShot::SetStraightShot_Private(Player& player)
{
	// ���W�̐ݒ�
	this->SetPosition(player.GetPosition());

	// �����w�c�̐ݒ�
	this->SetGroup(player.GetGroup());

	// �����̐ݒ�
	this->SetVecZ(player.GetFront());

	// �����x�̐ݒ�
	this->SetMove(player.GetStraightShotSpeed());

	// �����x�̐ݒ�
	this->SetAccelerate(0);

	// �����n�_�̐ݒ�
	m_uninitPos = GetPosition() + player.GetFront() * player.GetStraightShotRange();

	// �����p�̒P�ʃx�N�g���̐ݒ�i���ςŏ����j
	m_vecInitToUninit = m_uninitPos - GetPosition();
	D3DXVec3Normalize(&m_vecInitToUninit, &m_vecInitToUninit);

	// �g�p�t���OON
	this->SetInstance(true);

	// �e�̐ݒ�
	m_pParent = &player;

	// �e�N�X�`���̐ݒ�
	SetTexture(MainGame::GetTexture(List_LoadTexture_MainGame::TEXTURE_NAME::BULLET_TEXNAME)->GetTexture());

}

//	���m�Ƃ̓����蔻�菈��
bool StraightShot::CollisionSoldier()
{
	Soldier* pSoldier = (Soldier*)Object::GetLDATA_HEAD(TYPE_MODEL_SOLDIER);

	if (pSoldier == nullptr) return false;

	Soldier* pCurrent = pSoldier;
	Soldier* pNext = (Soldier*)pSoldier->GetNextPointer();

	for (;;) {

		// �w�c�̔���
		if (pCurrent->GetInstance() && pCurrent->GetGroup() != GetGroup())

			// �����蔻��
			if (Collision_SphereToSphere(GetPosition(), GetRadius(), pCurrent->GetPosition(), pCurrent->GetRadius())) {

				// �U������
				pCurrent->Attack(m_pParent->GetStraightShotDamage(), GetVecZ(), m_pParent->GetStraightShotSpeed(), m_pParent);

				return true;
			}

		if (pNext == nullptr) return false;

		pCurrent = pNext;
		pNext = (Soldier*)pCurrent->GetNextPointer();

	}

}

//	�v���C���[�Ƃ̓����蔻�菈��
bool StraightShot::CollisionPlayer()
{
	Player* pPlayer = (Player*)Object::GetLDATA_HEAD(TYPE_MODEL_PLAYER);

	if (pPlayer == nullptr) return false;

	Player* pCurrent = pPlayer;
	Player* pNext = (Player*)pPlayer->GetNextPointer();

	for (;;) {

		if (pCurrent->GetGroup() != GetGroup())
			if (Collision_SphereToSphere(GetPosition(), GetRadius(), pCurrent->GetPosition(), pCurrent->GetRadius()))
				return true;

		pCurrent = pNext;

		if (pCurrent == nullptr) 
			return false;

		pNext = (Player*)pCurrent->GetNextPointer();

	}

}

//	�ǂƂ̓����蔻�菈��
bool StraightShot::CollisionWall()
{
	// �� ������

	return false;
}

