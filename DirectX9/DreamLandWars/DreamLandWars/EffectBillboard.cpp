//*****************************************************************************
//
//		�G�t�F�N�g�i���X�g�\���j
//												Autohr	:	Yusuke Seki
//*****************************************************************************
#include "EffectBillboard.h"
#include "renderer.h"
#include "MainGame.h"
#include "camera.h"



//-----------------------------------------------------------------------------
//	�R���X�g���N�^
//-----------------------------------------------------------------------------
EffectBillboard::EffectBillboard(EffectManager::TYPE type) :Effect3D(type)
{
	// �f�[�^�̏�����
	m_pCamera = nullptr;
}


//-----------------------------------------------------------------------------
//	�f�X�g���N�^
//-----------------------------------------------------------------------------
EffectBillboard::~EffectBillboard()
{
	EffectBillboard::Uninit();
}


//-----------------------------------------------------------------------------
//	����
//-----------------------------------------------------------------------------
EffectBillboard* EffectBillboard::Create(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera)
{
	EffectBillboard* pEffectBillboard = new EffectBillboard(EffectManager::TYPE::TYPE_3D_BILLBOARD);
	pEffectBillboard->Init(position, size, pCamera);

	return pEffectBillboard;
}


//-----------------------------------------------------------------------------
//	������
//-----------------------------------------------------------------------------
void EffectBillboard::Init(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera)
{
	// �f�[�^�̏�����
	m_pCamera = pCamera;			// �J����
	Effect3D::Init(position, size);	// �p���f�[�^�̏�����

}


//-----------------------------------------------------------------------------
//	�I��
//-----------------------------------------------------------------------------
void EffectBillboard::Uninit(void)
{
	// �p���f�[�^�̏I������
	Effect3D::Uninit();

}


//-----------------------------------------------------------------------------
//	�X�V
//-----------------------------------------------------------------------------
void EffectBillboard::Update(void)
{
	// �p���f�[�^�̍X�V����
	Effect3D::Update();

}


//-----------------------------------------------------------------------------
//	�`��
//-----------------------------------------------------------------------------
void EffectBillboard::Draw(void)
{
	// �`�揈���͐e�N���X�Ɋۓ���
	Effect3D::Draw();

}


//=============================================================================
//	�ݒ�
//	�G�t�F�N�g�̔���
void EffectBillboard::SetEffect(D3DXVECTOR3& position, D3DXVECTOR3& vecZ, Camera* pCamera, Effect3D::TYPE effectType)
{
	// ���̎�����T��
	EffectBillboard* pEffectBillboard = (EffectBillboard*)EffectManager::GetLDATA_HEAD(EffectManager::TYPE::TYPE_3D);

	// �P������Ă��Ȃ������琶������
	if (pEffectBillboard == nullptr) {
		// ��������
		pEffectBillboard = EffectBillboard::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), pCamera);

		// �ݒ菈��
		pEffectBillboard->SetEffect_Protected(position, vecZ, effectType);

		return;
	}

	// ����Ă����疢�g�p�̃G�t�F�N�g��T��
	EffectBillboard* pCurrent = (EffectBillboard*)pEffectBillboard;
	EffectBillboard* pNext    = (EffectBillboard*)pEffectBillboard->GetNextPointer();
	for (;;) {
		// ���g�p�Ȃ�ݒ肵�ďI��
		if (!pCurrent->GetInstance()) {
			pCurrent->SetEffect_Protected(position, vecZ, effectType);
			break;
		}

		// ���g�p�G�t�F�N�g��������Ȃ���΁A�V������������
		if (pNext == nullptr) {
			// ��������
			pNext = EffectBillboard::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), pCamera);

			// �ݒ菈��
			pNext->SetEffect_Protected(position, vecZ, effectType);

			break;
		}

		// �|�C���^�����炷
		pCurrent = pNext;
		pNext    = (EffectBillboard*)pCurrent->GetNextPointer();

	}
}


//=============================================================================
//	private�֐�
// ���[���h�}�g���N�X�̍X�V
void EffectBillboard::UpdateWorldMatrix()
{
	// �e�N���X����s�񐶐��p�̃f�[�^���擾
	D3DXVECTOR3* pPosition = EffectManager::GetPosition();
	D3DXVECTOR3* pRotate = Effect3D::GetRotate();
	D3DXVECTOR3* pScale = Effect3D::GetScale();

	// �J��������r���[�s����擾
	D3DXMATRIX mtxView = m_pCamera->GetMtxView();


	// �ړ��A��]�A�g�k�s��A�r���[�̋t�s��̌v�Z
	D3DXMATRIX mtxWorld, mtxTranslate, mtxRotate, mtxScale, mtxViewInverse;
	D3DXMatrixTranslation(&mtxTranslate, pPosition->x, pPosition->y, pPosition->z);
	D3DXMatrixRotationYawPitchRoll(&mtxRotate, pRotate->y, pRotate->x, pRotate->z);
	D3DXMatrixScaling(&mtxScale, pScale->x, pScale->y, pScale->z);
	D3DXMatrixTranspose(&mtxViewInverse, &mtxView);
	mtxViewInverse._14 = mtxViewInverse._24 = mtxViewInverse._34 = 0.0f;

	// �S�s��̍���
	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxViewInverse);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRotate);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���N�X�̍X�V�t���OOFF
	Effect3D::SetUpdateWorldMatrix(false);

}

