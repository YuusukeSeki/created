//*****************************************************************************
//
//		�X�R�A
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"


class Object2D;

class Score
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	Score();
	~Score() {}

	//----- ��{�I�Ȋ֐� -----
	static Score* Create(const D3DXVECTOR3& centerPosition, const D3DXVECTOR3& sizeAll, unsigned int numDigit);
	void Init(const D3DXVECTOR3& centerPosition, const D3DXVECTOR3& sizeAll, unsigned int numDigit);
	void Uninit(void) {}
	void Update(void);
	void Draw(void);
	void Release(void) { delete this; }

	//----- �������� -----
	void MoveScore(int score);	// �X�R�A�̑���

	//----- �ݒ菈�� -----
	void SetScore(int score);							// �X�R�A�̐ݒ�
	void SetTexture(const LPDIRECT3DTEXTURE9 pTexture);	// �e�N�X�`���̐ݒ�

	//----- �f�[�^��Ԃ����� -----
	int GetScore() { return m_numScore + (int)m_moveScore; }	// ���݂̃X�R�A��Ԃ�


private:
	//----- �萔 -----
	static const double CONFFICIENT;	// ��x�ɑ����鑝����


	//----- �f�[�^ -----
	         D3DXVECTOR3  m_centerPosition;	// ����S�̂̒��S�_
	         D3DXVECTOR3  m_sizeAll;		// ����S�̂̑傫��
	         Object2D*    m_pDigit;			// �����|���S��
	unsigned int          m_numDigit;		// ����
	         int          m_maxScore;		// �X�R�A�̍ő�l
	         int          m_numScore;		// �X�R�A�̕\���l
	         double       m_moveScore;		// �X�R�A�̑����l

};

#endif
