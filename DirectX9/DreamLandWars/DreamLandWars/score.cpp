//*****************************************************************************
//
//		�X�R�A
//													Author : Yusuke Seki
//*****************************************************************************
#include "score.h"
#include "renderer.h"
#include "Object2D.h"
#include "texture.h"


//----- �ÓI�ϐ��̏����� ------
const double Score::CONFFICIENT = 0.5; // ��x�ɑ����鑝����



//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Score::Score()
{
	m_centerPosition = D3DXVECTOR3(0, 0, 0);
	m_sizeAll        = D3DXVECTOR3(0, 0, 0);
	m_pDigit         = nullptr;
	m_numDigit       = 0;
	m_maxScore       = 0;
	m_numScore       = 0;
	m_moveScore      = 0;

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
Score* Score::Create(const D3DXVECTOR3& posLeftEdge, const D3DXVECTOR3& sizeAll, unsigned int numDigit)
{
	// ���G���[�`�F�b�N�F�������O�ȉ��Ȃ琶�������ɏI������
	if (numDigit <= 0) {
		_MSGERROR("Failed Create Score!!\nCannot Read Digit!!", "Score* Score::Create(const D3DXVECTOR3& posLeftEdge, const D3DXVECTOR3& sizeAll, unsigned int numDigit)");
		return nullptr;
	}

	// ���̂̐���
	Score* pScore = new Score;

	// ���̂̏�����
	pScore->Init(posLeftEdge, sizeAll, numDigit);

	// �������ꂽ�^�C�}�[�̃|�C���^��Ԃ�
	return pScore;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void Score::Init(const D3DXVECTOR3& centerPosition, const D3DXVECTOR3& sizeAll, unsigned int numDigit)
{
	// ����S�̂̒��S�_�̎擾
	m_centerPosition = centerPosition;

	// ����S�̂̑傫���̎擾
	m_sizeAll = sizeAll;

	// �����̎擾
	m_numDigit = numDigit;


	// �������̃|���S���𐶐�
	m_pDigit = Object2D::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
	Object2D* pDigit = m_pDigit;
	for (int i = 1; i < (int)m_numDigit; i++) {
		Object2D::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
	}



	// �������������|���S���̃p�����[�^��ݒ肷��
	{
		// ���ꂼ��̐����|���S���̑傫���ƒ��S�_���Z�o
		float       rightEdge = m_centerPosition.x + m_sizeAll.x * 0.5f;						// ����̉E�[�̍��W
		D3DXVECTOR3 size      = D3DXVECTOR3(m_sizeAll.x / m_numDigit, m_sizeAll.y, 0);			// �T�C�Y
		D3DXVECTOR3 cPos      = D3DXVECTOR3(rightEdge - size.x * 0.5f , m_centerPosition.y, 0);	// ���S�_

		// �ݒ肷��
		for (int i = 0; i < (int)m_numDigit; i++) {
			pDigit->Init(cPos, size);					// ���S�_�ƃT�C�Y
			pDigit->SetUV_Size(D3DXVECTOR2(0.1f, 1.f));	// UV�T�C�Y

			// ���̃|���S���̒��S�_�Z�o
			cPos.x -= size.x;

			// ���̃|���S����
			pDigit = (Object2D*)pDigit->GetNextPointer();
		}

	}


	// �\���l�Ƒ����l�̏�����
	m_numScore  = 0;
	m_moveScore = 0;

	// �X�R�A�̏�����Z�o
	int digit  = 9;
	m_maxScore = 0;
	for (int i = 0; i < (int)m_numDigit; i++) {
		m_maxScore += digit;
		digit *= 10;
	}

}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void Score::Update(void)
{
	// �����l���O�`�P�H
	if (m_moveScore * CONFFICIENT > 0 && m_moveScore * CONFFICIENT < 1.f) {
		m_numScore += 1;
		m_moveScore = 0;
	}
	// �����l���O�`�P�H
	else if (m_moveScore * CONFFICIENT < 0 && m_moveScore * CONFFICIENT > -1.f){
		m_numScore -= 1;
		m_moveScore = 0;
	}
	// �����l�𑫂�
	else {
		m_numScore  += (int)(m_moveScore * CONFFICIENT);
		m_moveScore -= (int)(m_moveScore * CONFFICIENT);
	}



	//----- UV�l�̐ݒ� -----
	int scoreAll, number;
	scoreAll = m_numScore;

	// ��������
	Object2D* pDigit = m_pDigit;
	for (int i = 0; i < (int)m_numDigit; i++) {
		// ���l�̎Z�o
		number = scoreAll % 10;

		// ���l��UV�l�ɔ��f
		pDigit->SetUV_StartPoint(D3DXVECTOR2(number * 0.1f, 0.f));

		// �����ꌅ������
		scoreAll /= 10;

		// ���̐����|���S����
		pDigit = (Object2D*)pDigit->GetNextPointer();
	}
	// End...UV�l�̐ݒ�

}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void Score::Draw(void)
{
	// �`��
	Object2D* pDigit = m_pDigit;
	for (int i = 0; i < (int)m_numDigit; i++) {
		pDigit->Draw();
		pDigit = (Object2D*)pDigit->GetNextPointer();
	}
}



//=============================================================================
// ����
// ���_
void Score::MoveScore(int score)
{
	// �܂��͂��̂܂ܑ���
	m_moveScore += score;


	// �X�R�A������𒴂����H
	if (m_numScore + m_moveScore >= m_maxScore) { // ������
		// �����l�������t�܂łɂ���
		m_moveScore = m_maxScore - m_numScore;

	}
	// �X�R�A�������𒴂����H
	else if(m_numScore + m_moveScore < 0){ // ������
		// �����l��������t�܂łɂ���
		m_moveScore = 0 - m_numScore;

	}

}


//=============================================================================
// �ݒ�
// ���_
void Score::SetScore(int score)
{
	// �܂��͂��̂܂ܐݒ肷��
	m_moveScore = score - m_numScore;


	// �X�R�A������𒴂����H
	if (m_numScore + m_moveScore >= m_maxScore) { // ������
		// �����l�������t�܂łɂ���
		m_moveScore = m_maxScore - m_numScore;

	}
	// �X�R�A�������𒴂����H
	else if (m_numScore + m_moveScore < 0) { // ������
		// �����l��������t�܂łɂ���
		m_moveScore = 0 - m_numScore;

	}

}


// �e�N�X�`��
void Score::SetTexture(const LPDIRECT3DTEXTURE9 pTexture) 
{
	// �e�N�X�`���̐ݒ�
	Object2D* pDigit = m_pDigit;
	for (int i = 0; i < (int)m_numDigit; i++) {
		pDigit->SetTexture(pTexture);
		pDigit = (Object2D*)pDigit->GetNextPointer();
	}

}

