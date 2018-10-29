//*****************************************************************************
//	
//		���m�̒e
//													Autohr : Yusuke Seki
//*****************************************************************************
// base
#include "SoldierBullet.h"

// fw
#include "camera.h"
#include "collision.h"

// object
#include "ObjectModel.h"
#include "player.h"
#include "Soldier.h"

const float SoldierBullet::bulletDamage_cast = 5.f;		// �W�I�F�L���X�g�̏ꍇ�̕��m�e�̃_���[�W
const float SoldierBullet::bulletDamage_soldier = 50.f;	// �W�I�F���m�̏ꍇ�̕��m�e�̃_���[�W


// �R���X�g���N�^
SoldierBullet::SoldierBullet() : BulletBillboard(Object::TYPE::TYPE_3D_SOLDIERBULLET)
{
	m_pTarget = nullptr;
}

// �f�X�g���N�^
SoldierBullet::~SoldierBullet()
{
	Uninit();
}

// ��������
SoldierBullet* SoldierBullet::CreateBuffer()
{
	SoldierBullet *pSoldierBullet = new SoldierBullet;
	pSoldierBullet->Init();

	return pSoldierBullet;
}

// ����������
void SoldierBullet::Init()
{
	BulletBillboard::Init(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(6, 6, 0), nullptr);
	m_pTarget = nullptr;
}

// �I������
void SoldierBullet::Uninit(void)
{
	BulletBillboard::Uninit();
}

// �X�V����
void SoldierBullet::Update(void)
{
	// ���g�p���͖�����
	if (!GetInstance())
		return;

	// �W�I�̓L���X�g�H
	if (m_pTarget->GetType() == Object::TYPE::TYPE_MODEL_PLAYER) {
		Player* pPlayer = (Player*)m_pTarget;

		// �L���X�g�̉���s���Œǔ��t���O��؂�
		if (pPlayer->GetPosture() == Player::POSTURE::POSTURE_AVOID || pPlayer->GetPosture() == Player::POSTURE::POSTURE_EMAVOID) {
			m_bTracking = false;

		}

	}

	// �ǔ�����
	if (m_bTracking) {
		m_front = m_pTarget->GetPosition() + D3DXVECTOR3(0, m_pTarget->GetHalfSize().y, 0) - GetPosition();
		D3DXVec3Normalize(&m_front, &m_front);
	}

	// �ړ�����
	MovePosition(m_front * 2.f);

	// �����蔻��
	if (Collision_SphereToSphere(GetPosition(), GetRadius(), m_pTarget->GetPosition(), m_pTarget->GetHalfSize().x)) {

		// �W�I��ނ̔���
		if (m_pTarget->GetType() == Object::TYPE::TYPE_MODEL_PLAYER) {
			// �W�I�F�v���C���[
			Player* pPlayer = (Player*)m_pTarget;
		}
		else {
			// �W�I�F���m
			Soldier* pSoldier = (Soldier*)m_pTarget;
			pSoldier->Damage(bulletDamage_soldier);
		}

		// �g�p�t���O���~�낷
		SetInstance(false);

		return;
	}

	// �����̌���
	m_cntEraseFrame--;

	// �������؂ꂽ��g�p�t���O���~�낷
	if (m_cntEraseFrame <= 0)
		SetInstance(false);

}

// �`�揈��
void SoldierBullet::Draw(void)
{
	if (!GetInstance())
		return;

	BulletBillboard::Draw();
}

// ���m�e�̓��I��������
// position : �����ʒu
// pTarget  : �^�[�Q�b�g
void SoldierBullet::SetBullet(D3DXVECTOR3& position, ObjectModel *pTarget, Camera *pCamera)
{
	// ���̎�����T��
	SoldierBullet* pCurrent = (SoldierBullet*)Object::GetLDATA_HEAD(Object::TYPE::TYPE_3D_SOLDIERBULLET);

	// �P������Ă��Ȃ������琶������
	if (pCurrent == nullptr) {
		// ��������
		pCurrent = SoldierBullet::CreateBuffer();

		// �ݒ菈��
		pCurrent->SetBullet_private(position, pTarget, pCamera);

		return;
	}

	// ����Ă����疢�g�p�̈��T��
	SoldierBullet* pNext = (SoldierBullet*)pCurrent->GetNextPointer();
	for (;;) {
		// ���g�p�Ȃ畺�m�e��ݒ肵�ďI��
		if (!pCurrent->GetInstance()) {
			// �ݒ菈��
			pCurrent->SetBullet_private(position, pTarget, pCamera);

			return;
		}

		// ���g�p�̈悪������Ȃ���΁A�V������������
		if (pNext == nullptr) {
			// ��������
			pNext = SoldierBullet::CreateBuffer();

			// �ݒ菈��
			pNext->SetBullet_private(position, pTarget, pCamera);

			return;
		}

		// �|�C���^�����炷
		pCurrent = pNext;
		pNext = (SoldierBullet*)pCurrent->GetNextPointer();

	}

}

// ���m�e�̐ݒ菈��
void SoldierBullet::SetBullet_private(D3DXVECTOR3& position, ObjectModel *pTarget, Camera *pCamera)
{
	SetPosition(position + D3DXVECTOR3(0, pTarget->GetHalfSize().y, 0));

	m_pTarget = pTarget;
	
	SetCamera(*pCamera);

	m_cntEraseFrame = 240;

	m_front = m_pTarget->GetPosition() + D3DXVECTOR3(0, m_pTarget->GetHalfSize().y, 0) - GetPosition();

	D3DXVec3Normalize(&m_front, &m_front);

	m_bTracking = true;

	SetInstance(true);

}


