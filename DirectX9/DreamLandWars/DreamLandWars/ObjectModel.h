//*****************************************************************************
//
//		���f���i���X�g�\���j
//													Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _OBJECTMODEL_H_
#define _OBJECTMODEL_H_

#include "main.h"
#include "Object.h"


class ObjectModel : public Object
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	ObjectModel();
	ObjectModel(Object::TYPE type);
	virtual ~ObjectModel();

	
	//----- ��{�I�Ȋ֐� -----
	static ObjectModel* Create(D3DXVECTOR3& position, const char* FileName);
	virtual void Init(D3DXVECTOR3& position, const char* FileName);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);


	//----- �������� -----
	virtual void MovePosition(D3DXVECTOR3& movePosition);	// ���W�̈ړ�
	        void MoveSize(D3DXVECTOR3& moveSize);			// �傫���̑���
	        void MoveRotate(D3DXVECTOR3& moveRotate);		// ��]���̑���
	        void MoveScale(D3DXVECTOR3& moveScale);			// �g�k���̑���
	        void MoveColor(int r, int g, int b, int a);		// �F�̑���

	//----- �ݒ菈�� -----
	void SetPosition(D3DXVECTOR3& position);									// ���W�̐ݒ�
	void SetSize(D3DXVECTOR3& size);											// �傫���̐ݒ�
	void SetRotate(D3DXVECTOR3& rotate);										// ��]���̐ݒ�
	void SetScale(D3DXVECTOR3& scale);											// �g�k���̐ݒ�
	void SetColor(unsigned int rgba);											// �F�̐ݒ�
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { *m_pTexture = pTexture; }	// �e�N�X�`���̐ݒ�
	void SetDraw(bool bDraw) { m_bDraw = bDraw; }								// �`�揈���̗L���̐ݒ�
	void SetFront(D3DXVECTOR3& front) { m_front = front; }

	// ������
	void SetRotateToObj(D3DXVECTOR3& ObjectPostion);	// �Ώۂ̕����������悤�ɐݒ肷��
	void SetRadius(float radius) { m_radius = radius; }	// ���a�̐ݒ�


	//----- �f�[�^��Ԃ����� -----
	D3DXMATRIX&        GetWorldMatrix() { return m_WorldMatrix; }		// ���[���h�}�g���N�X��Ԃ�
	D3DXVECTOR3        GetSize()        { return (m_halfSize * 2); }	// �傫����Ԃ�
	D3DXVECTOR3&       GetHalfSize()    { return m_halfSize; }			// �����̑傫����Ԃ�
	D3DXVECTOR3&       GetRotate()      { return m_rotate; }			// ��]����Ԃ�
	D3DXVECTOR3&       GetScale()       { return m_scale; }				// �g�k����Ԃ�
	float              GetRadius()      { return m_radius; }			// ���a��Ԃ�
	D3DXVECTOR3&       GetFront()       { return m_front; }				// �O������Ԃ�
	LPDIRECT3DTEXTURE9 GetTexture()     { return *m_pTexture; }			// �e�N�X�`����Ԃ�


private:
	//----- ���p�̂̒�` -----
	union Color { // �F
		unsigned int color;
		unsigned char rgba[4];
	};


	//----- �֐� -----
	void MakeVertexBuf();							// ���_�o�b�t�@�̐���
	void UpdateVertexBuf();							// ���_�o�b�t�@�̍X�V
	void UpdateWorldMatrix();						// ���[���h�}�g���N�X�̍X�V
	void LoadModel(const char* FileName);			// ���f���f�[�^�̓ǂݍ���
	void LoadModelSizeFromX(const char* FileName);	// X�t�@�C������T�C�Y��ǂݍ���
	void LoadMaterial();							// �}�e���A�����̓ǂݍ���
	void LoadMeshModel_DX(const char* FileName);	// ���f���f�[�^�̓ǂݍ��݁idirectX�֗̕��֐��g�p�j


	//----- �f�[�^ -----
	LPD3DXMESH	  m_pMesh;		// ���b�V�����
	D3DMATERIAL9* m_pMeshMat;	// �}�e���A�����
	DWORD		  m_numMat;		// �}�e���A����

	D3DXMATRIX	m_WorldMatrix;	// ���[���h�}�g���N�X
	D3DXVECTOR3 m_halfSize;		// �����̑傫��
	D3DXVECTOR3 m_rotate;		// ��]��
	D3DXVECTOR3	m_scale;		// �g�k��
	float       m_radius;		// ���a
	Color       m_color;		// �F
	D3DXVECTOR3 m_front;		// �O����

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9*     m_pTexture;	// �e�N�X�`��

	bool m_bUpdateVertexBuf;	// true �Œ��_�o�b�t�@�̍X�V������
	bool m_bUpdateWorldMatrix;	// true �Ń��[���h�}�g���N�X�̍X�V������
	bool m_bDraw;				// true �ŕ`�揈�����s��

};

#endif

