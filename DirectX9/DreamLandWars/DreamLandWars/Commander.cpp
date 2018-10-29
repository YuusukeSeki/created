//*****************************************************************************
//
//		�w����
//													Author : Yusuke Seki
//*****************************************************************************
#include "Commander.h"
#include "soldier.h"
#include "collision.h"
#include "ObjectModel.h"
#include "ModelData.h"

#include "Etc_Paramaters.h"


// �R���X�g���N�^
Commander::Commander() : Object(Object::TYPE::TYPE_COMMANDER)
{
	m_pSoldier   = nullptr;					// �w�����̕��m�̐擪�A�h���X
	m_front      = D3DXVECTOR3(0, 0, 0);	// �O����
}


// �f�X�g���N�^
Commander::~Commander()
{

}


// ��������
Commander* Commander::CreateBuffer()
{
	Commander* pCommander = new Commander;
	pCommander->Init();

	return pCommander;
}


// ����������
void Commander::Init()
{
	m_pSoldier         = nullptr;				// �w�����̕��m�̐擪�A�h���X
	m_front            = D3DXVECTOR3(0, 0, 1);	// �O����
	m_restTime         = 0;						// ���̎ˌ��܂ł̋x�e����
	m_bInstance        = false;					// �g�p���t���O
	m_radius_ViewAngle = 30.f;					// ����p�̔��a
	m_bFormLine        = true;					// true �Ő��񂵂Ă���
	m_velocity         = SOLDIER_MOVESPEED;		// �ړ����x
	m_bSearchEnemy     = false;					// �G�����t���O
	m_pSearchBasePoint = nullptr;				// ���_�̔����t���O

}


// �I������
void Commander::Uninit()
{

}


// �X�V����
void Commander::Update()
{
	// ���g�p�Ŗ�����
	if (!m_bInstance) return;

	// ���_����������ˌ�
	else if (m_pSearchBasePoint != nullptr)
	{
		AssaultBasePoint();

		SetPosition(m_pSearchBasePoint->GetPosition());
	}

	// ���񂵂Ă��Ȃ������琮�񂷂�
	else if (!CheckFormLine_Mine()) {

	}

	// �G�𔭌�������~�܂�
	else if (m_bSearchEnemy) {
		// �x�e���Ԓ��łȂ���Βe������
		if (!m_restTime) {
			// �w�����̕��m�ɒe����������
			ShotBullet();

			// �x�e���n�߂�
			m_restTime = 300;

		}
	}

	else {

		// �O���̕��m�񂪐��񂵂Ă��邩�ǂ�������������
		if (!CheckFormLine_Others()) {
			// �w�����̕��m�̈ړ�
			SoldierMove();

			// ���������������A���������Ɉړ�
			MovePosition(m_front * m_velocity);

			// �����̈ʒu���ڕW�n�_�𒴂���������������
			//if () {

			//	// �t���O�𗧂āA���̃t���[�����������ς��鏈�����s��

			//}



		}

	}

	// �G�����t���O���~�낷
	m_bSearchEnemy = false;

	// �x�e���Ԃ����炷
	m_restTime = m_restTime - 1 <= 0 ? 0 : m_restTime - 1;

}


// �w�����̓��I��������
// positon �F�����ʒu
// �Ԃ�l  �F�������ꂽ�w�����̃|�C���^
Commander* Commander::SetCommander(D3DXVECTOR3& position, D3DXVECTOR3& front, Object::GROUP group)
{
	// ���̎�����T��
	Commander* pCommander = (Commander*)Object::GetLDATA_HEAD(Object::TYPE::TYPE_COMMANDER);

	// �P������Ă��Ȃ������琶������
	if (pCommander == nullptr) {
		// ��������
		pCommander = Commander::CreateBuffer();

		// �ݒ菈��
		pCommander->SetCommander_private(position, front, group);

		// ���m�𐶐�����
		pCommander->SpawnSoldier();

		return pCommander;
	}

	// ����Ă����疢�g�p�̈��T��
	Commander* pCurrent = (Commander*)pCommander;
	Commander* pNext = (Commander*)pCommander->GetNextPointer();
	for (;;) {
		// ���g�p�Ȃ畺�m�𐶐����ďI��
		if (!pCurrent->GetInstance()) {
			// �ݒ菈��
			pCurrent->SetCommander_private(position, front, group);

			// ���m�𐶐�����
			pCurrent->SpawnSoldier();

			return pCurrent;
		}

		// ���g�p�̈悪������Ȃ���΁A�V������������
		if (pNext == nullptr) {
			// ��������
			pNext = Commander::CreateBuffer();

			// �ݒ菈��
			pNext->SetCommander_private(position, front, group);

			// ���m�𐶐�����
			pNext->SpawnSoldier();

			return pNext;
		}

		// �|�C���^�����炷
		pCurrent = pNext;
		pNext = (Commander*)pCurrent->GetNextPointer();

	}

}


