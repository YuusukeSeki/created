//*****************************************************************************
//
//		�r���{�[�h�i���X�g�\���j
//												Autohr : Yusuke Seki
//*****************************************************************************
#include "ObjectBillboard.h"
#include "renderer.h"
#include "camera.h"


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
ObjectBillboard::ObjectBillboard(Object::TYPE type) :Object3D_Quaternion(type)
{
	// �����o�ϐ�������
	m_pCamera = nullptr;

}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
ObjectBillboard::~ObjectBillboard()
{
	// �I������
	Uninit();

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
ObjectBillboard* ObjectBillboard::Create(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera)
{
	// ����
	ObjectBillboard* pObjectBillboard = new ObjectBillboard(Object::TYPE::TYPE_3D_BILLBOARD);

	// ������
	pObjectBillboard->Init(position, size, pCamera);

	return pObjectBillboard;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void ObjectBillboard::Init(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera)
{
	//----- �f�[�^�̐ݒ� -----
	m_pCamera = pCamera;			// �J����
	Object3D_Quaternion::Init(position, size);	// ���̑��A�s��֌W�Ⓒ�_�o�b�t�@�֌W�A�t���O�Ȃ�

	// �s����Z�o
	//this->UpdateWorldMatrix();

}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void ObjectBillboard::Uninit(void)
{
	// �p���f�[�^�̏I������
	Object3D_Quaternion::Uninit();

	// �J�����|�C���^�������
	m_pCamera = nullptr;

}


//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void ObjectBillboard::Draw(void)
{
	// �`��@�\�͐e�N���X����
	Object3D_Quaternion::Draw();

}



//=============================================================================
//	��������


//=============================================================================
// �ݒ菈��


//=============================================================================
//	private�֐�
// ���[���h�}�g���N�X�̍X�V
void ObjectBillboard::UpdateWorldMatrix()
{
	// �e�N���X����s�񐶐��p�̃f�[�^���擾
	D3DXVECTOR3    position   = Object::GetPosition();
	D3DXQUATERNION quaternion = Object3D_Quaternion::GetQuaternion();
	D3DXVECTOR3    scale      = Object3D_Quaternion::GetScale();

	// �J��������r���[�s����擾
	D3DXMATRIX pMtxView = m_pCamera->GetMtxView();

	// �ړ��A��]�A�g�k�s��A�r���[�̋t�s��̌v�Z
	D3DXMATRIX mtxWorld, mtxTranslate, mtxRotate, mtxScale, mtxViewInverse;
	D3DXMatrixTranslation(&mtxTranslate, position.x, position.y, position.z);
	D3DXMatrixRotationQuaternion(&mtxRotate, &quaternion);
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
	Object3D_Quaternion::SetWorldMatrix(mtxWorld);

	// ���[���h�}�g���N�X�̍X�V�t���OOFF
	Object3D_Quaternion::SetUpdateWorldMatrix(false);

}
