//*****************************************************************************
//
//		�L���[�u
//												Autohr : Yusuke Seki
//*****************************************************************************
#include "ObjectCube.h"
#include "Object3D.h"
#include "renderer.h"
#include "collision.h"

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
ObjectCube::ObjectCube() :Object(Object::TYPE::TYPE_3D)
{
	// �����o�ϐ�������
	_surface_TOP    = nullptr;	// ���
	_surface_BOTTOM = nullptr;	// ���
	_surface_LEFT   = nullptr;	// ����
	_surface_RIGHT  = nullptr;	// �E��
	_surface_FRONT  = nullptr;	// �O��
	_surface_BACK   = nullptr;	// �w��

	m_halfSize           = D3DXVECTOR3(0, 0, 0);
	m_rotate             = D3DXVECTOR3(0, 0, 0);
	m_scale              = D3DXVECTOR3(0, 0, 0);
	m_radius             = 0;
	m_normal[0]          = D3DXVECTOR3(0, 0, 0);
	m_normal[1]          = D3DXVECTOR3(0, 0, 0);
	m_normal[2]          = D3DXVECTOR3(0, 0, 0);
	m_normal[3]          = D3DXVECTOR3(0, 0, 0);
	m_color.color        = 0xffffffff;
	m_UV_StartPoint      = D3DXVECTOR2(0, 0);
	m_UV_Size            = D3DXVECTOR2(0, 0);
	m_pTexture           = nullptr;
	m_bDraw              = true;
}


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
ObjectCube::ObjectCube(Object::TYPE type) :Object(type)
{
	// �����o�ϐ�������
	_surface_TOP    = nullptr;	// ���
	_surface_BOTTOM = nullptr;	// ���
	_surface_LEFT   = nullptr;	// ����
	_surface_RIGHT  = nullptr;	// �E��
	_surface_FRONT  = nullptr;	// �O��
	_surface_BACK   = nullptr;	// �w��

	m_halfSize           = D3DXVECTOR3(0, 0, 0);
	m_rotate             = D3DXVECTOR3(0, 0, 0);
	m_scale              = D3DXVECTOR3(0, 0, 0);
	m_radius             = 0;
	m_normal[0]          = D3DXVECTOR3(0, 0, 0);
	m_normal[1]          = D3DXVECTOR3(0, 0, 0);
	m_normal[2]          = D3DXVECTOR3(0, 0, 0);
	m_normal[3]          = D3DXVECTOR3(0, 0, 0);
	m_color.color        = 0xffffffff;
	m_UV_StartPoint      = D3DXVECTOR2(0, 0);
	m_UV_Size            = D3DXVECTOR2(0, 0);
	m_pTexture           = nullptr;
	m_bDraw              = true;
}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
ObjectCube::~ObjectCube()
{
	// �I������
	Uninit();

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
ObjectCube* ObjectCube::Create(D3DXVECTOR3& pos, D3DXVECTOR3& size)
{
	// ����
	ObjectCube* pObjectCube = new ObjectCube(Object::TYPE::TYPE_3D_CUBE);

	// ������
	pObjectCube->Init(pos, size);

	return pObjectCube;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void ObjectCube::Init(D3DXVECTOR3& position, D3DXVECTOR3& size)
{
	//----- �f�[�^�̐ݒ� -----
	Object::SetPosition(position);																// ���W
	m_halfSize           = size * 0.5f;															// �����̑傫��
	m_rotate             = D3DXVECTOR3(0, 0, 0);												// ��]��
	m_scale              = D3DXVECTOR3(1, 1, 1);												// �g�k��
	m_radius             = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y);	// ���a
	m_normal[0]          = D3DXVECTOR3(0, 0, -1);												// �@��
	m_normal[1]          = D3DXVECTOR3(0, 0, -1);												// �@��
	m_normal[2]          = D3DXVECTOR3(0, 0, -1);												// �@��
	m_normal[3]          = D3DXVECTOR3(0, 0, -1);												// �@��
	m_color.color        = 0xffffffff;															// �F
	m_UV_StartPoint      = D3DXVECTOR2(0, 0);													// UV�J�n�_
	m_UV_Size            = D3DXVECTOR2(1, 1);													// UV�傫��
	m_bDraw              = true;																// true �ŕ`�揈�����s��

	// ���
	D3DXVECTOR3 setPos  = D3DXVECTOR3(position.x, position.y + size.y * 0.5f, position.z);
	D3DXVECTOR3 setSize = D3DXVECTOR3(size.x, size.z, 0);
	_surface_TOP    = Object3D::Create(setPos, setSize);
	_surface_TOP->SetRotate(D3DXVECTOR3(D3DXToRadian(90), 0, 0));

	// ���
	setPos  = D3DXVECTOR3(position.x, position.y - size.y * 0.5f, position.z);
	_surface_BOTTOM = Object3D::Create(setPos, setSize);
	_surface_BOTTOM->SetRotate(D3DXVECTOR3(D3DXToRadian(-90), 0, 0));

	// ����
	setPos  = D3DXVECTOR3(position.x - size.x * 0.5f, position.y, position.z);
	setSize = D3DXVECTOR3(size.z, size.y, 0);
	_surface_LEFT   = Object3D::Create(setPos, setSize);
	_surface_LEFT->SetRotate(D3DXVECTOR3(0, D3DXToRadian(90), 0));

	// �E��
	setPos = D3DXVECTOR3(position.x + size.x * 0.5f, position.y, position.z);
	_surface_RIGHT  = Object3D::Create(setPos, setSize);
	_surface_RIGHT->SetRotate(D3DXVECTOR3(0, D3DXToRadian(-90), 0));

	// �O��
	setPos = D3DXVECTOR3(position.x, position.y, position.z - size.z * 0.5f);
	setSize = D3DXVECTOR3(size.x, size.y, 0);
	_surface_FRONT  = Object3D::Create(setPos, setSize);
	_surface_FRONT->SetRotate(D3DXVECTOR3(0, D3DXToRadian(0), 0));

	// �w��
	setPos = D3DXVECTOR3(position.x, position.y, position.z + size.z * 0.5f);
	_surface_BACK   = Object3D::Create(setPos, setSize);
	_surface_BACK->SetRotate(D3DXVECTOR3(0, D3DXToRadian(180), 0));

}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void ObjectCube::Uninit(void)
{

}



//=============================================================================
//	��������
// ���W�̈ړ�
void ObjectCube::MovePosition(D3DXVECTOR3& movePosition)
{
	// ���W�̈ړ�
	Object::MovePosition(movePosition);

	_surface_TOP->MovePosition(movePosition);		// ���
	_surface_BOTTOM->MovePosition(movePosition);	// ���
	_surface_LEFT->MovePosition(movePosition);		// ����
	_surface_RIGHT->MovePosition(movePosition);		// �E��
	_surface_FRONT->MovePosition(movePosition);		// �O��
	_surface_BACK->MovePosition(movePosition);		// �w��

}

// �傫���̑���
void ObjectCube::MoveSize(D3DXVECTOR3& moveSize)
{
	// �傫���̑���
	m_halfSize += moveSize * 0.5f;
	m_radius    = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y);	// ���a
	
	_surface_TOP->MoveSize(moveSize);		// ���
	_surface_BOTTOM->MoveSize(moveSize);	// ���
	_surface_LEFT->MoveSize(moveSize);		// ����
	_surface_RIGHT->MoveSize(moveSize);		// �E��
	_surface_FRONT->MoveSize(moveSize);		// �O��
	_surface_BACK->MoveSize(moveSize);		// �w��

}

