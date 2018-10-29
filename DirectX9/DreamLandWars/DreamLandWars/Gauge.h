//*****************************************************************************
//
//		�Q�[�W
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"

class ObjectBillboard;
class Camera;


class Gauge
{
public:
	Gauge();
	~Gauge();

	// ��������
	// position : ���W
	// size : �傫��
	static Gauge* Create(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera);

	// ����������
	virtual void Init(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera);

	// �I������
	virtual void Uninit(void);

	// �X�V����
	virtual void Update(void);

	// �������
	void Release(void);

	// �Q�[�W�ʂ̑�������
	virtual void MoveValue(float moveLife);

	// ���݂̃Q�[�W�ʂ̎擾
	// �Ԃ�l �F ���݂̃Q�[�W��
	float GetValue(void);

	// �`��̗L���X�C�b�`
	void SetDraw(bool bDraw);
	

private:
	bool _bDraw;					// �`�悷��H
	float _value;					// ���݂̃Q�[�W��
	float _initWidth;				// �Q�[�W�̏�����

	ObjectBillboard* _pGauge;		// �Q�[�W
	ObjectBillboard* _pBackGround;	// �Q�[�W�̔w�i

};

#endif
