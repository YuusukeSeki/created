//*****************************************************************************
//	
//		���C���Q�[��
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _MAINGAME_H_
#define _MAINGAME_H_

#include "main.h"
#include "GameScene.h"
#include "list_LoadTexture_MainGame.h"

// FW
class Camera;
class Light;
class Texture;

// Object
class Player;
class Field;
class SkyBox;
class DrawRange;
class Tower;
class Castle;
class Wall;

// UI
class Timer;
class Score;
class FrameBorder;

// etc...
class Object2D;


class MainGame : public GameScene
{
public:
	//----- ��{�I�Ȋ֐� -----
	void Init();
	void Uninit();
	GameScene* Update();
	void Draw();
	void Release();

	//----- �f�[�^��Ԃ����� -----
	static Field* GetField() { return m_pField; }																// �t�B�[���h�̎擾
	static SkyBox* GetSkyBox() { return m_pSkyBox; }															// �X�J�C�{�b�N�X�̎擾
	static Camera* GetCamera(int index) { return m_pCamera[index]; }											// �J�����̎擾
	static Texture* GetTexture(List_LoadTexture_MainGame::TEXTURE_NAME texName) { return m_pTexture[texName]; }	// �e�N�X�`���[�̎擾
	static Wall* GetWall(int index);																			// �Ǐ��̎擾

private:
	//----- �֐� -----
	bool Start_NextScene();	// true �Ŏ��̃V�[����
	void InputManage();		// ���͐���

	//----- �f�[�^ -----
	static const int NUM_WALL = 4;	// �ǂ̐�
	static const int NUM_TOWER = 4;	// ���̐�

	static Field* m_pField;			// �t�B�[���h
	static Wall* m_pWall[NUM_WALL];	// ��
	static SkyBox* m_pSkyBox;		// �X�J�C�{�b�N�X
	static Camera* m_pCamera[2];	// �J����
	Light* m_pLight;				// ���C�g
	Player* m_pPlayer;				// �v���C���[
	DrawRange* m_pDrawRange;		// �˒��͈�
	Score* m_pScore;				// �X�R�A
	Tower* m_pTower;				// ��
	Castle* m_pCastle;				// ��
	FrameBorder* m_pFrameBorder;	// �g��
	Object2D* _tutorial;

	static Texture* m_pTexture[List_LoadTexture_MainGame::TEXTURE_NAME::__LOADTEXTURE_MAX];	// �e�N�X�`��

	// �f�o�b�O�p�؂�ւ��X�C�b�`�i�J���� �� �v���C���[�j
	int _switchControl;

};

#endif
