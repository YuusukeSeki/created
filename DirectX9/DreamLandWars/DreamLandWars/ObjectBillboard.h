#pragma once
//*****************************************************************************
//
//		�r���{�[�h�i���X�g�\���j
//												Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _OBJECTBILLBOARD_H_
#define _OBJECTBILLBOARD_H_

#include "main.h"
#include "Object3D_Quaternion.h"

class Camera;


class ObjectBillboard : public Object3D_Quaternion
{
public:
	ObjectBillboard() {}
	ObjectBillboard(Object::TYPE type);
	virtual ~ObjectBillboard();

	static ObjectBillboard* Create(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera);
	virtual void Init(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera);
	virtual void Uninit(void);
	virtual void Update(void) {}
	virtual void Draw(void);

	// �J�����̐ݒ�
	void SetCamera(Camera& pCamera) { m_pCamera = &pCamera; }

	// �����Ă���J�����̃|�C���^��Ԃ�
	Camera* GetCamera() { return m_pCamera; }

private:
	// ���[���h�}�g���N�X�̍X�V
	void UpdateWorldMatrix();

	Camera* m_pCamera;	// �J����

};

#endif

