//*****************************************************************************
//
//		Part
//													Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _PART_H_
#define _PART_H_

#include "main.h"
#include "Object.h"


class Part : public Object
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	Part();
	Part(Object::TYPE type);
	virtual ~Part();


	//----- ��{�I�Ȋ֐� -----
	static Part* Create(D3DXVECTOR3& position, const char* FileName);
	virtual void Init(D3DXVECTOR3& position, const char* FileName);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);


	//----- �������� -----
	virtual void MovePosition(D3DXVECTOR3& movePosition);																				// ���W�̈ړ�
	void MoveSize(D3DXVECTOR3& moveSize);																						// �傫���̑���
	void MoveRotate(D3DXVECTOR3& moveRotate);																					// ��]���̑���
	void MoveScale(D3DXVECTOR3& moveScale);																						// �g�k���̑���
	void MoveNormal(D3DXVECTOR3& moveNormal0, D3DXVECTOR3& moveNormal1, D3DXVECTOR3& moveNormal2, D3DXVECTOR3& moveNormal3);	// �@���̑���
	void MoveColor(int r, int g, int b, int a);																					// �F�̑���
	void MoveUV_StartPoint(D3DXVECTOR2& moveUV_StartPoint);																		// UV�J�n�_�̑���
	void MoveUV_Size(D3DXVECTOR2& moveUV_Size);																					// UV�傫���̑���


	//----- �ݒ菈�� -----
	void SetPosition(D3DXVECTOR3& position);																				// ���W�̐ݒ�
	void SetSize(D3DXVECTOR3& size);																						// �傫���̐ݒ�
	void SetRotate(D3DXVECTOR3& rotate);																					// ��]���̐ݒ�
	void SetScale(D3DXVECTOR3& scale);																						// �g�k���̐ݒ�
	void SetNormal(D3DXVECTOR3& moveNormal0, D3DXVECTOR3& moveNormal1, D3DXVECTOR3& moveNormal2, D3DXVECTOR3& moveNormal3);	// �@���̐ݒ�
	void SetColor(unsigned int rgba);																						// �F�̐ݒ�
	void SetUV_StartPoint(D3DXVECTOR2& UV_StartPoint);																		// UV�J�n�_�̐ݒ�
	void SetUV_Size(D3DXVECTOR2& UV_Size);																					// UV�傫���̐ݒ�
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { *m_pTexture = pTexture; }												// �e�N�X�`���̐ݒ�
	void SetDraw(bool bDraw) { m_bDraw = bDraw; }																			// �`�揈���̗L���̐ݒ�
	void SetVecZ(D3DXVECTOR3& vecZ) { m_vecZ = vecZ; }

	// ������
	void SetRotateToObj(D3DXVECTOR3& ObjectPostion);	// �Ώۂ̕����������悤�ɐݒ肷��
	void SetRadius(float radius) { m_radius = radius; }	// ���a�̐ݒ�

	// �e�̃|�C���^�ݒ�
	void SetParent(Part *pParent) {
		m_pParent = pParent;
		m_bUpdateWorldMatrix = true;
	}


	//----- �f�[�^��Ԃ����� -----
	D3DXMATRIX&        GetWorldMatrix() { return m_WorldMatrix; }	// ���[���h�}�g���N�X��Ԃ�
	D3DXVECTOR3        GetSize() { return (m_halfSize * 2); }		// �傫����Ԃ�
	D3DXVECTOR3&       GetHalfSize() { return m_halfSize; }			// �����̑傫����Ԃ�
	D3DXVECTOR3&       GetRotate() { return m_rotate; }				// ��]����Ԃ�
	D3DXVECTOR3&       GetScale() { return m_scale; }				// �g�k����Ԃ�
	float              GetRadius() { return m_radius; }				// ���a��Ԃ�
	D3DXVECTOR3&       GetVecZ() { return m_vecZ; }					// �����Ă������Ԃ�
	LPDIRECT3DTEXTURE9 GetTexture() { return *m_pTexture; }			// �e�N�X�`����Ԃ�

	Part* GetParent() { return m_pParent; }

private:
	//----- ���p�̂̒�` -----
	union Color { // �F
		unsigned int color;
		unsigned char rgba[4];
	};


	//----- �\���̂̒�` -----
	struct MATERIAL {	// �}�e���A���\����
		Color		Ambient;
		Color		Diffuse;
		Color		Specular;
		Color		Emission;
		float		Shininess;
	};

	//----- �}�e���A���\���� -----
	struct MODEL_MATERIAL {
		char Name[256];
		MATERIAL Material;
		unsigned int Texture;
	};

	//----- �`��T�u�Z�b�g�\���� -----
	struct SUBSET {
		unsigned int StartIndex;
		unsigned int IndexNum;
		MODEL_MATERIAL Material;
	};

	//----- ���f���\���� -----
	struct MODEL {
		VERTEX_3D    *VertexArray;
		unsigned int *IndexArray;
		unsigned int IndexNum;
		SUBSET       *Subset;
		unsigned int SubsetNum;
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
	D3DXVECTOR3 m_vecZ;			// �����Ă����

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9*     m_pTexture;	// �e�N�X�`��

	bool m_bUpdateVertexBuf;	// true �Œ��_�o�b�t�@�̍X�V������
	bool m_bUpdateWorldMatrix;	// true �Ń��[���h�}�g���N�X�̍X�V������
	bool m_bDraw;				// true �ŕ`�揈�����s��

	Part *m_pParent;	// �e�̃|�C���^

							
	//LPD3DXMESH   mesh;		// ���b�V�����
	//D3DMATERIAL9 *meshMat;	// �}�e���A�����
	//DWORD        numMat;	// �}�e���A����
	//D3DXVECTOR3  position;	// ���W
	//D3DXVECTOR3  rotation;	// ��]��
	//D3DXMATRIX   matrix;	// ���[���h�}�g���N�X
	//LPDIRECT3DTEXTURE9* texture;	// �e�N�X�`��

};

#endif

