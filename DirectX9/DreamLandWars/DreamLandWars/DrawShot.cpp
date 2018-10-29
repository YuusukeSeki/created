//*****************************************************************************
//	
//		�h���[�V���b�g
//													Autohr : Yusuke Seki
//*****************************************************************************
// base
#include "DrawShot.h"
#include "DrawLine.h"
#include "player.h"

// fw
#include "collision.h"
#include "camera.h"

// resource
#include "MainGame.h"
#include "list_LoadTexture_MainGame.h"

// effect
#include "EffectBillboard.h"

// object
#include "Soldier.h"
#include "tower.h"


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
DrawShot::DrawShot(Object::TYPE type) : Bullet3D(type)
{
	// �f�[�^�̃N���A
	m_pMoveWay      = nullptr;				// �ړ��o�H
	m_vecPrevToNext = D3DXVECTOR3(0, 0, 0);	// �o�H���̒P�ʃx�N�g��
	m_pCamera       = nullptr;				// �J����
	m_pPlayer       = nullptr;				// �e�v���C���[

}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
DrawShot::~DrawShot()
{
	Uninit();
}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
DrawShot* DrawShot::Create(D3DXVECTOR3& position, D3DXVECTOR3& size)
{
	// ���̂𐶐�
	DrawShot* pDrawShot = new DrawShot(Object::TYPE::TYPE_3D_DRAWSHOT);

	// ������
	pDrawShot->Init(position, size);

	return pDrawShot;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void DrawShot::Init(D3DXVECTOR3& position, D3DXVECTOR3& size)
{
	// �f�[�^�̏�����
	Bullet3D::Init(position, size);							// �p���f�[�^
	m_pMoveWay      = nullptr;								// �ړ��o�H
	m_vecPrevToNext = D3DXVECTOR3(0, 0, 0);					// �o�H���̒P�ʃx�N�g��
	m_pCamera       = nullptr;								// �J����
	m_pPlayer       = nullptr;								// �e�v���C���[

	ClearCollisionID();	// �����������m�̏�����

}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void DrawShot::Uninit(void)
{
	Bullet3D::Uninit();

}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void DrawShot::Update(void)
{
	// �y�X�V����z
	if (!this->GetInstance()) return;	// ���g�p�ŏ�������

	//�ړ�
	{
		D3DXVECTOR3 move, position, vec;
		float result;

		// �ړ��ʂ̎Z�o
		move     = GetVecZ() * GetMove();
		position = GetPosition() + move;
		vec      = m_pMoveWay->GetNextPointer_DrawLine()->GetPosition() - GetPosition();

		// �ڕW�n�_�𒴂��Ă��Ȃ����̔���
		D3DXVec3Normalize(&vec, &vec);
		result = D3DXVec3Dot(&vec, &m_vecPrevToNext);
		if (result <= 0) { // �����Ă���

			// �ړ��ʂ̏C��
			move = m_pMoveWay->GetNextPointer_DrawLine()->GetPosition() - GetPosition();

			// �o�H�����̒n�_�֕ύX
			{
				DrawLine* pNextWay;
				D3DXVECTOR3 currentPos, nextPos, vec;

				// ���݂̃|�C���^�[�����̃|�C���^�[�ɕύX
				pNextWay   = m_pMoveWay->GetNextPointer_DrawLine();
				m_pMoveWay->ClearParameter();
				m_pMoveWay = pNextWay;

				// ���̒n�_���������DS�I��
				if (m_pMoveWay->GetNextPointer_DrawLine() == nullptr) {
					m_pMoveWay->ClearParameter();
					ClearCollisionID();
					SetInstance(false);
					return;
				}

				// �e�̌������Z�o
				currentPos = m_pMoveWay->GetPosition();
				nextPos    = m_pMoveWay->GetNextPointer_DrawLine()->GetPosition();
				vec        = nextPos - currentPos;
				D3DXVec3Normalize(&vec, &vec);
				
				// �e�̌������X�V
				SetVecZ(vec);
				m_vecPrevToNext = vec;

			}

		}// End.. ���ߔ���

		// �ړ�
		MovePosition(move);

		// �G�t�F�N�g�̔���
		Effect3D::SetEffect(GetPosition(), GetVecZ(), EffectBillboard::TYPE::TYPE_FIRE);
		Effect3D::SetEffect(GetPosition(), GetVecZ(), EffectBillboard::TYPE::TYPE_FIRE);
		//EffectBillboard::SetEffect(GetPosition(), GetVecZ(), MainGame::GetCamera(0), EffectBillboard::TYPE::TYPE_FIRE);
		//EffectBillboard::SetEffect(GetPosition(), GetVecZ(), MainGame::GetCamera(0), EffectBillboard::TYPE::TYPE_FIRE);

	}

	// ���m�Ƃ̓����蔻��
	CollisionSoldier();

	// ���Ƃ̓����蔻��
	if (Collision_Tower()) {
		DrawLine::ClearParameter_List(m_pMoveWay);
		ClearCollisionID();
		SetInstance(false);
	}

}


//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawShot::Draw(void)
{
	// ���g�p�ŏ�������
	if (!Bullet3D::GetInstance()) return;


	// �`������
	Bullet3D::Draw();
}


//=============================================================================
//	�ݒ菈��
//	DS�̔���
void DrawShot::SetDrawShot(DrawLine* pStartPoint)
{
	// �n�_��NULL�`�F�b�N
	if (pStartPoint == nullptr) {
		// �G���[���b�Z�[�W
		_MSGERROR("pStartPoint cannnot be nullptr!!", "void DrawShot::SetDrawShot(DrawLine* pStartPoint)");
	}


	// ���̎�����T��
	DrawShot* pDrawShot = (DrawShot*)Object::GetLDATA_HEAD(Object::TYPE::TYPE_3D_DRAWSHOT);

	// �P������Ă��Ȃ������琶������
	if (pDrawShot == nullptr) {
		// ��������
		pDrawShot = DrawShot::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(5, 5, 0));

		// �ݒ菈��
		pDrawShot->SetDrawShot_private(pStartPoint);

		return;
	}

	// ����Ă����疢�g�p�̈��T��
	DrawShot* pCurrent = (DrawShot*)pDrawShot;
	DrawShot* pNext    = (DrawShot*)pDrawShot->GetNextPointer();
	for (;;) {
		// ���g�p�Ȃ�ݒ肵�ďI��
		if (!pCurrent->GetInstance()) {
			pCurrent->SetDrawShot_private(pStartPoint);
			break;
		}

		// ���g�p�̈悪������Ȃ���΁A�V������������
		if (pNext == nullptr) {
			// ��������
			pNext = DrawShot::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(5, 5, 0));

			// �ݒ菈��
			pNext->SetDrawShot_private(pStartPoint);

			break;
		}

		// �|�C���^�����炷
		pCurrent = pNext;
		pNext    = (DrawShot*)pCurrent->GetNextPointer();

	}

}


