//*****************************************************************************
//	
//		�e�N�X�`���}�l�[�W���[
//												Author : Yusuke Seki
//*****************************************************************************
#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "main.h"


class TextureManager
{
public:
	// �R���X�g���N�^ / �f�X�g���N�^
	TextureManager();
	~TextureManager() {}

	// ��{�I�Ȋ֐�
	void Release(void);
	virtual void LoadTexture(const char* texPass) = 0;
	virtual void UnLoad() = 0;

	// ALL
	static void UnLoadAll();
	static void ReleaseAll();

	// �擾
	static TextureManager* GetTexture(int arrayIdx);


protected:


private:
	// �萔
	static const int NUM_TEXTURE = 0xff;

	// �ϐ�
	static TextureManager* m_pTextureArray[NUM_TEXTURE];

};

#endif

