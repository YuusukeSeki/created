//*****************************************************************************
//	
//		�G�t�F�N�g�i�r���{�[�h�j
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _EFFECTBILLBOARD_H_
#define _EFFECTBILLBOARD_H_

#include "main.h"
#include "Effect3D.h"

class Camera;


class EffectBillboard : public Effect3D
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	EffectBillboard() {}
	EffectBillboard(EffectManager::TYPE type);
	virtual ~EffectBillboard();

	
	//----- ��{�I�Ȋ֐� -----
	static EffectBillboard* Create(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera);
	virtual void Init(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);


	//----- �������� -----


	//----- �ݒ菈�� -----
	static void SetEffect(D3DXVECTOR3& position, D3DXVECTOR3& vecZ, Camera* pCamera, Effect3D::TYPE effectType);	// �G�t�F�N�g�̔���
	void SetCamera(Camera& pCamera) { m_pCamera = &pCamera; }											// �J�����̐ݒ�


	//----- �f�[�^��Ԃ����� -----
	Camera* GetCamera() { return m_pCamera; }	// �����Ă���J�����̃|�C���^��Ԃ�

	
protected:


private:
	//----- �֐� -----
	void UpdateWorldMatrix();	// ���[���h�}�g���N�X�̍X�V

	//----- �f�[�^ -----
	Camera* m_pCamera; // �J����

};

#endif

