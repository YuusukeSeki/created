//*****************************************************************************
//
//		���U���g
//												Author : Yusuke Seki
//*****************************************************************************
#include "result.h"
#include "list_LoadTexture_Result.h"

// �V�[���J��
#include "GameManager.h"
#include "title.h"
#include "fade.h"

// ���͐���
#include "input.h"

// �w�i
#include "Object2D.h"
#include "scene2D.h"

// �e�N�X�`��
#include "TextureManager.h"
#include "texture.h"



//=============================================================================
//	��{�I�Ȋ֐�
// ������
void Result::Init()
{
	List_LoadTexture_Result::LoadTextureAll(m_pTexture);

	// �w�i�̐���
	D3DXVECTOR3 pos((SCREEN_WIDTH >> 1), (SCREEN_HEIGHT >> 1), 0);
	D3DXVECTOR3 size((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0);
	//m_pScene2D = Scene2D::Create(pos, size);
	//m_pScene2D->SetTexture(m_pTexture[List_LoadTexture_Result::TEXTURE_NAME::BACKGROUND_TEXNAME]);

	m_pObject2D = Object2D::Create(pos, size);
	m_pObject2D->SetTexture(m_pTexture[List_LoadTexture_Result::TEXTURE_NAME::BACKGROUND_TEXNAME]->GetTexture());

}


// �I��
void Result::Uninit()
{
	// �e�N�X�`���̉������
	TextureManager::ReleaseAll();

}


// �X�V
GameScene* Result::Update()
{
	// ���̓f�o�C�X�̎擾
	Input* pInput = GameManager::GetInput();

	// �t�F�[�h��Ԃ̎擾
	Fade* pFade = GameManager::GetFade();

	// ���N���b�N�Ŏ��̃V�[����
	if (pInput->GetKeyboardTrigger(DIK_SPACE)) {
	//if (pInput->GetMouseTrigger(Input::MOUSEBUTTON_LEFT)) {
		// �t�F�[�h�A�E�g�J�n
		pFade->Start_FadeOut();
	}

	// �t�F�[�h�A�E�g�I�������H
	if (pFade->Finish_FadeOut()) {
		// �Q�[���V�[�������C���Q�[����
		return new Title;
	}

	return this;
}


// �`��
void Result::Draw()
{
}


// ���
void Result::Release()
{
	// �I������
	Uninit();

	// �������̉��
	delete this;
}

