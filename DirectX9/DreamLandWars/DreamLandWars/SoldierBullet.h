//*****************************************************************************
//	
//		���m�̒e
//													Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _SOLDIERBULLET_H_
#define _SOLDIERBULLET_H_

#include "main.h"
#include "BulletBillboard.h"

class Camera;
class ObjectModel;


class SoldierBullet : public BulletBillboard
{
public:
	// �R���X�g���N�^ / �f�X�g���N�^
	SoldierBullet();
	virtual ~SoldierBullet();

	// ��{�I�Ȋ֐�
	static SoldierBullet* CreateBuffer();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ���m�e�̓��I��������
	// position : �����ʒu
	// pTarget  : �^�[�Q�b�g
	static void SetBullet(D3DXVECTOR3& position, ObjectModel *pTarget, Camera *pCamera);


private:
	// ���m�e�̐ݒ菈��
	void SetBullet_private(D3DXVECTOR3& position, ObjectModel *pTarget, Camera *pCamera);


	//----- �f�[�^ -----
	static const float bulletDamage_cast;	// �W�I�F�L���X�g�̏ꍇ�̕��m�e�̃_���[�W
	static const float bulletDamage_soldier;	// �W�I�F���m�̏ꍇ�̕��m�e�̃_���[�W

	ObjectModel *m_pTarget;	// �^�[�Q�b�g�̃|�C���^
	int m_cntEraseFrame;	// �����܂ł̎���
	D3DXVECTOR3 m_front;	// �i�ޕ���
	bool m_bTracking;		// �ǔ��t���O

};


#endif

