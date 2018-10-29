//*****************************************************************************
//	
//		���C���Q�[��
//													Author : Yusuke Seki
//*****************************************************************************
// base
#include "MainGame.h"
#include "GameManager.h"
#include "result.h"
#include "Title.h"

// FW
#include "fade.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "renderer.h"

// Object
#include "player.h"
#include "Soldier.h"
#include "DrawRange.h"
#include "tower.h"
#include "castle.h"
#include "field.h"
#include "skybox.h"
#include "Wall.h"

// UI
#include "timer.h"
#include "score.h"
#include "FrameBorder.h"
#include "TeamGaugeManager.h"
#include "TeamGauge.h"
#include "Hold.h"

// resource
#include "texture.h"
#include "list_LoadTexture_MainGame.h"
#include "ModelData.h"

// etc...
#include "ObjectModel.h"
#include "Object2D.h"

#include "EventButton.h"


//----- �}�N����` -----
// ���M�����[�V�����p���͐���
#define _INPUT_REGULATION		// �R�����g�A�E�g�Ń��M�����[�V�����p��������O


//----- �ÓI�����o�ϐ������� -----
Field*     MainGame::m_pField          = nullptr;	// �n��
SkyBox*    MainGame::m_pSkyBox         = nullptr;	// �w�i
Wall*	   MainGame::m_pWall[]         = {};		// ��
Camera*    MainGame::m_pCamera[]       = {};		// �J����
Texture*   MainGame::m_pTexture[]      = {};		// �e�N�X�`���[


