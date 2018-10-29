//*****************************************************************************
//
//		�A�C�R��
//													Author : Yusuke Seki
//*****************************************************************************
#include "Icon.h"
#include "MainGame.h"
#include "list_LoadTexture_MainGame.h"
#include "Effect3D.h"
#include "tower.h"



//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Icon::Icon() : ObjectBillboard(Object::TYPE::TYPE_3D_BILLBOARD_ICON)
{
	// �f�[�^�̃N���A

}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
Icon::~Icon()
{
	// �I������
	Uninit();

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
Icon* Icon::Create(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera, Object::GROUP group)
{
	// ���̂̐���
	Icon* pIcon = new Icon;

	// ���̂̏�����
	pIcon->Init(position, size, pCamera, group);

	// �������ꂽ�^�C�}�[�̃|�C���^��Ԃ�
	return pIcon;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void Icon::Init(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera, Object::GROUP group)
{
	// �f�[�^�̏�����
	{
		// �p���f�[�^�̏�����
		ObjectBillboard::Init(position, size, pCamera);

		SetGroup(group);

		if      (group == Object::GROUP_A) SetColor(0xff0000b0);
		else if (group == Object::GROUP_B) SetColor(0x00ffffb0);

	}

}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void Icon::Uninit(void)
{
	// �p���f�[�^�̏I������
	ObjectBillboard::Uninit();

}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void Icon::Update(void)
{

}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void Icon::Draw(void)
{
	// �`�揈��
	ObjectBillboard::Draw();

}



//=============================================================================
// ����


//=============================================================================
// �ݒ�

