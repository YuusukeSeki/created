//*****************************************************************************
//
//		�J����
//												Autohr : Yusuke Seki
//*****************************************************************************
#include "camera.h"
#include "renderer.h"
#include <math.h>
#include "GameManager.h"
#include "MainGame.h"
#include "skybox.h"
//#include "input.h"



//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Camera::Camera()
{
	// �����o�ϐ�������
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixIdentity(&m_mtxProj);
	D3DXMatrixIdentity(&m_mtxZRot);
	D3DXMatrixIdentity(&m_mtxTrans);
	m_posEye = m_posAt  = m_vecUp  = m_distance = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_rot = 0.f;

}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
Camera::~Camera()
{
	Uninit();
}


//-----------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------
Camera* Camera::Create(D3DXVECTOR3 posEye, D3DXVECTOR3 posAt, D3DXVECTOR3 vecUp, float fNear, float fFar)
{
	Camera* pCamera = new Camera;
	pCamera->Init(posEye, posAt, vecUp, fNear, fFar);

	return pCamera;
}


//-----------------------------------------------------------------------------
// �������
//-----------------------------------------------------------------------------
void Camera::Release()
{
	delete this;
}


//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
void Camera::Init(D3DXVECTOR3 posEye, D3DXVECTOR3 posAt, D3DXVECTOR3 vecUp, float fNear, float fFar)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// �ʒu�ݒ�
	m_posEye = posEye;

	// �����_�ݒ�
	m_posAt = posAt;

	// ������ݒ�
	m_vecUp = vecUp;

	// ���_�ƒ����_�Ƃ̋��������߂�
	m_distance = m_posAt - m_posEye;
	//float dx = m_posAt.x - m_posEye.x;
	//float dy = m_posAt.y - m_posEye.y;
	//float dz = m_posAt.z - m_posEye.z;
	//m_distance.z = sqrtf((dx * dx) + (dy * dy) + (dz * dz));

	// �������̉�]����ݒ�
	m_rot = D3DXToRadian(90);

	// �����_�̍Đݒ�
	m_posAt.x = m_posEye.x + m_distance.x * cosf(m_rot);
	m_posAt.y = 0.0f;
	m_posAt.z = m_posEye.z + m_distance.z * sinf(m_rot);

	// �r���[�s��𐶐�
	D3DXMatrixLookAtLH(&m_mtxView, &m_posEye, &m_posAt, &m_vecUp);

	// �f�o�C�X�̃r���[�ϊ��s���ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �v���W�F�N�V�����}�g���N�X�̐���
	D3DXMatrixPerspectiveFovLH(&m_mtxProj,							// �p�[�X�y�N�e�B�u�ϊ�
							   D3DX_PI * 0.3333f,					// ����p
							   (float)SCREEN_WIDTH / SCREEN_HEIGHT,	// �A�X�y�N�g��
							   fNear,								// near
							   fFar);								// far

	// �f�o�C�X�Ƀv���W�F�N�V�����ϊ��s���ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProj);


	D3DXQuaternionIdentity(&m_quaternion);
}


//-----------------------------------------------------------------------------
//	�I��
//-----------------------------------------------------------------------------
void Camera::Uninit(void)
{
}


//-----------------------------------------------------------------------------
//	�X�V
//-----------------------------------------------------------------------------
void Camera::Update(void)
{
	// �r���[�s����X�V
	D3DXMatrixLookAtLH(&m_mtxView, &m_posEye, &m_posAt, &m_vecUp);

	// �s����f�o�C�X�ɐݒ�
	Renderer::GetDevice()->SetTransform(D3DTS_VIEW, &m_mtxView);

}


//=============================================================================
// ����
// �ړ��i�O��j
void Camera::MovePosEye_Z(float moveZ)
{
	D3DXVECTOR3 vecZ, move;

	// Z�������߂�
	vecZ = m_posAt - m_posEye;

	// �㉺�ɂ͈ړ����Ȃ�
	vecZ.y = 0.f;

	// ���������~����
	D3DXVec3Normalize(&vecZ, &vecZ);

	// �ړ��l�̎Z�o
	move = vecZ * moveZ;

	// ���_�ƒ����_�̈ړ�
	m_posEye += move;
	m_posAt += move;

}


// �ړ��i���E�j
void Camera::MovePosEye_X(float moveX)
{
	D3DXVECTOR3 vecZ, vecX, move;

	// Z�������߂�
	vecZ = m_posAt - m_posEye;

	// X�������߂�
	D3DXVec3Cross(&vecX, &vecZ, &m_vecUp);

	// �㉺�ɂ͈ړ����Ȃ�
	vecX.y = 0.f;

	// ���������~����
	D3DXVec3Normalize(&vecX, &vecX);

	// �ړ��l�̎Z�o
	moveX *= -1;
	move = vecX * moveX;

	// ���_�ƒ����_�̈ړ�
	m_posEye += move;
	m_posAt  += move;

}


// ��]
void Camera::MoveRotEye(float move)
{
	move *= -1;
	m_rot += move;
	m_posAt.x = m_posEye.x + cosf(m_rot) * m_distance.z;
	m_posAt.z = m_posEye.z + sinf(m_rot) * m_distance.z;

}


// ����
void Camera::MoveTurnEye(float move)
{
	float rotXZ_AtoE = atan2f(m_posEye.z - m_posAt.z, m_posEye.x - m_posAt.x);

	m_rot += move;
	rotXZ_AtoE += move;
	m_posEye.x = m_posAt.x + cosf(rotXZ_AtoE) * m_distance.z;
	m_posEye.z = m_posAt.z + sinf(rotXZ_AtoE) * m_distance.z;

}


//=============================================================================
// �ݒ�
// ���_
void Camera::SetPosEye(D3DXVECTOR3 posEye)
{
	D3DXVECTOR3 move = posEye - m_posEye;

	m_posEye += move;
	m_posAt += move;
}

// �����_
D3DXVECTOR3 Camera::SetPosAt(D3DXVECTOR3 posAt)
{
	D3DXVECTOR3 move = posAt - m_posAt;

	m_posEye += move;
	m_posAt += move;

	return move;
}

// �����
void Camera::SetVecUp(D3DXVECTOR3 vecUp)
{
	m_vecUp = vecUp;
}