//-----------------------------------------------------------------------------
//	����������
//-----------------------------------------------------------------------------
void MainGame::Init()
{
	// Load Texture
	{
		List_LoadTexture_MainGame::LoadTextureAll(m_pTexture);
	}

	// Create Camera
	{
		m_pCamera[0] = Camera::Create(D3DXVECTOR3(0.f, 200.f, -110.f), D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f), 1.f, 1000.f);
	}

	// Create Light
	{
		m_pLight = Light::Create();
		m_pLight->SetVectorDirection(D3DXVECTOR3(0.f, -1, 0.f));
	}


	//----- Create Object -----
	{
		// Create Field
		{
			m_pField = Field::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(750.f, 0, 3000.f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), 4, 4);
			m_pField->SetTexture(m_pTexture[List_LoadTexture_MainGame::TEXTURE_NAME::FIELD_TEXNAME]);
		}

		// Create Sky_Box
		{
			m_pSkyBox = SkyBox::Create(D3DXVECTOR3(0, 700, 0), 3500.f);
			m_pSkyBox->SetTexture(m_pTexture[List_LoadTexture_MainGame::TEXTURE_NAME::SKYBOX_TEXNAME]);
		}

		// Create Wall
		{
			// LeftWall
			D3DXVECTOR3 setSize = D3DXVECTOR3(	m_pField->GetSize().x * 0.05f, m_pField->GetSize().z * 0.03f, m_pField->GetSize().z);
			D3DXVECTOR3 setPos  = D3DXVECTOR3(	m_pField->GetPosition().x - m_pField->GetHalfSize().x + setSize.x * 0.5f,
												m_pField->GetPosition().y + setSize.y * 0.5f,
												m_pField->GetPosition().z);
			m_pWall[0] = Wall::Create(setPos, setSize);
			m_pWall[0]->SetTexture(m_pTexture[List_LoadTexture_MainGame::TEXTURE_NAME::WALL_TEXNAME]->GetTexture());

			// RightWall
			setPos  = D3DXVECTOR3(	m_pField->GetPosition().x + m_pField->GetHalfSize().x - setSize.x * 0.5f,
									m_pField->GetPosition().y + setSize.y * 0.5f,
									m_pField->GetPosition().z);
			m_pWall[1] = Wall::Create(setPos, setSize);
			m_pWall[1]->SetTexture(m_pTexture[List_LoadTexture_MainGame::TEXTURE_NAME::WALL_TEXNAME]->GetTexture());

			// FrontWall
			setSize = D3DXVECTOR3(	m_pField->GetSize().x, m_pField->GetSize().z * 0.03f, m_pField->GetSize().x * 0.05f);
			setPos  = D3DXVECTOR3(	m_pField->GetPosition().x,
									m_pField->GetPosition().y + setSize.y * 0.5f,
									m_pField->GetPosition().z - m_pField->GetHalfSize().z + setSize.z * 0.5f);
			m_pWall[2] = Wall::Create(setPos, setSize);
			m_pWall[2]->SetTexture(m_pTexture[List_LoadTexture_MainGame::TEXTURE_NAME::WALL_TEXNAME]->GetTexture());

			// BackWall
			setPos  = D3DXVECTOR3(	m_pField->GetPosition().x + m_pField->GetHalfSize().x - setSize.x * 0.5f,
									m_pField->GetPosition().y + setSize.y * 0.5f,
									m_pField->GetPosition().z + m_pField->GetHalfSize().z - setSize.z * 0.5f);
			m_pWall[3] = Wall::Create(setPos, setSize);
			m_pWall[3]->SetTexture(m_pTexture[List_LoadTexture_MainGame::TEXTURE_NAME::WALL_TEXNAME]->GetTexture());
		}

		// Create Cast
		{
			m_pPlayer = Player::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pCamera[0], MODELDATA_PLAYER, Player::CHARACTER::CHARACTER_KIBITSU);
			m_pPlayer->SetGroup(Object::GROUP::GROUP_A);
		}

		//// Create Range of Draw
		//{
		//	m_pDrawRange = DrawRange::Create(m_pPlayer);
		//	m_pDrawRange->SetTexture(m_pTexture[List_LoadTexture_MainGame::DRAWLINE_TEXNAME]->GetTexture());
		//	m_pDrawRange->SetColor(0xffffff80);
		//}

		//// Create Tower
		//{
		//	// Side Enemy
		//	D3DXVECTOR3 pos = m_pField->GetPosition();											// �t�B�[���h���W��ɕ␳
		//	float halfX = m_pField->GetHalfSize().x * 0.5f;										// �t�B�[���h�T�C�Y��ɕ␳
		//	float halfZ = m_pField->GetHalfSize().z * 0.5f;										// �t�B�[���h�T�C�Y��ɕ␳
		//	D3DXVECTOR3 setPos = D3DXVECTOR3(pos.x - halfX, 0, pos.z + halfZ - halfZ * 0.5f);	// ����ݒ肷����W

		//	for (int i = 0; i < NUM_TOWER; i++)
		//	{
		//		m_pTower = Tower::Create(setPos, MODELDATA_TOWER, Object::GROUP_B);
		//		m_pTower->SetRotate(D3DXVECTOR3(0, D3DXToRadian(180), 0));
		//		m_pTower->SetVecZ(D3DXVECTOR3(0, 0, -1));

		//		// ����������ƑO�ɏo��
		//		if (i <= 1)
		//			m_pTower->MovePosition(D3DXVECTOR3(0, 0, -m_pField->GetSize().z * 0.05f));
		//		else
		//			m_pTower->MovePosition(D3DXVECTOR3(0, 0, -m_pField->GetSize().z * 0.12f));

		//		setPos.x *= -1;

		//		if (i == 1)
		//			setPos.z += halfZ;

		//	}

		//	// Side Your Team
		//	setPos = D3DXVECTOR3(pos.x - halfX, 0, pos.z - halfZ + halfZ * 0.5f);	// ����ݒ肷����W

		//	for (int i = 0; i < NUM_TOWER; i++)
		//	{
		//		m_pTower = Tower::Create(setPos, MODELDATA_TOWER, Object::GROUP_A);
		//		if (i <= 1)
		//			m_pTower->MovePosition(D3DXVECTOR3(0, 0, m_pField->GetSize().z * 0.05f));
		//		else
		//			m_pTower->MovePosition(D3DXVECTOR3(0, 0, m_pField->GetSize().z * 0.12f));

		//		setPos.x *= -1;
		//		if (i == 1) setPos.z -= halfZ;
		//	}
		//}

		//// Create Castle
		//{
		//	// Side Enemy
		//	m_pCastle = Castle::Create(MODELDATA_CASTLE, Object::GROUP_B);

		//	// Side Your Team
		//	m_pCastle = Castle::Create(MODELDATA_CASTLE, Object::GROUP_A);

		//}

		//// Create Buffer of Soldier
		//{
		//	for (int i = 0; i < 256; i++)
		//		Soldier::Create(D3DXVECTOR3(0, 0, 0), MODELDATA_SOLDIER);
		//}

		// Create Point of Healing
		//Object3D* pObject3D = Object3D::Create(D3DXVECTOR3(0, 50, -7500), D3DXVECTOR3(750, 0, 750));
		//pObject3D->SetNormal(D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 1, 0));
		//pObject3D->SetColor(0x00ff0080);
		//pObject3D->SetTexture(m_pTexture[List_LoadTexture_MainGame::DRAWLINE_TEXNAME]->GetTexture());

		//pObject3D = Object3D::Create(D3DXVECTOR3(-2000, 50, -6000), D3DXVECTOR3(750, 0, 750));
		//pObject3D->SetNormal(D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 1, 0));
		//pObject3D->SetColor(0x00ff0080);
		//pObject3D->SetTexture(m_pTexture[List_LoadTexture_MainGame::DRAWLINE_TEXNAME]->GetTexture());

		//pObject3D = Object3D::Create(D3DXVECTOR3(2000, 50, -6000), D3DXVECTOR3(750, 0, 750));
		//pObject3D->SetNormal(D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 1, 0));
		//pObject3D->SetColor(0x00ff0080);
		//pObject3D->SetTexture(m_pTexture[List_LoadTexture_MainGame::DRAWLINE_TEXNAME]->GetTexture());


		// Create Point of Speedy

		// Create Forest

		// example
		//float scall = 10;

		//ObjectModel* pObj = ObjectModel::Create(D3DXVECTOR3(0, 0, 30), MODELDATA_SOLDIER02);
		//pObj->SetScale(D3DXVECTOR3(scall, scall, scall));
		//pObj->SetColor(0xff0000ff);

	}


	// ����UI�̐���
	D3DXVECTOR3 size = D3DXVECTOR3((SCREEN_WIDTH * 0.42f), (SCREEN_HEIGHT * 0.08f), 0);
	D3DXVECTOR3 pos  = D3DXVECTOR3((SCREEN_WIDTH * 0.22f), (SCREEN_HEIGHT * 0.06f), 0);
	m_pFrameBorder = FrameBorder::Create(pos, size);
	m_pFrameBorder->SetTexture(m_pTexture[List_LoadTexture_MainGame::FRAMEBORDER_TEXNAME]->GetTexture());
	
	// �X�R�A�̐���
	size = D3DXVECTOR3(600.f * 0.4f, 100.f * 0.4f, 0.f);
	pos  = D3DXVECTOR3(SCREEN_WIDTH - size.x * 0.55f, SCREEN_HEIGHT - size.y * 0.75f, 0.f);
	m_pScore = Score::Create(pos, size, 6);
	m_pScore->SetTexture(m_pTexture[List_LoadTexture_MainGame::TEXTURE_NAME::NUMBER_TEXNAME]->GetTexture());

	_tutorial = Object2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.8f, 0), D3DXVECTOR3(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.15f, 0));
	_tutorial->SetTexture(m_pTexture[List_LoadTexture_MainGame::TUTORIAL]->GetTexture());
	
	// �f�o�b�O�p�؂�ւ��X�C�b�`�i�J���� �� �v���C���[�j
	_switchControl = 1;


	m_pFrameBorder->GetTimer()->SwitchTimer();


	//ObjectModel* objModel;
	//pos = D3DXVECTOR3(0, 10, 10);
	//objModel = ObjectModel::Create(pos, MODELDATA_HEAD);
	//pos.z += 20;
	//objModel = ObjectModel::Create(pos, MODELDATA_BODY);
	//pos.z += 20;
	//objModel = ObjectModel::Create(pos, MODELDATA_RARM);
	//pos.z += 20;
	//objModel = ObjectModel::Create(pos, MODELDATA_RARM_EDGE);
	//pos.z += 20;
	//objModel = ObjectModel::Create(pos, MODELDATA_LARM);
	//pos.z += 20;
	//objModel = ObjectModel::Create(pos, MODELDATA_LARM_EDGE);
	//pos.z += 20;
	//objModel = ObjectModel::Create(pos, MODELDATA_RLEG);
	//pos.z += 20;
	//objModel = ObjectModel::Create(pos, MODELDATA_RLEG_EDGE);
	//pos.z += 20;
	//objModel = ObjectModel::Create(pos, MODELDATA_LLEG);
	//pos.z += 20;
	//objModel = ObjectModel::Create(pos, MODELDATA_LLEG_EDGE);

}