// ��]���̑���
void ObjectCube::MoveRotate(D3DXVECTOR3& moveRotate)
{
	// ��]���̑���
	m_rotate += moveRotate;
	
	_surface_TOP->MoveRotate(moveRotate);		// ���
	_surface_BOTTOM->MoveRotate(moveRotate);	// ���
	_surface_LEFT->MoveRotate(moveRotate);		// ����
	_surface_RIGHT->MoveRotate(moveRotate);		// �E��
	_surface_FRONT->MoveRotate(moveRotate);		// �O��
	_surface_BACK->MoveRotate(moveRotate);		// �w��

}

// �g�k���̑���
void ObjectCube::MoveScale(D3DXVECTOR3& moveScale)
{
	// �g�k���̑���
	m_scale.x = m_scale.x + moveScale.x < 0 ? 0 : m_scale.x + moveScale.x;
	m_scale.y = m_scale.y + moveScale.y < 0 ? 0 : m_scale.y + moveScale.y;
	m_scale.z = m_scale.z + moveScale.z < 0 ? 0 : m_scale.z + moveScale.z;

	_surface_TOP->MoveScale(moveScale);		// ���
	_surface_BOTTOM->MoveScale(moveScale);	// ���
	_surface_LEFT->MoveScale(moveScale);	// ����
	_surface_RIGHT->MoveScale(moveScale);	// �E��
	_surface_FRONT->MoveScale(moveScale);	// �O��
	_surface_BACK->MoveScale(moveScale);	// �w��

}