// �w�����̕��m���玀�S�񍐂��󂯎��
// pSoldier�F���񂾕��m
void Commander::ReceiveReport_Death(Soldier* pSoldier)
{
	// �擪�̕��m�������ꍇ�͎��̕��m�ɓ���ւ���
	if (m_pSoldier == pSoldier) {
		m_pSoldier = m_pSoldier->GetNextSoldier();

		// ���̕��m�����Ȃ������ꍇ�͎w�����̎g�p�t���O���~�낵�A�ҋ@��Ԃɂ���
		if (m_pSoldier == nullptr) {
			m_bInstance = false;
			return;
		}

	}
	// �܂����m���c���Ă���ꍇ�́A���񂾕��m�̑O��̃��X�g���C������
	else {
		if (pSoldier->GetNextSoldier() != nullptr) pSoldier->GetNextSoldier()->SetPrevSoldier(pSoldier->GetPrevSoldier());
		if (pSoldier->GetPrevSoldier() != nullptr) pSoldier->GetPrevSoldier()->SetNextSoldier(pSoldier->GetNextSoldier());
	}

	// ���m�̈ʒu���C������
	{
		D3DXVECTOR3 vec;
		float move = 7.5f;
		Soldier* tagSoldier = m_pSoldier;

		// ���񂾕��m�̕����ɓ�����
		for (;;) {
			vec = pSoldier->GetPosition() - tagSoldier->GetPosition();
			D3DXVec3Normalize(&vec, &vec);
			tagSoldier->MovePosition(vec * move);

			tagSoldier = tagSoldier->GetNextSoldier();

			if (tagSoldier == nullptr)
				break;
		}
	}

}


// �w�����̕��m���狒�_�j��񍐂��󂯎��
void Commander::ReceiveReport_BreakBasePoint()
{
	// �w�����̕��m��S�ĎE��
	Soldier* pCurrent = m_pSoldier;

	if (pCurrent == nullptr) return;

	Soldier* pNext = pCurrent->GetNextSoldier();

	for (;;) {
		m_pSoldier->KillMe();

		if (m_pSoldier == nullptr)
			break;

	}


}


//=============================================================================
//	private �֐�
// �w�����̐ݒ菈��
void Commander::SetCommander_private(D3DXVECTOR3& position, D3DXVECTOR3& front, Object::GROUP group)
{
	// �ʒu
	SetPosition(position);

	// �O����
	m_front = front;

	// �����O���[�v
	SetGroup(group);

	// �x�e����
	m_restTime = 0;

	// �g�p���t���OON
	m_bInstance = true;

	// �����t���OOFF
	m_bSearchEnemy     = false;		// �G�����t���O
	m_pSearchBasePoint = nullptr;	// ���_�����t���O


}


// �w�����̕��m�𐶐�
void Commander::SpawnSoldier()
{
	D3DXVECTOR3 vecZ, vecX;
	vecZ = GetPosition() + m_front - GetPosition();

	D3DXVec3Cross(&vecX, &vecZ, &D3DXVECTOR3(0, 1, 0));
	vecX.y = 0.f;

	D3DXVec3Normalize(&vecX, &vecX);

	m_pSoldier = Soldier::SetSoldier(GetPosition() + vecX * *D3DXVECTOR3(-60, 0, 0), m_front, MODELDATA_SOLDIER, GetGroup(), this);

	m_pSoldier->SetPrevSoldier(nullptr);
	m_pSoldier->SetNextSoldier(nullptr);

	Soldier* pPrev    = m_pSoldier;
	Soldier* pCurrent = nullptr;

	D3DXVECTOR3 space(-60.f, 0, 0);

	for (int i = 1; i < 9; i++) {

		space.x += i * 15;
		D3DXVECTOR3 a(vecX.x * space.x, vecX.y * space.y, vecX.z * space.z);
		D3DXVECTOR3 b = vecX * * D3DXVECTOR3(-60.f + i * 15, 0, 0);
		float c = D3DXVec3Dot(&a, &b);

		//pCurrent = Soldier::SetSoldier(GetPosition() + a, m_front, MODELDATA_SOLDIER, GetGroup(), this);
		pCurrent = Soldier::SetSoldier(GetPosition() + vecX * * D3DXVECTOR3(-60.f + i * 15, 0, 0), m_front, MODELDATA_SOLDIER, GetGroup(), this);

		pPrev->SetNextSoldier(pCurrent);
		pCurrent->SetPrevSoldier(pPrev);
		pCurrent->SetNextSoldier(nullptr);

		pPrev = pCurrent;

	}

}


