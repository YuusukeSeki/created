//*****************************************************************************
//
//		�z�[���h
//												Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _HOLD_H_
#define _HOLD_H_

#include "main.h"
#include "ObjectBillboard.h"

class ObjectModel;
class Camera;


class Hold : public ObjectBillboard
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	Hold();
	virtual ~Hold();


	//----- ��{�I�Ȋ֐� -----
	static Hold* Create(ObjectModel* pObjModel, Camera* pCamera);
	virtual void Init(ObjectModel* pObjModel, Camera* pCamera);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//----- �������� -----
	void MovePosition(D3DXVECTOR3& movePosition);

	//----- �ݒ菈�� -----
	// true ��"HOLD"�\��
	void SetDrawHold(bool bDraw) { m_bDraw = bDraw; }

	// 
	void ReleaseThis();

	//----- �f�[�^��Ԃ����� -----


private:
	//----- �f�[�^ -----
	ObjectModel*     m_pParent;				// �e�̃|�C���^
	ObjectBillboard* m_pBackGround;			// �Ə��F�w�i
	ObjectBillboard* m_pLockOn_OutLine;		// �Ə��F�O��
	ObjectBillboard* m_pLockOn_InnerLine;	// �Ə��F����
	ObjectBillboard* m_pLockOn_Hold;		// �Ə��F"HOLD"

	bool m_bDraw;	// true ��"Hold"�\��


};

#endif