// �@���̑���
void ObjectCube::MoveNormal(D3DXVECTOR3& moveNormal0, D3DXVECTOR3& moveNormal1, D3DXVECTOR3& moveNormal2, D3DXVECTOR3& moveNormal3)
{
	// �@���̑���
	m_normal[0] += moveNormal0;
	m_normal[1] += moveNormal1;
	m_normal[2] += moveNormal2;
	m_normal[3] += moveNormal3;
	
	_surface_TOP->MoveNormal(moveNormal0, moveNormal1, moveNormal2, moveNormal3);		// ���
	_surface_BOTTOM->MoveNormal(moveNormal0, moveNormal1, moveNormal2, moveNormal3);	// ���
	_surface_LEFT->MoveNormal(moveNormal0, moveNormal1, moveNormal2, moveNormal3);		// ����
	_surface_RIGHT->MoveNormal(moveNormal0, moveNormal1, moveNormal2, moveNormal3);		// �E��
	_surface_FRONT->MoveNormal(moveNormal0, moveNormal1, moveNormal2, moveNormal3);		// �O��
	_surface_BACK->MoveNormal(moveNormal0, moveNormal1, moveNormal2, moveNormal3);		// �w��

}

// �F�̑���
void ObjectCube::MoveColor(int r, int g, int b, int a)
{
	// �F�̑���
	m_color.rgba[3] = m_color.rgba[3] + r >= 255 ? 255 : m_color.rgba[3] + r;
	m_color.rgba[2] = m_color.rgba[2] + g >= 255 ? 255 : m_color.rgba[2] + g;
	m_color.rgba[1] = m_color.rgba[1] + b >= 255 ? 255 : m_color.rgba[1] + b;
	m_color.rgba[0] = m_color.rgba[0] + a >= 255 ? 255 : m_color.rgba[0] + a;
	m_color.rgba[3] = m_color.rgba[3] + r <=   0 ?   0 : m_color.rgba[3] + r;
	m_color.rgba[2] = m_color.rgba[2] + g <=   0 ?   0 : m_color.rgba[2] + g;
	m_color.rgba[1] = m_color.rgba[1] + b <=   0 ?   0 : m_color.rgba[1] + b;
	m_color.rgba[0] = m_color.rgba[0] + a <=   0 ?   0 : m_color.rgba[0] + a;

	_surface_TOP->MoveColor(r, g, b, a);	// ���
	_surface_BOTTOM->MoveColor(r, g, b, a);	// ���
	_surface_LEFT->MoveColor(r, g, b, a);	// ����
	_surface_RIGHT->MoveColor(r, g, b, a);	// �E��
	_surface_FRONT->MoveColor(r, g, b, a);	// �O��
	_surface_BACK->MoveColor(r, g, b, a);	// �w��

}

// UV�J�n�_�̑���
void ObjectCube::MoveUV_StartPoint(D3DXVECTOR2& moveUV_StartPoint)
{
	// UV�J�n�_�̑���
	m_UV_StartPoint += moveUV_StartPoint;

	_surface_TOP->MoveUV_StartPoint(moveUV_StartPoint);		// ���
	_surface_BOTTOM->MoveUV_StartPoint(moveUV_StartPoint);	// ���
	_surface_LEFT->MoveUV_StartPoint(moveUV_StartPoint);	// ����
	_surface_RIGHT->MoveUV_StartPoint(moveUV_StartPoint);	// �E��
	_surface_FRONT->MoveUV_StartPoint(moveUV_StartPoint);	// �O��
	_surface_BACK->MoveUV_StartPoint(moveUV_StartPoint);	// �w��

}

// UV�傫���̑���
void ObjectCube::MoveUV_Size(D3DXVECTOR2& moveUV_Size)
{
	// UV�J�n�_�̑���
	m_UV_Size += moveUV_Size;

	_surface_TOP->MoveUV_Size(moveUV_Size);		// ���
	_surface_BOTTOM->MoveUV_Size(moveUV_Size);	// ���
	_surface_LEFT->MoveUV_Size(moveUV_Size);	// ����
	_surface_RIGHT->MoveUV_Size(moveUV_Size);	// �E��
	_surface_FRONT->MoveUV_Size(moveUV_Size);	// �O��
	_surface_BACK->MoveUV_Size(moveUV_Size);	// �w��

}



