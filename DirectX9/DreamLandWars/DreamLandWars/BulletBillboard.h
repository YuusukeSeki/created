//*****************************************************************************
//	
//		�o���b�g�i�r���{�[�h�j
//													Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _BULLETBILLBOARD_H_
#define _BULLETBILLBOARD_H_

#include "main.h"
#include "Bullet3D.h"

class Camera;


class BulletBillboard : public Bullet3D
{
public:
	// �R���X�g���N�^ / �f�X�g���N�^
	BulletBillboard();
	BulletBillboard(Object::TYPE type);
	virtual ~BulletBillboard();

	// ��{�I�Ȋ֐�
	static BulletBillboard* Create(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera);
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


	//----- �f�[�^ -----
	Camera* m_pCamera;	// �J����

};


#endif