//-----------------------------------------------------------------------------
//	�I������
//-----------------------------------------------------------------------------
void MainGame::Uninit()
{
	// ���C�g
	m_pLight->Release();
	m_pLight = nullptr;

	// �J����
	m_pCamera[0]->Release();
	m_pCamera[0] = nullptr;

	// �X�R�A
	m_pScore->Release();

}

//-----------------------------------------------------------------------------
//	�X�V����
//-----------------------------------------------------------------------------
GameScene* MainGame::Update()
{
	// ���͐���
	InputManage();

	// �J�������v���C���[�ɒǏ]������F�v�񋓑�
	if (_switchControl) {
		D3DXVECTOR3 pos = m_pPlayer->GetPosition();
		pos.z += 0.f;
		D3DXVECTOR3 move = m_pCamera[0]->SetPosAt(pos);
	}

	// �X�J�C�{�b�N�X���J�����ɒǏ]������F�v�񋓑�
	//m_pSkyBox->MovePos(move);

	// �X�R�A
	m_pScore->Update();
	m_pScore->SetScore(m_pPlayer->GetScore_CrushSoldier());

	// �J����
	m_pCamera[0]->Update();

	// ���C�g
	m_pLight->Update();

	// ���̃V�[���ɍs���H
	if(GameManager::GetFade()->Finish_FadeOut()){ // �s��
		// �Q�[���V�[�������U���g��
		//return new Result;
		return new Title;
	}
	else {	// �s���Ȃ�
		// ���C���Q�[���̏����𑱍s����
		return this;
	}
}

