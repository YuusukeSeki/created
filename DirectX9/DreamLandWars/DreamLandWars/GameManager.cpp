//*****************************************************************************
//	
//	�Q�[���Ǘ�
//	Author	:	Yusuke Seki
//	
//*****************************************************************************
#include "GameManager.h"
#include "renderer.h"
#include "GameScene.h"
#include "input.h"
#include "fade.h"
#include "Object.h"
#include "EffectManager.h"
#include "TextureManager.h"

#include "EventButton.h"


//----- �ÓI�����o�ϐ������� -----
GameScene* GameManager::m_pGameScene = nullptr;
Input*	   GameManager::m_pInput     = nullptr;
Fade*	   GameManager::m_pFade      = nullptr;
int        GameManager::_drawDebugInfo = 1;


//-----------------------------------------------------------------------------
//	������
//-----------------------------------------------------------------------------
HRESULT GameManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow, GameScene* pGameScene)
{
	// DirectX������
	if( FAILED( Renderer::Init( hWnd, bWindow ) ) ){ // �ł��Ȃ�����
		// �G���[���b�Z�[�W�̕\��
		_MSGERROR("Failed Init DirectX!!", "");

		// �I���܂�
		return E_FAIL;
	}
	

	// �Q�[���V�[���擾�ł����H
	if (pGameScene == nullptr) { // �ł��ĂȂ�
		// �G���[���b�Z�[�W�\��
		_MSGERROR("Cannot Get GameScene!!", "");

		// DirectX�I��
		Renderer::Uninit();

		// �I���܂�
		return E_FAIL;
	}

	// �Q�[���V�[���̎擾
	m_pGameScene = pGameScene;

	// �f�o�b�O����
	OX::DebugFont::initialize(Renderer::GetDevice(), 2500, 1024);

	
	// ���͐���f�o�C�X����
	m_pInput = Input::Create(hInstance, hWnd);

	// ���͏�Ԃ̍X�V
	m_pInput->Update();


	// �Q�[���V�[����������
	m_pGameScene->Init();


	// �t�F�[�h�̐���
	m_pFade = Fade::Create();


	// ����I��
	return S_OK;
}


//-----------------------------------------------------------------------------
//	�I��
//-----------------------------------------------------------------------------
void GameManager::Uninit()
{
	// �t�F�[�h�̉������
	m_pFade->Release();
	m_pFade = nullptr;

	// �I�u�W�F�N�g�̉������
	Object::ReleaseAll();

	// �G�t�F�N�g�̉������
	EffectManager::ReleaseAll();
	
	// �e�N�X�`���̉������
	TextureManager::ReleaseAll();

	// �Q�[���V�[���̉������
	m_pGameScene->Release();
	m_pGameScene = nullptr;

	// ���̓f�o�C�X�̉������
	m_pInput->Uninit();
	m_pInput = nullptr;
	
	// �f�o�b�N�\���̉������
	OX::DebugFont::terminate();

	// DirectX�̉������
	Renderer::Uninit();
}


//-----------------------------------------------------------------------------
//	�X�V
//-----------------------------------------------------------------------------
void GameManager::Update()
{
	// ���̓f�o�C�X�̍X�V
	m_pInput->Update();

	// �t�F�[�h�̍X�V
	m_pFade->Update();

	// �Q�[���V�[���̍X�V�Ǝ擾
	GameScene* pGameScene = m_pGameScene->Update();

#ifdef _DEBUG
	// �{������
	if (m_pInput->GetKeyboardPress(BUTTON_DOUBLE_SPEED)) {
		// �I�u�W�F�N�g�̍X�V����
		Object::UpdateAll();

		// �G�t�F�N�g�̍X�V����
		EffectManager::UpdateAll();

	}
#endif

	// �I�u�W�F�N�g�̍X�V����
	Object::UpdateAll();

	// �G�t�F�N�g�̍X�V����
	EffectManager::UpdateAll();

	// �V�[���J�ڂ���H
	if (m_pGameScene == pGameScene) return; // ���Ȃ�

	// �I�u�W�F�N�g�̉������
	Object::ReleaseAll();

	// �G�t�F�N�g�̉������
	EffectManager::ReleaseAll();

	// �e�N�X�`���̉������
	TextureManager::ReleaseAll();

	// ���݂̃Q�[���V�[���̏I������
	m_pGameScene->Release();

	// �V�����Q�[���V�[�����擾
	m_pGameScene = pGameScene;

	// �V�����Q�[���V�[���̏�����
	m_pGameScene->Init();

}


//-----------------------------------------------------------------------------
//	�`��
//-----------------------------------------------------------------------------
void GameManager::Draw()
{
	// DirectX�`��J�n
	Renderer::DrawBegin();

	// �I�u�W�F�N�g�̕`�揈��
	Object::DrawAll();
	
	// �G�t�F�N�g�̕`�揈��
	EffectManager::DrawAll();

	// �Q�[���V�[��
	m_pGameScene->Draw();

	// �t�F�[�h�̕`��
	m_pFade->Draw();

	// �`��
#ifdef _DEBUG
	if (m_pInput->GetKeyboardTrigger(BUTTON_DEBUG_DRAW)) {
		_drawDebugInfo ^= 1;
	}

	if (_drawDebugInfo) {
		OX::DebugFont::print(0, 0, 0xffff0000, "fps : %d", GetFPS());
		OX::DebugFont::draw(Renderer::GetDevice());
	}
#endif

	// DirectX�`��I��
	Renderer::DrawEnd();

	// �o�b�t�@�̃N���A
	OX::DebugFont::clear();

}

