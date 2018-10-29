//*****************************************************************************
//
//		�L���[�u
//												Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _OBJECTCUBE_H_
#define _OBJECTCUBE_H_

#include "main.h"
#include "Object.h"
#include "Object3D.h"

class ObjectCube : public Object
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	ObjectCube();
	ObjectCube(Object::TYPE type);
	virtual ~ObjectCube();

	
	//----- ��{�I�Ȋ֐� -----
	static ObjectCube* Create(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Init(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Uninit(void);
	virtual void Update(void) {}
	virtual void Draw(void) {}


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
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture);																				// �e�N�X�`���̐ݒ�
	void SetDraw(bool bDraw);																									// �`�揈���̗L���̐ݒ�


	//----- �f�[�^��Ԃ����� -----
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

	D3DXVECTOR3& GetNormal_TOP()	{ return _surface_TOP->GetNormal_Suface(); }
	D3DXVECTOR3& GetNormal_BOTTOM()	{ return _surface_BOTTOM->GetNormal_Suface(); }
	D3DXVECTOR3& GetNormal_LEFT()	{ return _surface_LEFT->GetNormal_Suface(); }
	D3DXVECTOR3& GetNormal_RIGHT()	{ return _surface_RIGHT->GetNormal_Suface(); }
	D3DXVECTOR3& GetNormal_FRONT()	{ return _surface_FRONT->GetNormal_Suface(); }
	D3DXVECTOR3& GetNormal_BACK()	{ return _surface_BACK->GetNormal_Suface(); }

	D3DXVECTOR3& GetPosition_TOP()		{ return _surface_TOP->GetPosition(); }
	D3DXVECTOR3& GetPosition_BOTTOM()	{ return _surface_BOTTOM->GetPosition(); }
	D3DXVECTOR3& GetPosition_LEFT()		{ return _surface_LEFT->GetPosition(); }
	D3DXVECTOR3& GetPosition_RIGHT()	{ return _surface_RIGHT->GetPosition(); }
	D3DXVECTOR3& GetPosition_FRONT()	{ return _surface_FRONT->GetPosition(); }
	D3DXVECTOR3& GetPosition_BACK()		{ return _surface_BACK->GetPosition(); }

protected:
	//----- ���p�̂̒�` -----
	union Color { // �F
		unsigned int color;
		unsigned char rgba[4];
	};


private:
	//----- �f�[�^ -----
	Object3D* _surface_TOP;		// Surface of Top
	Object3D* _surface_BOTTOM;	// Surface of Bottom
	Object3D* _surface_LEFT;	// Surface of Left
	Object3D* _surface_RIGHT;	// Surface of Right
	Object3D* _surface_FRONT;	// Surface of Front
	Object3D* _surface_BACK;	// Surface of Back

	D3DXVECTOR3 m_halfSize;			// �����̑傫��
	D3DXVECTOR3 m_rotate;			// ��]��
	D3DXVECTOR3 m_scale;			// �g�k��
	float       m_radius;			// ���a
	D3DXVECTOR3 m_normal[4];		// �@��
	Color       m_color;			// �F
	D3DXVECTOR2 m_UV_StartPoint;	// UV�J�n�_
	D3DXVECTOR2 m_UV_Size;			// UV�傫��

	LPDIRECT3DTEXTURE9      m_pTexture;	// �e�N�X�`��

	bool m_bDraw;				// true �ŕ`�揈�����s��

};

#endif

