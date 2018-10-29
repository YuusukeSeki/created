//*****************************************************************************
//	
//		�I�u�W�F�N�g���N���X�i���X�g�\���j
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _OBJECT_LIST_H_
#define _OBJECT_LIST_H_

#include "main.h"

#define _WLW		// �����_�[�p�̃t���[�����[�N�ɕύX�i�R�����g�A�E�g�Ŗ����j



class Object
{
public:
	//----- �񋓌^�̒�` -----
	enum TYPE { // ��ށi�`�揇�����݁j
		TYPE_COMMANDER,					// �w�����i���W�̂݁j
		TYPE_MODEL,						// �����f��
		TYPE_MODEL_PLAYER,				// �v���C���[
		TYPE_MODEL_SOLDIER,				// ���m
		TYPE_MODEL_CASTLE,				// ��
		TYPE_MODEL_TOWER,				// ��
		TYPE_MODEL_SKYDOME,				// �X�J�C�h�[��
		TYPE_3D_FIELD,					// �t�B�[���h
		TYPE_3D_SKYBOX,					// �X�J�C�{�b�N�X
		TYPE_3D,						// ��3D�|���S��
		TYPE_3D_CUBE,					// �L���[�u
		TYPE_3D_WALL,					// ��
		TYPE_3D_DRAWRANGE,				// DS�˒��͈�
		TYPE_3D_DRAWLINE,				// �`���
		TYPE_3D_SOLDIERBULLET,			// ���m�e
		TYPE_3D_STRAIGHTSHOT,			// �X�g���[�g�V���b�g
		TYPE_3D_DRAWSHOT,				// �h���[�V���b�g
		TYPE_3D_BILLBOARD_LIFEGAUGE,	// �̗̓Q�[�W
		TYPE_3D_BILLBOARD_ICON,			// �A�C�R��
		TYPE_3D_BILLBOARD_HOLD,			// "HOLD"
		TYPE_3D_BILLBOARD,				// �r���{�[�h
		TYPE_3D_BULLET,					// �o���b�g�i3D�j
		TYPE_3D_BILLBOARD_BULLET,		// �o���b�g�i�r���{�[�h�j
		TYPE_3D_BILLBOARD_EFFECT,		// �G�t�F�N�g�i�r���{�[�h�j
		TYPE_3D_GAMETITLE,				// �Q�[���^�C�g��
		TYPE_3D_TOUCHSCREEN,			// �^�b�`�X�N���[��
		TYPE_2D,						// ��2D�|���S��
		TYPE_2D_FRAMEBORDER,			// �g��

		TYPE_MAX,	// �� ��ނ̍ő吔
	};


public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	Object(){}
	Object(Object::TYPE type);
	virtual ~Object(){}

	
	//----- ��{�I�Ȋ֐� -----
	virtual void Init(void) {}
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	        void Release(void);
	static  void UpdateAll();
	static  void DrawAll();
	static  void ReleaseAll();


	//----- �������� -----
	virtual void MovePosition(D3DXVECTOR3& movePosition) { _position += movePosition; }	// ���W���ړ�����


	//----- �ݒ菈�� -----
	virtual void SetPosition(D3DXVECTOR3& position) { _position = position; }	// ���W��ݒ肷��
	        void SetNextPointer(Object* pNext)		{ m_pNext = pNext; }		// ���̃|�C���^�[��ݒ肷��
	        void SetPrevPointer(Object* pPrev)		{ m_pPrev = pPrev; }		// �O�̃|�C���^�[��ݒ肷��


	//----- �f�[�^��Ԃ����� -----
	static Object*      GetLDATA_HEAD(Object::TYPE type) { return m_pHEAD[type]; }	// ���̂�Ԃ�
	       Object*      GetNextPointer()                 { return m_pNext; }		// �����̎��̃|�C���^��Ԃ�
	       Object*      GetPrevPointer()                 { return m_pPrev; }		// �����̑O�̃|�C���^��Ԃ�
	       D3DXVECTOR3& GetPosition()                    { return _position; }		// ���W��Ԃ�
		   Object::TYPE GetType()						 { return m_type; }			// ��ނ�Ԃ�

protected:
	//----- �f�[�^ -----
	D3DXVECTOR3 _position;		// ���W
	Object::TYPE m_type;		// ���

private:
	//----- �Ǘ��p�f�[�^ -----
	static Object* m_pHEAD[Object::TYPE_MAX];	// ���X�g�f�[�^�̐擪
	static Object* m_pTAIL[Object::TYPE_MAX];	// ���X�g�f�[�^�̍Ō�
	       Object* m_pNext;						// ���̃I�u�W�F�N�g
	       Object* m_pPrev;						// �O�̃I�u�W�F�N�g


#ifdef _WLW
public:
	//----- �񋓌^�̒�` -----
	enum GROUP { // �w�c
		GROUP_NONE, // ������
		GROUP_A,	// A
		GROUP_B,	// B
	};

	//----- �ݒ菈�� -----
	void SetGroup(Object::GROUP group) { m_group = group; }	// WLW�w�c�ݒ�

	//----- �f�[�^��Ԃ����� -----
	Object::GROUP GetGroup() { return m_group; }	// �����w�c��Ԃ�

protected:
	//----- �f�[�^ -----
	Object::GROUP m_group;	// �w�c

#endif

};

#endif

