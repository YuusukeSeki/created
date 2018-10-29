//*****************************************************************************
//
//		�J����
//													Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"


class Camera
{
public:
	// �R���X�g���N�^ / �f�X�g���N�^
	Camera();
	~Camera();

	// ��{�I�Ȋ֐�
	static Camera* Create(D3DXVECTOR3 posEye, D3DXVECTOR3 posAt, D3DXVECTOR3 vecUp, float fNear, float fFar);
	void Release(void);
	void Init(D3DXVECTOR3 posEye, D3DXVECTOR3 posAt, D3DXVECTOR3 vecUp, float fNear, float fFar);
	void Uninit(void);
	void Update(void);

	// ����
	void MovePosEye_Z(float moveZ);  // �ړ��i�O��j
	void MovePosEye_X(float moveX);  // �ړ��i���E�j
	void MoveRotEye  (float move);	 // ��]
	void MoveTurnEye (float move);	 // ����

	// �ݒ�
	//void SetPosEye(D3DXVECTOR3 posEye); // ���_
	//void SetPosAt(D3DXVECTOR3 posAt);   // �����_
	//void SetVecUp(D3DXVECTOR3 vecUp);   // �����
	void SetPosEye(D3DXVECTOR3 posEye);      // ���_
	D3DXVECTOR3 SetPosAt(D3DXVECTOR3 posAt); // �����_
	void SetVecUp(D3DXVECTOR3 vecUp);        // �����

	// �擾
	D3DXMATRIX GetMtxView() { return m_mtxView; }
	D3DXMATRIX GetMtxProj() { return m_mtxProj; }
	float GetRot() { return m_rot; }
	D3DXVECTOR3 GetVecZ() {
		D3DXVECTOR3 vecZ = m_posAt - m_posEye;
		vecZ.y = 0.f;

		return *D3DXVec3Normalize(&vecZ, &vecZ);
	}
	D3DXVECTOR3 GetVecX() {
		D3DXVECTOR3 vecZ, vecX;
		vecZ = m_posAt - m_posEye;
		D3DXVec3Cross(&vecX, &m_vecUp, &vecZ);
		vecX.y = 0.f;

		return *D3DXVec3Normalize(&vecX, &vecX);
	}
	D3DXVECTOR3 GetVecUp() { return m_vecUp; }
	D3DXVECTOR3 GetVecZ_UnNormal() { return m_posAt - m_posEye; }
	D3DXVECTOR3 GetPosEye() { return m_posEye; }
	D3DXVECTOR3 GetPosAt() { return m_posAt; }

	const D3DXMATRIX* GetMtxView() const { return &m_mtxView; }


protected:


private:
	// �ϐ�
	D3DXMATRIX  m_mtxView;	// �r���[�s��
	D3DXMATRIX  m_mtxProj;	// �v���W�F�N�V�����s��
	D3DXMATRIX  m_mtxZRot;	// Z����]�s��
	D3DXMATRIX  m_mtxTrans;	// �ړ��s��
	D3DXVECTOR3 m_posEye;	// ���_
	D3DXVECTOR3 m_posAt;	// �����_
	D3DXVECTOR3 m_vecUp;	// �����
	float       m_rot;      // ��]��
	D3DXVECTOR3 m_distance; // �����_���王�_�܂ł̋���

	D3DXQUATERNION m_quaternion;


};

#endif
