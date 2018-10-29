//*****************************************************************************
//
//		�^�C�}�[
//													Author : Yusuke Seki
//*****************************************************************************
#include "timer.h"
#include "renderer.h"
#include "Object2D.h"
#include "texture.h"


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Timer::Timer()
{
	m_pMinute = m_pColon = m_pSecondLeft  = m_pSecondRight = nullptr;
	m_cntFrame   = m_numMinutes = m_numSeconds = 0;
	m_bStop = true;

}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
Timer::~Timer()
{
}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
Timer* Timer::Create(const D3DXVECTOR3& posLeftEdge, const D3DXVECTOR3& sizeAll)
{
	// ���̂̐���
	Timer* pTimer = new Timer;

	// ���̂̏�����
	pTimer->Init(posLeftEdge, sizeAll);

	// �������ꂽ�^�C�}�[�̃|�C���^��Ԃ�
	return pTimer;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void Timer::Init(const D3DXVECTOR3& posLeftEdge, const D3DXVECTOR3& sizeAll)
{
	D3DXVECTOR3 posBuf1, posBuf2, posBuf3, posBuf4;

	// ���W���Z�o
	posBuf1 = D3DXVECTOR3(posLeftEdge.x + sizeAll.x * 0.15f, posLeftEdge.y, 0.f);
	posBuf2 = D3DXVECTOR3(posLeftEdge.x + sizeAll.x * 0.35f, posLeftEdge.y, 0.f);
	posBuf3 = D3DXVECTOR3(posLeftEdge.x + sizeAll.x * 0.55f, posLeftEdge.y, 0.f);
	posBuf4 = D3DXVECTOR3(posLeftEdge.x + sizeAll.x * 0.85f, posLeftEdge.y, 0.f);

	// ���̂𐶐�
	m_pMinute      = Object2D::Create(posBuf1, D3DXVECTOR3(sizeAll.x * 0.32f, sizeAll.y, 0.f));
	m_pColon       = Object2D::Create(posBuf2, D3DXVECTOR3(sizeAll.x * 0.04f, sizeAll.y, 0.f));
	m_pSecondLeft  = Object2D::Create(posBuf3, D3DXVECTOR3(sizeAll.x * 0.32f, sizeAll.y, 0.f));
	m_pSecondRight = Object2D::Create(posBuf4, D3DXVECTOR3(sizeAll.x * 0.32f, sizeAll.y, 0.f));

	// UV�l�̐ݒ�
	m_pMinute     ->SetUV_Size(D3DXVECTOR2(0.1f, 1.f));
	m_pColon      ->SetUV_Size(D3DXVECTOR2(1.0f, 1.f));
	m_pSecondLeft ->SetUV_Size(D3DXVECTOR2(0.1f, 1.f));
	m_pSecondRight->SetUV_Size(D3DXVECTOR2(0.1f, 1.f));

	
	// �c�莞�Ԃƃt���[���J�E���^�[������
	m_cntFrame = m_numMinutes = m_numSeconds = 0;

	
	// �^�C�}�[�����ꎞ��~
	m_bStop = true;
}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void Timer::Uninit(void)
{
}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void Timer::Update(void)
{
	// �^�C�}�[�~�܂��Ă�H
	if (m_bStop) { // �~�܂��Ă�
		// �^�C�}�[�𓮂����Ȃ��ŏI��
		return;
	}


	// �J�E���^�[����
	m_cntFrame++;

	// �J�E���^�[��60�������H
	if (m_cntFrame == 60) { // �����
		// �J�E���^�[��0��
		m_cntFrame = 0;

		// �b�������炷
		m_numSeconds--;

		// �b�������̐��ɂȂ��Ă���H
		if (m_numSeconds < 0) { // �Ȃ��Ă���
			// ���������炷
			m_numMinutes--;

			// �b����59�b��
			m_numSeconds = 59;
		}
	}


	// ���ƕb��2���ڂ�1���ڂ����ꂼ��؂���
	int minute, second1, second2;
	minute  = m_numMinutes % 10;
	second1 = m_numSeconds / 10;
	second2 = m_numSeconds % 10;

	// UV�l�̐ݒ�
	m_pMinute     ->SetUV_StartPoint(D3DXVECTOR2(minute  * 0.1f, 0.f));
	m_pSecondLeft ->SetUV_StartPoint(D3DXVECTOR2(second1 * 0.1f, 0.f));
	m_pSecondRight->SetUV_StartPoint(D3DXVECTOR2(second2 * 0.1f, 0.f));


	// �c�莞�Ԃ͎c���Ă�H
	if (m_numMinutes == 0 && m_numSeconds == 0) { // �c���ĂȂ�
		// ����ȏ�^�C�}�[��i�߂Ȃ�
		m_bStop = true;
	}


}


//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void Timer::Draw(void)
{
	// ��
	m_pMinute->Draw();

	// �F
	m_pColon->Draw();

	// �b
	m_pSecondLeft->Draw();
	m_pSecondRight->Draw();

}


//-----------------------------------------------------------------------------
//	true�Ŏc�莞�Ԃ��O
//-----------------------------------------------------------------------------
bool Timer::TimeUp()
{
	// �c�莞�Ԃ͎c���Ă�H
	if (m_numMinutes == 0 && m_numSeconds == 0) { // �c���ĂȂ�
		// ���Ԑ؂�ł�
		return true;
	}

	// �܂����Ԃ͎c���Ă܂�
	return false;
}


//-----------------------------------------------------------------------------
//	�^�C�}�[��i�߂�
//-----------------------------------------------------------------------------
void Timer::StartTimer()
{
	// �c�莞�Ԃ͎c���Ă�H
	if (m_numMinutes == 0 && m_numSeconds == 0) { // �c���ĂȂ�
												  // �^�C�}�[��i�߂��ɕԂ�
		return;
	}

	// �^�C�}�[����
	m_bStop = false;
}


//-----------------------------------------------------------------------------
//	�^�C�}�[���~�߂�
//-----------------------------------------------------------------------------
void Timer::StopTimer()
{
	// �^�C�}�[�~�܂�
	m_bStop = true;
}


//-----------------------------------------------------------------------------
// �^�C�}�[��i�߂� / �~�߂�
//-----------------------------------------------------------------------------
void Timer::SwitchTimer()
{
	// �~�܂��Ă��瓮����
	if (m_bStop) {
		// �c�莞�Ԃ͎c���Ă�H
		if (m_numMinutes == 0 && m_numSeconds == 0) { // �c���ĂȂ�
													  // �^�C�}�[��i�߂��ɕԂ�
			return;
		}

		// �^�C�}�[����
		m_bStop = false;

	}
	// �����Ă���~�߂�
	else {
		// �^�C�}�[�~�܂�
		m_bStop = true;
	}
}



//=============================================================================
// �ݒ�
// ����
void Timer::SetTimer(unsigned int minutes, unsigned int seconds)
{
	int minute, second1, second2;


	// �b����ݒ�
	m_numSeconds = seconds % 60;

	// ������b���̗]�肾�����₷
	minutes += seconds / 60;

	// �����͏���𒴂��Ă�H
	if (minutes >= 10) {
		// ����ɐݒ肷��
		minutes = 9;
	}

	// �����̐ݒ�
	m_numMinutes = minutes;


	// ���ƕb��2���ڂ�1���ڂ����ꂼ��؂���
	minute  = m_numMinutes % 10;
	second1 = m_numSeconds / 10;
	second2 = m_numSeconds % 10;

	// UV�l�̐ݒ�
	m_pMinute->SetUV_StartPoint(D3DXVECTOR2(minute  * 0.1f, 0.f));
	m_pSecondLeft->SetUV_StartPoint(D3DXVECTOR2(second1 * 0.1f, 0.f));
	m_pSecondRight->SetUV_StartPoint(D3DXVECTOR2(second2 * 0.1f, 0.f));
}


// �����̃e�N�X�`��
void Timer::SetTexture_Number(const LPDIRECT3DTEXTURE9 pTexture)
{
	m_pMinute->SetTexture(pTexture);
	m_pSecondLeft->SetTexture(pTexture);
	m_pSecondRight->SetTexture(pTexture);
	
}


// �R�����̃e�N�X�`��
void Timer::SetTexture_Colon(const LPDIRECT3DTEXTURE9 pTexture)
{
	m_pColon->SetTexture(pTexture);

}