//=============================================================================
// �ݒ菈��
// ���W�̐ݒ�
void ObjectCube::SetPosition(D3DXVECTOR3& position)
{
	// ���
	D3DXVECTOR3 vec = _surface_TOP->GetPosition() - GetPosition();
	D3DXVECTOR3 setPos = GetPosition() + vec;
	_surface_TOP->SetPosition(setPos);

	// ���
	vec = _surface_BOTTOM->GetPosition() - GetPosition();
	setPos = GetPosition() + vec;
	_surface_BOTTOM->SetPosition(setPos);

	// ����
	vec = _surface_LEFT->GetPosition() - GetPosition();
	setPos = GetPosition() + vec;
	_surface_LEFT->SetPosition(setPos);

	// �E��
	vec = _surface_RIGHT->GetPosition() - GetPosition();
	setPos = GetPosition() + vec;
	_surface_RIGHT->SetPosition(setPos);

	// �O��
	vec = _surface_FRONT->GetPosition() - GetPosition();
	setPos = GetPosition() + vec;
	_surface_FRONT->SetPosition(setPos);

	// �w��
	vec = _surface_BACK->GetPosition() - GetPosition();
	setPos = GetPosition() + vec;
	_surface_BACK->SetPosition(setPos);

	// ���W�̈ړ�
	Object::SetPosition(position);

}

// �傫���̐ݒ�
void ObjectCube::SetSize(D3DXVECTOR3& size)
{
	// �傫���̐ݒ�
	m_halfSize = size * 0.5f;
	m_radius   = sqrtf(m_halfSize.x * m_halfSize.x + m_halfSize.y * m_halfSize.y);	// ���a

	// ���
	D3DXVECTOR3 setSize = D3DXVECTOR3(size.x, size.z, 0);
	_surface_TOP->SetSize(setSize);

	// ���
	setSize = D3DXVECTOR3(size.x, size.z, 0);
	_surface_BOTTOM->SetSize(setSize);

	// ����
	setSize = D3DXVECTOR3(size.z, size.y, 0);
	_surface_LEFT->SetSize(setSize);

	// �E��
	_surface_RIGHT->SetSize(setSize);

	// �O��
	setSize = D3DXVECTOR3(size.x, size.y, 0);
	_surface_FRONT->SetSize(setSize);

	// �w��
	_surface_BACK->SetSize(setSize);

}

// ��]���̐ݒ�
void ObjectCube::SetRotate(D3DXVECTOR3& rotate)
{
	// ��]���̐ݒ�
	m_rotate = rotate;

	// ���
	_surface_TOP->SetRotate(rotate);
	_surface_TOP->MoveRotate(D3DXVECTOR3(D3DXToRadian(90), 0, 0));

	// ���
	_surface_BOTTOM->SetRotate(rotate);
	_surface_BOTTOM->MoveRotate(D3DXVECTOR3(D3DXToRadian(-90), 0, 0));

	// ����
	_surface_LEFT->SetRotate(rotate);
	_surface_LEFT->MoveRotate(D3DXVECTOR3(0, D3DXToRadian(-90), 0));

	// �E��
	_surface_RIGHT->SetRotate(rotate);
	_surface_RIGHT->MoveRotate(D3DXVECTOR3(0, D3DXToRadian(90), 0));

	// �O��
	_surface_FRONT->SetRotate(rotate);
	_surface_FRONT->MoveRotate(D3DXVECTOR3(0, 0, 0));

	// �w��
	_surface_BACK->SetRotate(rotate);
	_surface_FRONT->MoveRotate(D3DXVECTOR3(0, D3DXToRadian(180), 0));

}

// �g�k���̐ݒ�
void ObjectCube::SetScale(D3DXVECTOR3& scale)
{
	// �g�k���̐ݒ�
	m_scale.x = scale.x < 0 ? 0 : scale.x;
	m_scale.y = scale.y < 0 ? 0 : scale.y;
	m_scale.z = scale.z < 0 ? 0 : scale.z;

	_surface_TOP->SetScale(scale);		// ���
	_surface_BOTTOM->SetScale(scale);	// ���
	_surface_LEFT->SetScale(scale);		// ����
	_surface_RIGHT->SetScale(scale);	// �E��
	_surface_FRONT->SetScale(scale);	// �O��
	_surface_BACK->SetScale(scale);		// �w��

}

