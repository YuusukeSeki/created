//*****************************************************************************
//	
//		�I�u�W�F�N�g���N���X�i���X�g�\���j
//													Author : Yusuke Seki
//*****************************************************************************
#include "Object.h"


//----- �ÓI�����o�ϐ������� -----
Object* Object::m_pHEAD[Object::TYPE::TYPE_MAX] = {};
Object* Object::m_pTAIL[Object::TYPE::TYPE_MAX] = {};



//-----------------------------------------------------------------------------
//	�R���X�g���N�^
//-----------------------------------------------------------------------------
Object::Object(Object::TYPE type)
{
	// ���߂Đ������ꂽ��ނȂ�A�擪�Ƀ|�C���^�����B
	if (m_pHEAD[type] == nullptr) {
		// �w�b�h�̍X�V
		m_pHEAD[type] = this;
		m_pHEAD[type]->m_pNext = nullptr;
		m_pHEAD[type]->m_pPrev = nullptr;

		// �e�C���̍X�V
		m_pTAIL[type] = m_pHEAD[type];

		// �O��̃|�C���^�̏�����
		this->m_pNext    = nullptr;
		this->m_pPrev    = nullptr;

	}
	// �Q�ڈȏ�ɐ������ꂽ��ނȂ�A�����ɒǉ��B
	else {
		// �e�C���̎��̃|�C���^��"����"�ɂ���
		m_pTAIL[type]->m_pNext = this;

		// �O��̃|�C���^�̏�����
		this->m_pNext    = nullptr;
		this->m_pPrev    = m_pTAIL[type];

		// �e�C���̍X�V
		m_pTAIL[type] = this;

	}


	// �����o�ϐ��̏�����
	this->_position = D3DXVECTOR3(0, 0, 0);
	this->m_type = type;

#ifdef _WLW
	this->m_group = Object::GROUP::GROUP_NONE;
#endif

}


//-----------------------------------------------------------------------------
//	��������F��
//-----------------------------------------------------------------------------
void Object::Release()
{
	// �O��̃I�u�W�F�N�g�������Ă���A�O��̃|�C���^���X�V
	if (this->m_pNext != nullptr) m_pNext->m_pPrev = this->m_pPrev;
	if (this->m_pPrev != nullptr) m_pPrev->m_pNext = this->m_pNext;

	// �w�b�h�̃|�C���^���X�V
	if (m_pHEAD[m_type] == this) m_pHEAD[m_type] = this->m_pNext;

	// �e�C���̃|�C���^���X�V
	if (m_pTAIL[m_type] == this) m_pTAIL[m_type] = this->m_pPrev;

	// �I������
	this->Uninit();

	// �������̉��
	delete this;

}


//-----------------------------------------------------------------------------
//	�X�V�����F�S��
//-----------------------------------------------------------------------------
void Object::UpdateAll()
{
	int cnt[Object::TYPE::TYPE_MAX] = {};


	for (int i = 0; i < Object::TYPE::TYPE_MAX; i++) {
		Object* pCurrent = m_pHEAD[i];


		for (;;) {
			if (pCurrent == nullptr) break;
			else {
				pCurrent->Update();
				pCurrent = pCurrent->m_pNext;

				cnt[i]++;
			}
		}
	}

	OX::DebugFont::print(0, SCREEN_HEIGHT - 420, 0xffff8080, "___Create Object___");
	OX::DebugFont::print(0, SCREEN_HEIGHT - 380, 0xffff0000, "TYPE_COMMANDER           : %d", cnt[TYPE_COMMANDER]);
	OX::DebugFont::print(0, SCREEN_HEIGHT - 360, 0xffff0000, "TYPE_MODEL_SOLDIER       : %d", cnt[TYPE_MODEL_SOLDIER]);
	OX::DebugFont::print(0, SCREEN_HEIGHT - 300, 0xffff0000, "TYPE_MODEL_TOWER         : %d", cnt[TYPE_MODEL_TOWER]);
	OX::DebugFont::print(0, SCREEN_HEIGHT - 260, 0xffff0000, "TYPE_3D_BILLBOARD        : %d", cnt[TYPE_3D_BILLBOARD]);
	OX::DebugFont::print(0, SCREEN_HEIGHT - 240, 0xffff0000, "TYPE_3D_SOLDIERBULLET    : %d", cnt[TYPE_3D_SOLDIERBULLET]);
	OX::DebugFont::print(0, SCREEN_HEIGHT - 220, 0xffff0000, "TYPE_3D_BILLBOARD_BULLET : %d", cnt[TYPE_3D_BILLBOARD_BULLET]);
	OX::DebugFont::print(0, SCREEN_HEIGHT - 200, 0xffff0000, "TYPE_3D_BILLBOARD_EFFECT : %d", cnt[TYPE_3D_BILLBOARD_EFFECT]);
	OX::DebugFont::print(0, SCREEN_HEIGHT - 180, 0xffff0000, "TYPE_3D_STRAIGHTSHOT     : %d", cnt[TYPE_3D_STRAIGHTSHOT]);
	OX::DebugFont::print(0, SCREEN_HEIGHT - 160, 0xffff0000, "TYPE_3D_DRAWLINE         : %d", cnt[TYPE_3D_DRAWLINE]);
	OX::DebugFont::print(0, SCREEN_HEIGHT - 140, 0xffff0000, "TYPE_3D_DRAWSHOT         : %d", cnt[TYPE_3D_DRAWSHOT]);

}


//-----------------------------------------------------------------------------
//	�`�揈���F�S��
//-----------------------------------------------------------------------------
void Object::DrawAll()
{
	for (int i = 0; i < Object::TYPE::TYPE_MAX; i++) {
		Object* pCurrent = m_pHEAD[i];

		for (;;) {
			if (pCurrent == nullptr) break;
			else {
				pCurrent->Draw();
				pCurrent = pCurrent->m_pNext;

			}

		}
	}

}


//-----------------------------------------------------------------------------
//	��������F�S��
//-----------------------------------------------------------------------------
void Object::ReleaseAll()
{
	for (int i = 0; i < Object::TYPE::TYPE_MAX; i++) {
		if (m_pHEAD[i] == nullptr) continue;

		Object* pCurrent = m_pHEAD[i];
		Object* pNext    = m_pHEAD[i]->m_pNext;

		for (;;) {
			if (pCurrent == nullptr) break;
			else {
				pNext = pCurrent->m_pNext;
				pCurrent->Release();
				pCurrent = pNext;
				
			}

		}
	}

}


