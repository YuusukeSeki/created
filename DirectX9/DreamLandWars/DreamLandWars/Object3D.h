//*****************************************************************************
//
//		3D�|���S���i���X�g�\���j
//												Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"
#include "Object.h"


class Object3D : public Object
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	Object3D();
	Object3D(Object::TYPE type);
	virtual ~Object3D();

	
	//----- ��{�I�Ȋ֐� -----
	static Object3D* Create(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Init(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Uninit(void);
	virtual void Update(void) {}
	virtual void Draw(void);


	//----- �������� -----
	void MovePosition(D3DXVECTOR3& movePosition);																				// ���W�̈ړ�
	void MoveSize(D3DXVECTOR3& moveSize);																						// �傫���̑���
	void MoveRotate(D3DXVECTOR3& moveRotate);																					// ��]���̑���
	void MoveScale(D3DXVECTOR3& moveScale);																						// �g�k���̑���
	void MoveNormal(D3DXVECTOR3& moveNormal0,  D3DXVECTOR3& moveNormal1,  D3DXVECTOR3& moveNormal2,  D3DXVECTOR3& moveNormal3);	// �@���̑���
	void MoveColor(int r, int g, int b, int a);																					// �F�̑���
	void MoveUV_StartPoint(D3DXVECTOR2& moveUV_StartPoint);																		// UV�J�n�_�̑���
	void MoveUV_Size(D3DXVECTOR2& moveUV_Size);																					// UV�傫���̑���


	//----- �ݒ菈�� -----
	void SetPosition(D3DXVECTOR3& position);																					// ���W�̐ݒ�
	void SetSize(D3DXVECTOR3& size);																							// �傫���̐ݒ�
	void SetRotate(D3DXVECTOR3& rotate);																						// ��]���̐ݒ�
	void SetScale(D3DXVECTOR3& scale);																							// �g�k���̐ݒ�
	void SetNormal(D3DXVECTOR3& moveNormal0,  D3DXVECTOR3& moveNormal1,  D3DXVECTOR3& moveNormal2,  D3DXVECTOR3& moveNormal3);	// �@���̐ݒ�
	void SetColor(unsigned int rgba);																							// �F�̐ݒ�
	void SetUV_StartPoint(D3DXVECTOR2& UV_StartPoint);																			// UV�J�n�_�̐ݒ�
	void SetUV_Size(D3DXVECTOR2& UV_Size);																						// UV�傫���̐ݒ�
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }														// �e�N�X�`���̐ݒ�
	void SetDraw(bool bDraw) { m_bDraw = bDraw; }																				// �`�揈���̗L���̐ݒ�


	//----- �f�[�^��Ԃ����� -----
	D3DXMATRIX&        GetWorldMatrix()        { return m_WorldMatrix; }	// ���[���h�}�g���N�X��Ԃ�
	D3DXVECTOR3        GetSize()               { return (m_halfSize * 2); }	// �傫����Ԃ�
	D3DXVECTOR3&       GetHalfSize()           { return m_halfSize; }		// �����̑傫����Ԃ�
	D3DXVECTOR3&       GetRotate()             { return m_rotate; }			// ��]����Ԃ�
	D3DXVECTOR3&       GetScale()              { return m_scale; }			// �g�k����Ԃ�
	float              GetRadius()             { return m_radius; }			// ���a��Ԃ�
	D3DXVECTOR3&       GetNormal_LeftTop()     { return m_normal[0]; }		// �@����Ԃ�
	D3DXVECTOR3&       GetNormal_RightTop()    { return m_normal[1]; }		// �@����Ԃ�
	D3DXVECTOR3&       GetNormal_LeftBottom()  { return m_normal[2]; }		// �@����Ԃ�
	D3DXVECTOR3&       GetNormal_RightBottom() { return m_normal[3]; }		// �@����Ԃ�
	unsigned int       GetColor()              { return m_color.color; }	// �F��Ԃ�
	D3DXVECTOR2&       GetUV_StartPoint()      { return m_UV_StartPoint; }	// UV�J�n�_��Ԃ�
	D3DXVECTOR2&       GetUV_Size()            { return m_UV_Size; }		// UV�̑傫����Ԃ�
	LPDIRECT3DTEXTURE9 GetTexture()            { return m_pTexture; }		// �e�N�X�`����Ԃ�

	D3DXVECTOR3& GetNormal_Suface() { return m_normal_Surface; }	// �ʂ̖@����Ԃ�

protected:
	//----- ���p�̂̒�` -----
	union Color { // �F
		unsigned int color;
		unsigned char rgba[4];
	};


protected:
	//----- �ݒ菈�� -----
	void SetWorldMatrix(D3DXMATRIX& mtxWorld)          { m_WorldMatrix = mtxWorld; }					// ���[���h�}�g���N�X�̐ݒ�
	void SetUpdateVertexBuf(bool bUpdateVertexBuf)     { m_bUpdateVertexBuf = bUpdateVertexBuf; }		// true �Œ��_�o�b�t�@�̍X�V����������
	void SetUpdateWorldMatrix(bool bUpdateWorldMatrix) { m_bUpdateWorldMatrix = bUpdateWorldMatrix; }	// true �Ń��[���h�}�g���N�X�̍X�V����������
	virtual void UpdateWorldMatrix();	// ���[���h�}�g���N�X�̍X�V


private:
	//----- ���\�b�h -----
	void MakeVertexBuf();	// ���_�o�b�t�@�̐���
	void UpdateVertexBuf();	// ���_�o�b�t�@�̍X�V


	//----- �f�[�^ -----
	D3DXMATRIX  m_WorldMatrix;		// ���[���h�}�g���N�X
	D3DXVECTOR3 m_halfSize;			// �����̑傫��
	D3DXVECTOR3 m_rotate;			// ��]��
	D3DXVECTOR3 m_scale;			// �g�k��
	float       m_radius;			// ���a
	D3DXVECTOR3 m_normal[4];		// �@��
	Color       m_color;			// �F
	D3DXVECTOR2 m_UV_StartPoint;	// UV�J�n�_
	D3DXVECTOR2 m_UV_Size;			// UV�傫��

	D3DXVECTOR3 m_normal_Surface;	// �ʂ̖@��

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9      m_pTexture;	// �e�N�X�`��

	bool m_bUpdateVertexBuf;	// true �Œ��_�o�b�t�@�̍X�V������
	bool m_bUpdateWorldMatrix;	// true �Ń��[���h�}�g���N�X�̍X�V������
	bool m_bDraw;				// true �ŕ`�揈�����s��

};

#endif

