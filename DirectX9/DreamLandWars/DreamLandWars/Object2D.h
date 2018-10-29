//*****************************************************************************
//
//		2D�|���S���i���X�g�\���j
//												Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "main.h"
#include "object.h"


class Object2D : public Object	// 2D�|���S��
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	Object2D();
	Object2D(Object::TYPE type);
	virtual ~Object2D();

	
	//----- ��{�I�Ȋ֐� -----
	static Object2D* Create(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Init(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Uninit(void);
	virtual void Update(void) {}
	virtual void Draw(void);


	//----- �������� -----
	virtual void MovePosition(D3DXVECTOR3& movePosition);			// ���W�̈ړ�
	virtual void MoveSize(D3DXVECTOR3& moveSize);					// �傫���̑���
	virtual void MoveRotate(float moveRotate);						// ��]���̑���
	virtual void MoveColor(int r, int g, int b, int a);				// �F�̑���
	virtual void MoveUV_StartPoint(D3DXVECTOR2& moveUV_StartPoint);	// UV�J�n�_�̑���
	virtual void MoveUV_Size(D3DXVECTOR2& moveUV_Size);				// UV�傫���̑���


	//----- �ݒ菈�� -----
	virtual void SetPosition(D3DXVECTOR3& position);								// ���W�̐ݒ�
	virtual void SetSize(D3DXVECTOR3& size);										// �傫���̐ݒ�
	virtual void SetRotate(float rotate);											// ��]���̐ݒ�
	virtual void SetColor(unsigned int rgba);										// �F�̐ݒ�
	virtual void SetUV_StartPoint(D3DXVECTOR2& UV_StartPoint);						// UV�J�n�_�̐ݒ�
	virtual void SetUV_Size(D3DXVECTOR2& UV_Size);									// UV�傫���̐ݒ�
	        void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }	// �e�N�X�`���̐ݒ�
	        void SetDraw(bool bDraw) { m_bDraw = bDraw; }							// �`�揈���̗L���̐ݒ�


	//----- �f�[�^��Ԃ����� -----
	D3DXVECTOR3        GetSize()          { return (m_halfSize * 2); }	// �傫����Ԃ�
	D3DXVECTOR3&       GetHalfSize()      { return m_halfSize; }		// �����̑傫����Ԃ�
	float              GetRadius()        { return m_radius; }			// ���a��Ԃ�
	float              GetAngle()         { return m_angle; }			// atan��Ԃ�
	float              GetRotate()        { return m_rotate; }			// ��]����Ԃ�
	unsigned int       GetColor()         { return m_color.color; }		// �F��Ԃ�
	D3DXVECTOR2&       GetUV_StartPoint() { return m_UV_StartPoint; }	// UV�J�n�_��Ԃ�
	D3DXVECTOR2&       GetUV_Size()       { return m_UV_Size; }			// UV�̑傫����Ԃ�
	LPDIRECT3DTEXTURE9 GetTexture()       { return m_pTexture; }		// �e�N�X�`����Ԃ�


protected:
	//----- ���p�̂̒�` -----
	union Color { // �F
		unsigned int color;
		unsigned char rgba[4];
	};


private:
	//----- �֐� -----
	void MakeVertexBuf();		// ���_�o�b�t�@�̐���
	void UpdateVertexBuf();		// ���_�o�b�t�@�̍X�V


	//----- �f�[�^ -----
	D3DXVECTOR3 m_halfSize;			// �����̑傫��
	float       m_radius;			// ���a
	float       m_angle;			// atan
	float       m_rotate;			// ��]��
	Color       m_color;			// �F
	D3DXVECTOR2 m_UV_StartPoint;	// UV�J�n�_
	D3DXVECTOR2 m_UV_Size;			// UV�傫��

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9      m_pTexture;	// �e�N�X�`��

	bool m_bUpdateVertexBuf;	// true �Œ��_�o�b�t�@�̍X�V������
	bool m_bDraw;				// true �ŕ`�揈�����s��

};

#endif
