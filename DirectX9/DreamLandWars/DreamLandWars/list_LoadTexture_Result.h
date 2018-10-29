//*****************************************************************************
//
//		Result : �e�N�X�`���ǂݍ��ݕ\
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _LIST_LOADTEXTURE_RESULT_H_
#define _LIST_LOADTEXTURE_RESULT_H_

#include "main.h"
#include "texture.h"


class List_LoadTexture_Result
{
public:
	// �萔
	enum TEXTURE_NAME {
		BACKGROUND_TEXNAME, // �w�i

		__LOADTEXTURE_MAX,  // �� �Ǎ��ő吔
	};

	// �֐�
	static void LoadTextureAll(Texture** ppTexture) {
		// �Ǎ��ރe�N�X�`���p�X��
		List texPassList[List_LoadTexture_Result::__LOADTEXTURE_MAX] = {
			"data/TEXTURE/Result/resultBG01.jpg", // �w�i

		};


		// �Ǎ�
		for (int i = 0; i < List_LoadTexture_Result::__LOADTEXTURE_MAX; i++) {
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