//-----------------------------------------------------------------------------
//	�`�揈��
//-----------------------------------------------------------------------------
void MainGame::Draw()
{
}

//-----------------------------------------------------------------------------
//	true�Ŏ��̃V�[���ɑJ��
//-----------------------------------------------------------------------------
bool MainGame::Start_NextScene()
{
	// ���̓f�o�C�X�̎擾
	Input* pInput = GameManager::GetInput();

	// �t�F�[�h��Ԃ̎擾
	Fade* pFade = GameManager::GetFade();


	// �X�y�[�X�[�L�[�����ꂽ�H
	if (pInput->GetKeyboardTrigger(DIK_SPACE)) {
		// �t�F�[�h�A�E�g�J�n
		pFade->Start_FadeOut();
	}

	// �t�F�[�h�A�E�g�I�������H
	if (pFade->Finish_FadeOut()) {
		// �Q�[���V�[�������U���g��
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//	
//-----------------------------------------------------------------------------
void MainGame::Release()
{
	// �I������
	Uninit();

	// �������̉��
	delete this;
}

//-----------------------------------------------------------------------------
//	
//-----------------------------------------------------------------------------
void MainGame::InputManage()
{
	// ���̓f�o�C�X�̎擾
	Input* pInput = GameManager::GetInput();

	// �X�C�b�`�̐؂�ւ�
	if (pInput->GetKeyboardTrigger(BUTTON_DEBUG_SWITCH_CTRL)) _switchControl ^= 1;


	// �J���� 
	if(!_switchControl)
	{
		const float MOVE = 10.0f;
		const float ROT = 0.03f;
		
		// �ړ�
		if (pInput->GetKeyboardPress(DIK_W)) m_pCamera[0]->MovePosEye_Z( MOVE); // �O
		if (pInput->GetKeyboardPress(DIK_S)) m_pCamera[0]->MovePosEye_Z(-MOVE); // ��
		if (pInput->GetKeyboardPress(DIK_A)) m_pCamera[0]->MovePosEye_X(-MOVE); // ��
		if (pInput->GetKeyboardPress(DIK_D)) m_pCamera[0]->MovePosEye_X( MOVE); // �E

		// ��]
		if (pInput->GetKeyboardPress(DIK_Q)) m_pCamera[0]->MoveRotEye(-ROT);  // �����v����
		if (pInput->GetKeyboardPress(DIK_E)) m_pCamera[0]->MoveRotEye( ROT);  // ���v����

		// ����
		if (pInput->GetKeyboardPress(DIK_Z)) m_pCamera[0]->MoveTurnEye(-ROT); // �����v����
		if (pInput->GetKeyboardPress(DIK_C)) m_pCamera[0]->MoveTurnEye( ROT); // ���v����

	}

	// �v���C���[
	{
		// �W���C�X�e�B�b�N�A�����X���̎擾
		D3DXVECTOR3 lAxis = pInput->GetJoystickLeftAxis();
		lAxis.y *= -1;
		// �덷�C��
		if (fabs(lAxis.x) < 50 && fabs(lAxis.y) < 50) {
			lAxis.x = 0;
			lAxis.y = 0;
		}


		// �ړ� : Joystick_LAxis �X��
		m_pPlayer->Run(lAxis.x, lAxis.y);

		// ��� : Joystick_Trigger L1�{�^��
		if (pInput->GetJoystickTrigger(Input::JOYSTICKBUTTON005)) m_pPlayer->Avoid(lAxis.x, lAxis.y);

		// �ً}��� : Joystick_Trigger L1�{�^���_�u���N���b�N
		if (pInput->GetJoystickWTrigger(Input::JOYSTICKBUTTON005)) m_pPlayer->EmAvoid(lAxis.x, lAxis.y);

		// SS���� : Mouse_Press ���{�^��
		if (pInput->GetMouseTrigger(Input::MOUSEBUTTON_LEFT)) m_pPlayer->STReady();

		// SS���� : Mouse_Release ���{�^��
		if (pInput->GetMouseRelease(Input::MOUSEBUTTON_LEFT)) m_pPlayer->STShot();

		// DS���� : Mouse_Press �E�{�^��
		if (pInput->GetMousePress(Input::MOUSEBUTTON_RIGHT)) m_pPlayer->DRReady(pInput->GetMouseTrigger(Input::MOUSEBUTTON_RIGHT));

		// DS���� : Mouse_Release �E�{�^��
		if (pInput->GetMouseRelease(Input::MOUSEBUTTON_RIGHT)) m_pPlayer->DRShot(true);

		// ���_������ : Mouse_Press ���{�^��
		if (pInput->GetMousePress(Input::MOUSEBUTTON_LEFT)) m_pPlayer->BreakBasePoint();


#ifdef _INPUT_REGULATION
		//----- �����ȉ����M�����[�V�����p�L�[�{�[�h���쁥�� -----
		// �ړ�
		if (_switchControl) {
			if (pInput->GetKeyboardPress(DIK_W) && pInput->GetKeyboardPress(DIK_A)) m_pPlayer->Run(-1, +1);
			else if (pInput->GetKeyboardPress(DIK_W) && pInput->GetKeyboardPress(DIK_D)) m_pPlayer->Run(+1, +1);
			else if (pInput->GetKeyboardPress(DIK_S) && pInput->GetKeyboardPress(DIK_A)) m_pPlayer->Run(-1, -1);
			else if (pInput->GetKeyboardPress(DIK_S) && pInput->GetKeyboardPress(DIK_D)) m_pPlayer->Run(+1, -1);
			else if (pInput->GetKeyboardPress(DIK_W))                                    m_pPlayer->Run(0, +1);
			else if (pInput->GetKeyboardPress(DIK_S))                                    m_pPlayer->Run(0, -1);
			else if (pInput->GetKeyboardPress(DIK_A))                                    m_pPlayer->Run(-1, 0);
			else if (pInput->GetKeyboardPress(DIK_D))                                    m_pPlayer->Run(+1, 0);
		}

		// ���
		if (pInput->GetKeyboardTrigger(DIK_E)) {
			if      (pInput->GetKeyboardPress(DIK_W) && pInput->GetKeyboardPress(DIK_A)) m_pPlayer->Avoid(-1, +1);
			else if (pInput->GetKeyboardPress(DIK_W) && pInput->GetKeyboardPress(DIK_D)) m_pPlayer->Avoid(+1, +1);
			else if (pInput->GetKeyboardPress(DIK_S) && pInput->GetKeyboardPress(DIK_A)) m_pPlayer->Avoid(-1, -1);
			else if (pInput->GetKeyboardPress(DIK_S) && pInput->GetKeyboardPress(DIK_D)) m_pPlayer->Avoid(+1, -1);
			else if (pInput->GetKeyboardPress(DIK_W))                                    m_pPlayer->Avoid( 0, +1);
			else if (pInput->GetKeyboardPress(DIK_S))                                    m_pPlayer->Avoid( 0, -1);
			else if (pInput->GetKeyboardPress(DIK_A))                                    m_pPlayer->Avoid(-1,  0);
			else if (pInput->GetKeyboardPress(DIK_D))                                    m_pPlayer->Avoid(+1,  0);
			else                                                                         m_pPlayer->Avoid( 0,  0);
		}

		// �ً}���
		if (pInput->GetKeyboardWTrigger(DIK_E)) {
			if      (pInput->GetKeyboardPress(DIK_W) && pInput->GetKeyboardPress(DIK_A)) m_pPlayer->EmAvoid(-1, +1);
			else if (pInput->GetKeyboardPress(DIK_W) && pInput->GetKeyboardPress(DIK_D)) m_pPlayer->EmAvoid(+1, +1);
			else if (pInput->GetKeyboardPress(DIK_S) && pInput->GetKeyboardPress(DIK_A)) m_pPlayer->EmAvoid(-1, -1);
			else if (pInput->GetKeyboardPress(DIK_S) && pInput->GetKeyboardPress(DIK_D)) m_pPlayer->EmAvoid(+1, -1);
			else if (pInput->GetKeyboardPress(DIK_W))                                    m_pPlayer->EmAvoid( 0, +1);
			else if (pInput->GetKeyboardPress(DIK_S))                                    m_pPlayer->EmAvoid( 0, -1);
			else if (pInput->GetKeyboardPress(DIK_A))                                    m_pPlayer->EmAvoid(-1,  0);
			else if (pInput->GetKeyboardPress(DIK_D))                                    m_pPlayer->EmAvoid(+1,  0);
			else                                                                         m_pPlayer->EmAvoid( 0,  0);

		}

		//----- �������M�����[�V�����p���͐��䂱���܂Ł��� -----
#endif

	}


	// �^�C�}�[�𓮂��� / �~�߂�
	if (pInput->GetKeyboardTrigger(DIK_T)) m_pFrameBorder->GetTimer()->SwitchTimer();

	// �_����...
	if (pInput->GetKeyboardPress(DIK_P)) m_pScore->MoveScore(+50000); // �グ��
	if (pInput->GetKeyboardPress(DIK_O)) m_pScore->MoveScore(-50000); // ������

	// �h��Ԃ����[�h��...
	if (pInput->GetKeyboardPress(DIK_F1)) Renderer::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);	    // "�_" �ɕύX
	if (pInput->GetKeyboardPress(DIK_F2)) Renderer::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); // "���C���[�t���[��" �ɕύX
	if (pInput->GetKeyboardPress(DIK_F3)) Renderer::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);	    // "��" �ɕύX

	// �V�[���J��
	if (pInput->GetKeyboardTrigger(BUTTON_NEXT_SCENE)) GameManager::GetFade()->Start_FadeOut();

}

// �Ǐ��̎擾
Wall* MainGame::GetWall(int index)
{
	if (index < 0 || index >= NUM_WALL) {
		return nullptr;
	}

	return m_pWall[index];

}