// �w�����̕��m��i�܂���
void Commander::SoldierMove()
{
	if (m_pSoldier == nullptr) return;

	Soldier* pCurrent = m_pSoldier;

	for (;;) {
		pCurrent->Run(m_front, m_velocity);

		if (pCurrent->GetNextSoldier() == nullptr) break;

		pCurrent = pCurrent->GetNextSoldier();

	}

}


// �O���̕��m�񂪐��񂵂Ă��邩�ǂ�������������
// �Ԃ�l�F	true  ���񂵂Ă���
//			false ���񂵂Ă��Ȃ��A���݂��Ȃ�
bool Commander::CheckFormLine_Others()
{
	Commander* pCurrent = (Commander*)Object::GetLDATA_HEAD(TYPE_COMMANDER);

	if (pCurrent == nullptr) return false;

	Commander* pNext = (Commander*)pCurrent->GetNextPointer();

	for (;;) {

		// �����ł͂Ȃ��A�g�p���A�����O���[�v
		if (pCurrent != this && pCurrent->GetInstance() && pCurrent->GetGroup() == GetGroup()) {
			// �����蔻��
			if (Collision_SphereToSphere(GetPosition() + m_front * *D3DXVECTOR3(0, 0, m_radius_ViewAngle), m_radius_ViewAngle, pCurrent->GetPosition(), 1.f)) {
				// ���񂵂Ă��邩�ǂ�������������
				if (pCurrent->GetFormLine()) {
					// �����͑�������O�ɂ��邩
					if ((pCurrent->GetPosition().z - GetPosition().z) * m_front.z > 0) {
						return true;

					}
				}
			}
		}

		pCurrent = pNext;

		if (pCurrent == nullptr) return false;

		pNext = (Commander*)pCurrent->GetNextPointer();

	}

}


// �w�����̕��m�𓃂ɓˌ�������
void Commander::AssaultBasePoint()
{
	Soldier* pCurrent = m_pSoldier;

	if (pCurrent == nullptr) return;

	Soldier* pNext = pCurrent->GetNextSoldier();

	for (;;)
	{
		// �ڕW���_��ݒ肷��
		pCurrent->SetTargetBasePoint(m_pSearchBasePoint);

		// ���������_�Ɍ�����
		pCurrent->SetRotateToObj(m_pSearchBasePoint->GetPosition());

		// ���_�Ɍ������Đi�܂���
		D3DXVECTOR3 vec = m_pSearchBasePoint->GetPosition() - pCurrent->GetPosition();
		D3DXVec3Normalize(&vec, &vec);
		pCurrent->Run(vec, m_velocity);

		if (pNext == nullptr)
			break;

		pCurrent = pNext;
		pNext = pCurrent->GetNextSoldier();

	}

}


// �w�����̕��m�ɒe����������
void Commander::ShotBullet()
{
	Soldier* pCurrent = m_pSoldier;

	if (pCurrent == nullptr) return;

	Soldier* pNext = pCurrent->GetNextSoldier();

	int i = 0;

	for (;;) {
		i++;
		pCurrent->ShotBullet();

		pCurrent = pNext;

		if (pCurrent == nullptr)
			break;

		pNext = pCurrent->GetNextSoldier();

	}

}


// �w�����̕��m�����񂵂Ă��邩�ǂ�������������
// �Ԃ�l�F	true  ���񂵂Ă���
//			false ���񂵂Ă��Ȃ�
bool Commander::CheckFormLine_Mine()
{
	Soldier* pBase = m_pSoldier;

	// ���m�̉E�����Ƀ��C���΂�
	


	// �S���m��position��臒l���Ȃ�� true ��Ԃ�



	return true;
	
}





