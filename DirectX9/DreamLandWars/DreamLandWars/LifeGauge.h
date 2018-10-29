//*****************************************************************************
//
//		�̗̓Q�[�W�i���_�j
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _BASEPOINT_LIFEGAUGE_H_
#define _BASEPOINT_LIFEGAUGE_H_

#include "main.h"
#include "ObjectBillboard.h"
#include "ObjectModel.h"

class Camera;


class LifeGauge : public ObjectBillboard
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	LifeGauge();
	~LifeGauge();

	//----- ��{�I�Ȋ֐� -----
	static LifeGauge* Create(ObjectModel* pObjModel, Camera* pCamera);
	void Init(ObjectModel* pObjModel, Camera* pCamera);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//----- �������� -----
	void MoveLife(float moveLife);	// �Q�[�W�ʂ̑�������

	//----- �ݒ菈�� -----

	//----- �f�[�^��Ԃ����� -----


private:
	//----- �f�[�^ -----
	ObjectModel* m_pParent;	// �e���f��

	float m_initLife;		// �����̗�
	float m_initWidth;		// �|���S���̏�����

	ObjectBillboard* m_pBG;	// �w�i

};

#endif
