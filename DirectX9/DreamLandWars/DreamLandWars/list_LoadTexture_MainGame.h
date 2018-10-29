//*****************************************************************************
//
//		MainGame : �e�N�X�`���ǂݍ��ݕ\
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _LIST_LOADTEXTURE_MAINGAME_H_
#define _LIST_LOADTEXTURE_MAINGAME_H_

#include "main.h"
#include "texture.h"


class List_LoadTexture_MainGame
{
public:
	// �萔
	enum TEXTURE_NAME {
		FIELD_TEXNAME,			// �n��
		SKYBOX_TEXNAME,			// �X�J�C�{�b�N�X
		BULLET_TEXNAME,			// �e
		NUMBER_TEXNAME,			// ����
		COLON_TEXNAME,			// �R����
		DRAWLINE_TEXNAME,		// �`���
		EFFECT_TEXNAME,			// �G�t�F�N�g
		FRAMEBORDER_TEXNAME,	// �g��
		LABEL_YOURTEAM_TEXNAME,	// "YOUR TEAM"
		LABEL_ENEMY_TEXNAME,	// "ENEMY"
		TEAMGAUGE_TEXNAME,		// �`�[���Q�[�W
		LOCKON_INNERLINE,		// �Ə��F����
		LOCKON_OUTLINE,			// �Ə��F�O��
		LOCKON_HOLD,			// �Ə��F"HOLD"
		ICON_TOWER,				// �A�C�R���F��
		ICON_CASTLE,			// �A�C�R���F��
		WALL_TEXNAME,			// ��
		TUTORIAL,

		__LOADTEXTURE_MAX,  // �� �Ǎ��ő吔
	};


	// �֐�
	static void LoadTextureAll(Texture** ppTexture) {
		// �Ǎ��ރe�N�X�`���p�X��
		List texPassList[List_LoadTexture_MainGame::__LOADTEXTURE_MAX] = {
			//"data/texture/debugTexture01.jpg",			// �n��
			"data/texture/MainGame/ground03.jpg",			// �n��
			"data/texture/MainGame/skybox001.png",			// �X�J�C�{�b�N�X
			"data/texture/MainGame/kobeni1.png",			// �e
			"data/texture/MainGame/numberFile03.png",		// ����
			"data/texture/MainGame/numberFile04.png",		// �R����
			"data/texture/MainGame/drawLine01.png",			// �`���
			"data/texture/MainGame/effect000.jpg",			// �G�t�F�N�g
			"data/texture/MainGame/FrameBorder02.png",		// �g��
			"data/texture/MainGame/Text_YourTeam01.png",	// "YOUR TEAM"
			"data/texture/MainGame/Text_Enemy01.png",		// "ENEMY"
			"data/texture/MainGame/TeamGauge01.png",		// �`�[���Q�[�W
			"data/texture/MainGame/Lock-On02.png",			// �Ə��F����
			"data/texture/MainGame/Lock-On01.png",			// �Ə��F�O��
			"data/texture/MainGame/Hold01.png",				// �Ə��F"HOLD"
			"data/texture/MainGame/fortress_icon01.png",	// �A�C�R���F��
			"data/texture/MainGame/castle_icon01.png",		// �A�C�R���F��
			"data/texture/MainGame/wall01.jpg",				// ��
			"data/texture/tutrorial03.png",					// �����g

		};


		// �Ǎ�
		for (int i = 0; i < List_LoadTexture_MainGame::__LOADTEXTURE_MAX; i++) {
			ppTexture[i] = Texture::Create(texPassList[i].texPass);

		}

	}

private:
	// �Ǎ��p�̍\���̒�`
	struct List {
		char texPass[256];
	};

};

#endif