//=============================================================================
//	private�֐�
// ���m�Ƃ̓����蔻��
void DrawShot::CollisionSoldier()
{
	Soldier* pSoldier = (Soldier*)Object::GetLDATA_HEAD(TYPE_MODEL_SOLDIER);

	if (pSoldier == nullptr) return;

	Soldier* pCurrent = pSoldier;
	Soldier* pNext = (Soldier*)pSoldier->GetNextPointer();

	for (;;) {

		// ���̂�����A�����ƈႤ�w�c�̕��m���𔻒�
		if (pCurrent->GetInstance() && pCurrent->GetGroup() != GetGroup())
			
			// �������Ă�H
			if (Collision_SphereToSphere(GetPosition(), GetRadius(), pCurrent->GetPosition(), pCurrent->GetRadius())) {

				// �܂��������Ă��Ȃ��Ώۂ��𔻒�
				for (int i = 0; i <= m_cntCollisionSoldier; i++) {
					if (m_CollisionID_Soldier[i] == pCurrent->GetID()) {
						// �������Ă���
						break;
					}
					else if (m_CollisionID_Soldier[i] == CLEAR_ID) {
						// �܂��������Ă��Ȃ�

						// �������������ID���L��
						m_CollisionID_Soldier[m_cntCollisionSoldier] = pCurrent->GetID();
						m_cntCollisionSoldier++;

						// �_���[�W��^����
						pCurrent->Attack(m_pPlayer->GetDrawShotDamage(), m_vecPrevToNext, m_pPlayer->GetDrawShotSpeed(), m_pPlayer);
						//pCurrent->Damage(m_pPlayer->GetDrawShotDamage());

						break;

					}
				}
			}

		pCurrent = pNext;

		if (pCurrent == nullptr) return;

		pNext = (Soldier*)pCurrent->GetNextPointer();

	}

}

// ���Ƃ̓����蔻��
// �Ԃ�l�F	true  ��������
//			false �������ĂȂ�
bool DrawShot::Collision_Tower()
{
	Tower* pTower = (Tower*)Object::GetLDATA_HEAD(TYPE_MODEL_TOWER);

	if (pTower == nullptr) return false;

	Tower* pCurrent = pTower;
	Tower* pNext = (Tower*)pTower->GetNextPointer();

	for (;;) {

		if (pCurrent->GetGroup() != GetGroup())
			if (Collision_SphereToSphere(GetPosition(), GetRadius(), pCurrent->GetPosition(), pCurrent->GetHalfSize().x)) return true;

		pCurrent = pNext;

		if (pCurrent == nullptr) return false;

		pNext = (Tower*)pCurrent->GetNextPointer();

	}

}

// DS�̐ݒ�
void DrawShot::SetDrawShot_private(DrawLine* pStartPoint)
{
	// �e�v���C���[�̎擾
	m_pPlayer = pStartPoint->GetPlayer_DrawLine();

	// �o�H�̎擾
	m_pMoveWay = pStartPoint;

	// ���W�̐ݒ�
	SetPosition(pStartPoint->GetPosition());

	// �����w�c�̐ݒ�
	SetGroup(pStartPoint->GetPlayer_DrawLine()->GetGroup());

	// �����̐ݒ�
	{
		// �X�^�[�g�n�_���擾
		D3DXVECTOR3 startPos = m_pMoveWay->GetPosition();

		// ���̖ڕW�n�_���擾
		D3DXVECTOR3 nextPos = m_pMoveWay->GetNextPointer_DrawLine()->GetPosition();

		// ������ݒ�
		D3DXVECTOR3 vec = nextPos - startPos;
		D3DXVec3Normalize(&vec, &vec);
		Bullet3D::SetVecZ(vec);

		// ���̒n�_�܂ł̃x�N�g����ۑ�
		m_vecPrevToNext = vec;

	}
	//SetVecZ(pStartPoint->GetPlayer_DrawLine()->GetVecZ());

	// �����x�̐ݒ�
	SetMove(pStartPoint->GetPlayer_DrawLine()->GetDrawShotSpeed());

	// �����x�̐ݒ�
	SetAccelerate(0);

	// �J�����̎擾
	m_pCamera = pStartPoint->GetPlayer_DrawLine()->GetCamera();

	// �g�p�t���OON
	SetInstance(true);

}

// �������������������
void DrawShot::ClearCollisionID()
{
	for (int i = 0; i < NUM_COLLISION_ID_SOLDIER; i++)
	{
		m_CollisionID_Soldier[i] = CLEAR_ID;
	}

	m_cntCollisionSoldier = 0;

}
