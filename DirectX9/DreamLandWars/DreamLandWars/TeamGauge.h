//*****************************************************************************
//
//		�`�[���Q�[�W
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _TEAMGAUGE_H_
#define _TEAMGAUGE_H_

#include "main.h"
#include "Object2D.h"



class TeamGauge : public Object2D
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	TeamGauge() {}
	TeamGauge(Object::TYPE type);
	~TeamGauge();

	//----- ��{�I�Ȋ֐� -----
	static TeamGauge* Create(D3DXVECTOR3& position, D3DXVECTOR3& size, Object::GROUP group);
	void Init(D3DXVECTOR3& position, D3DXVECTOR3& size, Object::GROUP group);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//----- �������� -----
	void MoveLife(float moveLife);	// �Q�[�W�ʂ̑�������

	//----- �ݒ菈�� -----

	//----- �f�[�^��Ԃ����� -----
	float GetCurrentGauge() { return m_life; }	// ���݂̃Q�[�W�ʂ�Ԃ�
	bool Lose();


private:
	float m_life;		// ���݂̃Q�[�W��
	float m_initWidth;	// �|���S���̏�����

};

#endif
