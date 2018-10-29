//*****************************************************************************
//
//		�^�C�g�� : �e�N�X�`���ǂݍ��ݕ\
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _LIST_LOADTEXTURE_TITLE_H_
#define _LIST_LOADTEXTURE_TITLE_H_

#include "main.h"
#include "texture.h"


class List_LoadTexture_Title
{
public:
	// �萔
	enum TEXTURE_NAME {
		TEXT_TEXNAME,				// �啶��
		TEXTBORDER_TEXNAME,			// �啶���g
		TEXTSMALL_TEXNAME,			// ������
		TEXTSMALLBORDER_TEXNAME,	// �������g
		TUTORIAL01,
		TUTORIAL02,

		__LOADTEXTURE_MAX,	// �� �Ǎ��ő吔
	};

	// �֐�
	static void LoadTextureAll(Texture** ppTexture) {
		// �Ǎ��ރe�N�X�`���p�X��
		List texPassList[List_LoadTexture_Title::__LOADTEXTURE_MAX] = {
			"data/texture/text_alphabet02.png", // ����
			"data/texture/text_alphabet04.png", // �����g
			"data/texture/text_alphabet_S02.png", // ����
			"data/texture/text_alphabet_S03.png", // �����g
			"data/texture/tutrorial01.png", // �����g
			"data/texture/tutrorial02.png", // �����g
		};


		// �Ǎ�
		for (int i = 0; i < List_LoadTexture_Title::__LOADTEXTURE_MAX; i++) {
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


