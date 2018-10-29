//*****************************************************************************
//
//		�g��
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _FRAMEBORDER_H_
#define _FRAMEBORDER_H_

#include "main.h"
#include "Object2D.h"

class Timer;
class TeamGaugeManager;
class TeamLevel;


class FrameBorder : public Object2D
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	FrameBorder() {}
	FrameBorder(Object::TYPE type);
	~FrameBorder();

	//----- ��{�I�Ȋ֐� -----
	static FrameBorder* Create(D3DXVECTOR3& position, D3DXVECTOR3& size);
	void Init(D3DXVECTOR3& position, D3DXVECTOR3& size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Release(void) { delete this; }

	//----- �������� -----
	//void MovePosition(D3DXVECTOR3& movePosition);			// ���W�̈ړ�
	//void MoveSize(D3DXVECTOR3& moveSize);					// �傫���̑���
	//void MoveRotate(float moveRotate);						// ��]���̑���
	//void MoveColor(int r, int g, int b, int a);				// �F�̑���
	//void MoveUV_StartPoint(D3DXVECTOR2& moveUV_StartPoint);	// UV�J�n�_�̑���
	//void MoveUV_Size(D3DXVECTOR2& moveUV_Size);				// UV�傫���̑���

	////----- �ݒ菈�� -----
	//void SetPosition(D3DXVECTOR3& position);			// ���W�̐ݒ�
	//void SetSize(D3DXVECTOR3& size);					// �傫���̐ݒ�
	//void SetRotate(float rotate);						// ��]���̐ݒ�
	//void SetColor(unsigned int rgba);					// �F�̐ݒ�
	//void SetUV_StartPoint(D3DXVECTOR2& UV_StartPoint);	// UV�J�n�_�̐ݒ�
	//void SetUV_Size(D3DXVECTOR2& UV_Size);				// UV�傫���̐ݒ�

	//----- �f�[�^��Ԃ����� -----
	Timer*            GetTimer()            { return m_pTimer; }			// "�q"�̃^�C�}�[��Ԃ�
	TeamGaugeManager* GetTeamGaugeManager() { return m_pTeamGaugeManager; }	// "�q"�̃`�[���Q�[�W�}�l�[�W���[��Ԃ�
	TeamLevel*        GetTeamLevel()        { return m_pTeamLevel; }		// "�q"�̃`�[�����x����Ԃ�

private:
	//----- �f�[�^ -----
	Timer*            m_pTimer;				// �y�q�z�^�C�}�[
	TeamGaugeManager* m_pTeamGaugeManager;	// �y�q�z�`�[���Q�[�W
	TeamLevel*        m_pTeamLevel;			// �y�q�z�`�[�����x��


};

#endif
