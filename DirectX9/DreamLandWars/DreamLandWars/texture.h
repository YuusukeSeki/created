//*****************************************************************************
//	
//		�e�N�X�`���[
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"
#include "TextureManager.h"



class Texture : public TextureManager
{
public:
	// �R���X�g���N�^ / �f�X�g���N�^
	~Texture();

	// ��{�I�Ȋ֐�
	static Texture* Create(const char* texPass);
	void Release();
	void LoadTexture(const char* texPass);
	void UnLoad();

	// �擾
	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTexture; }


protected:
	Texture(const char* texPass);


private:
	// �R���X�g���N�^ / �f�X�g���N�^
	Texture(){}

	// �ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture;


};

#endif

