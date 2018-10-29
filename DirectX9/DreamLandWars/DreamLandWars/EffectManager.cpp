//*****************************************************************************
//	
//		�G�t�F�N�g���N���X�i���X�g�\���j
//													Author : Yusuke Seki
//*****************************************************************************
#include "EffectManager.h"
#include "renderer.h"


//----- �ÓI�����o�ϐ������� -----
EffectManager* EffectManager::m_pHEAD[EffectManager::TYPE::TYPE_MAX] = {};
EffectManager* EffectManager::m_pTAIL[EffectManager::TYPE::TYPE_MAX] = {};



//-----------------------------------------------------------------------------
//	�R���X�g���N�^
//-----------------------------------------------------------------------------
EffectManager::EffectManager(EffectManager::TYPE type)
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
		this->m_pNext = nullptr;
		this->m_pPrev = nullptr;

	}
	// �Q�ڈȏ�ɐ������ꂽ��ނȂ�A�����ɒǉ��B
	else {
		// �e�C���̎��̃|�C���^��"����"�ɂ���
		m_pTAIL[type]->m_pNext = this;

		// �O��̃|�C���^�̏�����
		this->m_pNext = nullptr;
		this->m_pPrev = m_pTAIL[type];

		// �e�C���̍X�V
		m_pTAIL[type] = this;

	}


	// �����o�ϐ��̏�����
	this->_position = D3DXVECTOR3(0, 0, 0);
	this->m_type = type;

}


//-----------------------------------------------------------------------------
//	��������F��
//-----------------------------------------------------------------------------
void EffectManager::Release()
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
void EffectManager::UpdateAll()
{
	int cnt[EffectManager::TYPE::TYPE_MAX] = {};


	for (int i = 0; i < EffectManager::TYPE::TYPE_MAX; i++) {
		EffectManager* pCurrent = m_pHEAD[i];

		for (;;) {
			if (pCurrent == nullptr) break;
			else {
				pCurrent->Update();
				pCurrent = pCurrent->m_pNext;

				cnt[i]++;
			}

		}
	}

	OX::DebugFont::print(0, SCREEN_HEIGHT - 80, 0xffff8080, "___Create Effect___");
	OX::DebugFont::print(0, SCREEN_HEIGHT - 60, 0xffff0000, "TYPE_3D                  : %d", cnt[TYPE_3D]);
	OX::DebugFont::print(0, SCREEN_HEIGHT - 40, 0xffff0000, "TYPE_3D_BILLBOARD        : %d", cnt[TYPE_3D_BILLBOARD]);
	OX::DebugFont::print(0, SCREEN_HEIGHT - 20, 0xffff0000, "TYPE_2D                  : %d", cnt[TYPE_2D]);

}


//-----------------------------------------------------------------------------
//	�`�揈���F�S��
//-----------------------------------------------------------------------------
void EffectManager::DrawAll()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//// ���e�X�g�̐ݒ�
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ���e�X�g�n�m
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 128);				// ����l
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ���Z�q
	
	// �J�����O��؂�
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �u�����h���@�ύX
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Z�o�b�t�@���������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �`�揈��
	for (int i = 0; i < EffectManager::TYPE::TYPE_MAX; i++) {
		EffectManager* pCurrent = m_pHEAD[i];

		for (;;) {
			if (pCurrent == nullptr) break;
			else {
				pCurrent->Draw();
				pCurrent = pCurrent->m_pNext;
			}

		}
	}

	// �����_�[�X�e�[�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);				// Z�o�b�t�@����������
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// �u�����h���@��߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);					// ���C�g��L���ɖ߂�
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// �J�����O���[�h�𔽎��v���ɂ��܂�

	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// ���e�X�g�I��

}


//-----------------------------------------------------------------------------
//	��������F�S��
//-----------------------------------------------------------------------------
void EffectManager::ReleaseAll()
{
	for (int i = 0; i < EffectManager::TYPE::TYPE_MAX; i++) {
		if (m_pHEAD[i] == nullptr) continue;

		EffectManager* pCurrent = m_pHEAD[i];
		EffectManager* pNext = m_pHEAD[i]->m_pNext;

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


