//*****************************************************************************
//
//		�^�C�}�[
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"


class Object2D;

class Timer
{
public:
	// �R���X�g���N�^ / �f�X�g���N�^
	Timer();
	~Timer();

	// �֐�
	static Timer* Create(const D3DXVECTOR3& posLeftEdge, const D3DXVECTOR3& size);
	void Init(const D3DXVECTOR3& posLeftEdge, const D3DXVECTOR3& sizeAll);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Release() { delete this; }

	// �t���O�擾
	bool TimeUp();

	// �ݒ�
	void SetTimer(unsigned int minutes, unsigned int seconds);
	void StartTimer();	// �^�C�}�[�𓮂���
	void StopTimer();	// �^�C�}�[���~�߂�
	void SwitchTimer(); // �^�C�}�[�𓮂��� / �~�߂�
	void SetTexture_Number(const LPDIRECT3DTEXTURE9 pTexture);
	void SetTexture_Colon(const LPDIRECT3DTEXTURE9 pTexture);




protected:


private:
	Object2D* m_pMinute;
	Object2D* m_pColon;
	Object2D* m_pSecondLeft;
	Object2D* m_pSecondRight;

	unsigned int m_cntFrame;

	int m_numMinutes;
	int m_numSeconds;

	bool m_bStop;

};

#endif