// �@���̐ݒ�
void ObjectCube::SetNormal(D3DXVECTOR3& moveNormal0, D3DXVECTOR3& moveNormal1, D3DXVECTOR3& moveNormal2, D3DXVECTOR3& moveNormal3)
{
	// �@���̑���
	m_normal[0] = moveNormal0;
	m_normal[1] = moveNormal1;
	m_normal[2] = moveNormal2;
	m_normal[3] = moveNormal3;

	_surface_TOP->SetNormal(moveNormal0, moveNormal1, moveNormal2, moveNormal3);	// ���
	_surface_BOTTOM->SetNormal(moveNormal0, moveNormal1, moveNormal2, moveNormal3);	// ���
	_surface_LEFT->SetNormal(moveNormal0, moveNormal1, moveNormal2, moveNormal3);	// ����
	_surface_RIGHT->SetNormal(moveNormal0, moveNormal1, moveNormal2, moveNormal3);	// �E��
	_surface_FRONT->SetNormal(moveNormal0, moveNormal1, moveNormal2, moveNormal3);	// �O��
	_surface_BACK->SetNormal(moveNormal0, moveNormal1, moveNormal2, moveNormal3);	// �w��

}

// �F�̐ݒ�
void ObjectCube::SetColor(unsigned int rgba)
{
	// �F�ݒ�
	m_color.color = rgba;

	_surface_TOP->SetColor(rgba);		// ���
	_surface_BOTTOM->SetColor(rgba);	// ���
	_surface_LEFT->SetColor(rgba);		// ����
	_surface_RIGHT->SetColor(rgba);		// �E��
	_surface_FRONT->SetColor(rgba);		// �O��
	_surface_BACK->SetColor(rgba);		// �w��

}

// UV�J�n�_�̐ݒ�
void ObjectCube::SetUV_StartPoint(D3DXVECTOR2& UV_StartPoint)
{
	// UV�J�n�_�̐ݒ�
	m_UV_StartPoint = UV_StartPoint;

	_surface_TOP->SetUV_StartPoint(UV_StartPoint);		// ���
	_surface_BOTTOM->SetUV_StartPoint(UV_StartPoint);	// ���
	_surface_LEFT->SetUV_StartPoint(UV_StartPoint);	// ����
	_surface_RIGHT->SetUV_StartPoint(UV_StartPoint);	// �E��
	_surface_FRONT->SetUV_StartPoint(UV_StartPoint);	// �O��
	_surface_BACK->SetUV_StartPoint(UV_StartPoint);	// �w��

}

// UV�̑傫���̐ݒ�
void ObjectCube::SetUV_Size(D3DXVECTOR2& UV_Size)
{
	// UV�̑傫���̐ݒ�
	m_UV_StartPoint = UV_Size;

	_surface_TOP->SetUV_Size(UV_Size);		// ���
	_surface_BOTTOM->SetUV_Size(UV_Size);	// ���
	_surface_LEFT->SetUV_Size(UV_Size);	// ����
	_surface_RIGHT->SetUV_Size(UV_Size);	// �E��
	_surface_FRONT->SetUV_Size(UV_Size);	// �O��
	_surface_BACK->SetUV_Size(UV_Size);	// �w��

}

// �`�揈���̗L���̐ݒ�
void ObjectCube::SetDraw(bool bDraw)
{
	_surface_TOP->SetDraw(bDraw);		// ���
	_surface_BOTTOM->SetDraw(bDraw);	// ���
	_surface_LEFT->SetDraw(bDraw);		// ����
	_surface_RIGHT->SetDraw(bDraw);		// �E��
	_surface_FRONT->SetDraw(bDraw);		// �O��
	_surface_BACK->SetDraw(bDraw);		// �w��

}

// �e�N�X�`���̐ݒ�
void ObjectCube::SetTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;

	_surface_TOP->SetTexture(pTexture);		// ���
	_surface_BOTTOM->SetTexture(pTexture);	// ���
	_surface_LEFT->SetTexture(pTexture);	// ����
	_surface_RIGHT->SetTexture(pTexture);	// �E��
	_surface_FRONT->SetTexture(pTexture);	// �O��
	_surface_BACK->SetTexture(pTexture);	// �w��

}
