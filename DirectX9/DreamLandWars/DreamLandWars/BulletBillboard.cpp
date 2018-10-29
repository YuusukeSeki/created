//*****************************************************************************
//	
//		�o���b�g
//													Autohr : Yusuke Seki
//*****************************************************************************
#include "BulletBillboard.h"
#include "camera.h"


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
BulletBillboard::BulletBillboard() : Bullet3D(Object::TYPE::TYPE_3D_BILLBOARD_BULLET)
{
	m_pCamera = nullptr;
}

BulletBillboard::BulletBillboard(Object::TYPE type) : Bullet3D(type)
{
	m_pCamera = nullptr;
}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
BulletBillboard::~BulletBillboard()
{
	Uninit();
}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
BulletBillboard* BulletBillboard::Create(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera)
{
	// ���̂𐶐�
	BulletBillboard* pBullet = new BulletBillboard;

	// ������
	pBullet->Init(position, size, pCamera);

	return pBullet;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void BulletBillboard::Init(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera)
{
	// �p���f�[�^�̏�����
	Bullet3D::Init(position, size);

	// �J�����̎擾
	m_pCamera = pCamera;

}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void BulletBillboard::Uninit(void)
{
	Bullet3D::Uninit();
}


//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void BulletBillboard::Draw(void)
{
	Bullet3D::Draw();
}


//=============================================================================
//	private�֐�
// ���[���h�}�g���N�X�̍X�V
void BulletBillboard::UpdateWorldMatrix()
{
	if (m_pCamera == nullptr) {
		Object3D::UpdateWorldMatrix();
		return;
	}


	// �e�N���X����s�񐶐��p�̃f�[�^���擾
	D3DXVECTOR3    position = Object::GetPosition();
	D3DXQUATERNION rotate   = Bullet3D::GetRotate();
	D3DXVECTOR3    scale    = Bullet3D::GetScale();

	// �J��������r���[�s����擾
	D3DXMATRIX pMtxView = m_pCamera->GetMtxView();


	// �ړ��A��]�A�g�k�s��A�r���[�̋t�s��̌v�Z
	D3DXMATRIX mtxWorld, mtxTranslate, mtxRotate, mtxScale, mtxViewInverse;
	D3DXMatrixTranslation(&mtxTranslate, position.x, position.y, position.z);
	D3DXMatrixRotationYawPitchRoll(&mtxRotate, rotate.y, rotate.x, rotate.z);
	D3DXMatrixScaling(&mtxScale, scale.x, scale.y, scale.z);
	D3DXMatrixTranspose(&mtxViewInverse, &pMtxView);
	mtxViewInverse._14 = mtxViewInverse._24 = mtxViewInverse._34 = 0.0f;

	// �S�s��̍���
	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRotate);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxViewInverse);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���������s���ݒ�
	Bullet3D::SetWorldMatrix(mtxWorld);

	// ���[���h�}�g���N�X�̍X�V�t���OOFF
	Bullet3D::SetUpdateWorldMatrix(false);

}

