//*****************************************************************************
//
//		��
//													Autohr : Yusuke Seki
//*****************************************************************************
#include "castle.h"

#include "MainGame.h"	// ���g�̍��W�ݒ�̂���
#include "field.h"		// ���g�̍��W�ݒ�̂���
#include "Wall.h"		// ���g�̍��W�ݒ�̂���

#include "Hold.h"		// �����͈͂��������邽��
#include "player.h"		// �����͈͂��������邽��

#include "collision.h"	// 3D�����蔻��p�֗̕��֐�

#include "Commander.h"	// ���m�����̂���

#include "TeamGaugeManager.h"	// �`�[���Q�[�W�ɉe����^���邽��
#include "TeamGauge.h"			// �`�[���Q�[�W�ɉe����^���邽��

#include "Etc_Paramaters.h"



//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Castle::Castle() : ObjectModel(Object::TYPE::TYPE_MODEL_CASTLE)
{
	// �����o�ϐ�������
	m_browRange = 0.f;	// �����͈�
	m_pHold = nullptr;	// �����͈͂�GUI
	m_frameCounter = 0;	// ���m�����p�t���[���J�E���^�[
	vector_LEFT  = D3DXVECTOR3(0, 0, 0);	// ���m�������̏����ڕW���W
	vector_RIGHT = D3DXVECTOR3(0, 0, 0);	// ���m�������̏����ڕW���W

}


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Castle::Castle(Object::TYPE type) : ObjectModel(type)
{
	// �����o�ϐ�������
	m_browRange = 0.f;	// �����͈�
	m_pHold = nullptr;	// �����͈͂�GUI
	m_frameCounter = 0;	// ���m�����p�t���[���J�E���^�[
	vector_LEFT = D3DXVECTOR3(0, 0, 0);	// ���m�������̏����ڕW���W
	vector_RIGHT = D3DXVECTOR3(0, 0, 0);	// ���m�������̏����ڕW���W

}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
Castle::~Castle()
{
	Uninit();

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
Castle* Castle::Create(const char* FileName, Object::GROUP group)
{
	Castle* pCastle = new Castle(Object::TYPE::TYPE_MODEL_CASTLE);
	pCastle->Init(FileName, group);

	return pCastle;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void Castle::Init(const char* FileName, Object::GROUP group)
{
	// �p���f�[�^�̏�����
	ObjectModel::Init(D3DXVECTOR3(0, 0, 0), FileName);

	// �O���[�v�̐ݒ�
	SetGroup(group);

	// �O���[�v����Ńf�[�^���C��
	// ���@�C���ΏہF���W�A�F�A�����A���m�̏����ڕW���W
	{
		Field* pField = MainGame::GetField();
		Wall* pWall = MainGame::GetWall(3);
		D3DXVECTOR3 length(0, 0, pField->GetPosition().z + pField->GetHalfSize().z - pWall->GetHalfSize().z * 2 - GetHalfSize().z);
		D3DXVECTOR3 setPos(pField->GetPosition().x, 0, 0);
		vector_LEFT  = D3DXVECTOR3(-1, 0, 1);
		vector_RIGHT = D3DXVECTOR3(1, 0, 1);

		// Side Your Team
		if (GetGroup() == Object::GROUP_A) {
			SetPosition(setPos - length);
			SetColor(0xff0000a0);
			SetFront(D3DXVECTOR3(0, 0, 1));

		}

		// Side Enemy
		else if(GetGroup() == Object::GROUP_B) {
			SetPosition(setPos + length);
			SetColor(0x0000ffa0);
			SetRotate(D3DXVECTOR3(0, D3DXToRadian(180), 0));
			SetFront(D3DXVECTOR3(0, 0, -1));
			vector_LEFT  *= -1;
			vector_RIGHT *= -1;

		}
		// Error Command
		else {
			_MSGERROR("Castle cannot be 'GROUP_NONE'!!", "Error!!");
			Release();

			return;
		}

	}

	// �����͈͂̐ݒ�
	m_browRange = GetSize().x * 1.05f;

	// �����͈͂�GUI����
	m_pHold = Hold::Create(this, MainGame::GetCamera(0));

	// ���m�����p�J�E���^�[�̏����l�ݒ�
	m_frameCounter = 1500;

}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void Castle::Uninit(void)
{
	// �p���f�[�^�̏I������
	ObjectModel::Uninit();

}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void Castle::Update(void)
{
	//// ���m�����p�t���[���J�E���^�[����
	//m_frameCounter++;

	//// �t���[���J�E���^�[���K��l�𒴂����畺�m�𐶐�����
	//if (m_frameCounter >= Castle::_INTERVAL_CREATE_SOLDIER) {
	//	D3DXVECTOR3 vecX;
	//	D3DXVec3Cross(&vecX, &vector_LEFT, &D3DXVECTOR3(0, 1, 0));
	//	vecX.y = 0.f;
	//	vecX.z = 0;

	//	D3DXVec3Normalize(&vecX, &vecX);

	//	vecX *= 20;

	//	// �����[��
	//	Commander::SetCommander(GetPosition() + vecX, vector_LEFT, GetGroup());

	//	// �E���[��
	//	Commander::SetCommander(GetPosition() + vecX * -1, vector_RIGHT, GetGroup());

	//	// �J�E���^�[�������߂�
	//	m_frameCounter = 0;

	//}

	// �����͈͂̉�������
	{
		// �v���C���[���X�g�̐擪�f�[�^���擾
		Player* pCurrent = (Player*)Object::GetLDATA_HEAD(Object::TYPE::TYPE_MODEL_PLAYER);

		// Error Command
		if (pCurrent == nullptr)
			return;

		// �G�L���X�g�Ǝ��g�Ƃ̋������K��l�ȓ��ŁA������Ԃ���������
		for (;;) {

			// �G�L���X�g���ǂ����𔻒�
			if (pCurrent->GetGroup() != GetGroup()) {

				// �������K��l�ȓ��Ȃ牣����Ԃł��邱�Ƃ���������
				if (Distance3D(pCurrent->GetPosition(), GetPosition()) <= m_browRange * m_browRange) {
					m_pHold->SetDrawHold(true);
				}

				// �͈͊O�Ȃ��\��
				else {
					m_pHold->SetDrawHold(false);
				}

			}

			// ���̃L���X�g��
			pCurrent = (Player*)pCurrent->GetNextPointer();

			// ���̃L���X�g�����Ȃ���Δ���I��
			if (pCurrent == nullptr) {
				break;
			}

		}

	}


}


//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void Castle::Draw(void)
{
	// �`�揈���͐e���Ɋۓ���
	ObjectModel::Draw();

}


// �_���[�W��^����
// breakPower : �^����_���[�W
void Castle::BrowCastle(float breakPower)
{
	TeamGaugeManager::GetTeamGauge_ENEMY()->MoveLife(-breakPower * CASTLE_RETOUCH_BREAKPOWER);

}

// �����͈͂Ƃ̓����蔻��
// position : �ΏۃL���X�g�̈ʒu
// �y�Ԃ�l�z	true  : �����
//				false : ����Ȃ�
bool Castle::CollisionBrowRange(D3DXVECTOR3& position)
{
	if (Distance3D(GetPosition(), position) <= m_browRange * m_browRange)
		return true;

	return false;

}


