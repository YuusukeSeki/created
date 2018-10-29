//*****************************************************************************
//
//		�`���
//												Autohr	:	Yusuke Seki
//*****************************************************************************
#ifndef _DRAWLINE_H_
#define _DRAWLINE_H_

#include "main.h"
#include "Object3D.h"

class Player;


class DrawLine : public Object3D
{
public:
	//----- �񋓌^�̒�` -----
	enum TYPE{	// �_�̎��
		TYPE_START,		// �n�_
		TYPE_VIA,		// �o�R�_
	};


public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	DrawLine() {}
	DrawLine(Object::TYPE type);
	virtual ~DrawLine();


	//----- ��{�I�Ȋ֐� -----
	static DrawLine* Create(D3DXVECTOR3& position);
	void Init(D3DXVECTOR3& position);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	//----- �ݒ菈�� -----
	static DrawLine* SetStartLine(D3DXVECTOR3& position, Player& player);		// �n�_�̐ݒ�
	static void SetViaPoint(D3DXVECTOR3& position, DrawLine* pStartPoint);		// �o�R�_�̐ݒ�
	static void SetDrawShot(DrawLine* pStartPoint);								// DS�̔���
	static void ClearParameter_List(DrawLine* pStartPoint);						// �f�[�^�̃N���A�F�q�����Ă�̈�S��
	       void ClearParameter();												// �f�[�^�̃N���A�F��


	//-----�@�f�[�^��Ԃ����� -----
	DrawLine::TYPE GetType_DrawLine()        { return m_type; }			// ��ނ�Ԃ�
	DrawLine*      GetNextPointer_DrawLine() { return m_pNext; }		// ���̓_��Ԃ�
	bool           GetInstance()             { return m_bInstance; }	// �g�p�����ǂ�����Ԃ��Ftrue �Ŏg�p��
	Player*        GetPlayer_DrawLine()      { return m_pPlayer; }		// �e�v���C���[��Ԃ�

private:
	//----- �ݒ菈�� -----
	void SetStartLine_private(D3DXVECTOR3& position, Player& player);			// �n�_�̐ݒ�
	void SetViaPoint_private(D3DXVECTOR3& position, DrawLine* pStartPoint);		// �o�R�_�̐ݒ�

	//----- �f�[�^ -----
	static const float DRAWLINE_HEIGHT;	// �`����|���S���̍���

	DrawLine::TYPE m_type;		// ���
	DrawLine*      m_pNext;		// ���̓_
	DrawLine*      m_pTail;		// �����̓_
	bool           m_bInstance;	// �g�p���t���O
	Player*        m_pPlayer;	// �e�v���C���[

};

#endif
