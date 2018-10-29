//*****************************************************************************
//	
//		�G�t�F�N�g���N���X�i���X�g�\���j
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _EFFECT_MANAGER_H_
#define _EFFECT_MANAGER_H_

#include "main.h"


class EffectManager
{
public:
	//----- �񋓌^�̒�` -----
	enum TYPE { // ��ށi�`�揇�����݁j
		TYPE_3D,			// ��3D�|���S��
		TYPE_3D_BILLBOARD,	// �r���{�[�h
		TYPE_2D,			// ��2D�|���S��

		TYPE_MAX,	// �� ��ނ̍ő吔
	};


public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	EffectManager() {}
	EffectManager(EffectManager::TYPE type);
	virtual ~EffectManager() {}


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
	        void SetNextPointer(EffectManager* pNext) { m_pNext = pNext; }		// ���̃|�C���^�[��ݒ肷��
	        void SetPrevPointer(EffectManager* pPrev) { m_pPrev = pPrev; }		// �O�̃|�C���^�[��ݒ肷��


	//----- �f�[�^��Ԃ����� -----
	static EffectManager* GetLDATA_HEAD(EffectManager::TYPE type) { return m_pHEAD[type]; }	// ���̂�Ԃ�
	       EffectManager* GetNextPointer()                        { return m_pNext; }		// �����̎��̃|�C���^��Ԃ�
	       EffectManager* GetPrevPointer()                        { return m_pPrev; }		// �����̑O�̃|�C���^��Ԃ�
	       D3DXVECTOR3*   GetPosition()                           { return &_position; }	// ���W��Ԃ�


protected:


private:
	//----- �f�[�^ -----
	D3DXVECTOR3 _position;		// ���W
	EffectManager::TYPE m_type;	// ���

	//----- �Ǘ��p�f�[�^ -----
	static EffectManager* m_pHEAD[EffectManager::TYPE_MAX];	// ���X�g�f�[�^�̐擪
	static EffectManager* m_pTAIL[EffectManager::TYPE_MAX];	// ���X�g�f�[�^�̍Ō�
	       EffectManager* m_pNext;							// ���̃I�u�W�F�N�g
	       EffectManager* m_pPrev;							// �O�̃I�u�W�F�N�g

};

#endif

