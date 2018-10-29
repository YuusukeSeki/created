//*****************************************************************************
//
//		�t�B�[���h
//													Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"
#include "Object.h"
#include "texture.h"


class Field : public Object	// 3D�|���S��
{
public:
	// �萔
	static const float FIELD_WIDTH_ALL;	 // �S�̃t�B�[���h��
	static const float FIELD_HEIGHT_ALL; // �S�̃t�B�[���h����

	// �R���X�g���N�^ / �f�X�g���N�^
	virtual ~Field();

	// ��{�I�Ȋ֐�
	static	Field*	Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 scl, int numFieldHorizon, int numFieldVertical);
	virtual HRESULT	Init( D3DXVECTOR3 pos , D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 scl, int numFieldHorizon, int numFieldVertical);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	// �ݒ�
	void SetMtxWorld( D3DXMATRIX mtxWorld )	{ m_mtxWorld = mtxWorld; }
	void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }

	// �擾
	const D3DXVECTOR3* GetRotate (void) const { return &m_rot; }
	const D3DXVECTOR3* GetScall (void) const { return &m_scl; }
	float GetHeight(D3DXVECTOR3 pos);
	D3DXVECTOR3& GetSize() { return m_size; }
	D3DXVECTOR3& GetHalfSize() { return m_halfSize; }


private:
	// �R���X�g���N�^ / �f�X�g���N�^
	Field() {}
	//Field(int priority, TYPE type);
	Field(Object::TYPE type);

	// �֐�
	void MakeVertexBuf(void); // ���_�o�b�t�@����
	void MakeIdxBuf(void);    // �C���f�b�N�X�o�b�t�@����

	// �ϐ�
	D3DXMATRIX				m_mtxWorld;	   // ���[���h�s��
	D3DXVECTOR3             m_size;        // �S�̂̑傫��
	D3DXVECTOR3				m_rot;		   // ��]��
	D3DXVECTOR3				m_scl;		   // �g�k��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuf;	   // ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuf;	   // �C���f�b�N�X�o�b�t�@
	D3DMATERIAL9			m_mat;		   // �}�e���A�����i���j
	int                     m_numFieldHorizon;  // ���̃t�B�[���h��
	int                     m_numFieldVertical; // �c�̃t�B�[���h��

	D3DXVECTOR3 m_halfSize;	// �����̑傫��

	Texture* m_pTexture;

};

#endif
