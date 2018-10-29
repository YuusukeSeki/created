//*****************************************************************************
//	
//		�e�N�X�`���}�l�[�W���[
//												Author : Yusuke Seki
//*****************************************************************************
#include "TextureManager.h"

//----- �ÓI�����o�ϐ������� -----
TextureManager* TextureManager::m_pTextureArray[TextureManager::NUM_TEXTURE] = {};



//-----------------------------------------------------------------------------
//	�R���X�g���N�^
//-----------------------------------------------------------------------------
TextureManager::TextureManager()
{
	for (int i = 0; i < NUM_TEXTURE; i++) {
		if (m_pTextureArray[i] == nullptr) {
			m_pTextureArray[i] = this;

			return;
		}
	}

	_MSGERROR("�e�N�X�`�����i�[����󂫔z�񂪂���܂���", "");

}


//-----------------------------------------------------------------------------
//	��������F��
//-----------------------------------------------------------------------------
void TextureManager::Release()
{
	for (int i = 0; i < NUM_TEXTURE; i++) {
		if (m_pTextureArray[i] == this) {
			UnLoad();
			delete this;
			m_pTextureArray[i] = nullptr;

			break;
		}
	}
}


//-----------------------------------------------------------------------------
//	�I������
//-----------------------------------------------------------------------------
void TextureManager::UnLoadAll()
{
	for (int i = 0; i < NUM_TEXTURE; i++) {
		if (m_pTextureArray[i] != nullptr) {
			m_pTextureArray[i]->UnLoad();
		}
	}
}


//-----------------------------------------------------------------------------
//	�������
//-----------------------------------------------------------------------------
void TextureManager::ReleaseAll()
{
	for (int i = 0; i < NUM_TEXTURE; i++) {
		if (m_pTextureArray[i] != nullptr) {
			m_pTextureArray[i]->Release();
		}
	}
}


//-----------------------------------------------------------------------------
//	
//-----------------------------------------------------------------------------
TextureManager* TextureManager::GetTexture(int arrayIdx)
{
	// ���̂�������� nullptr ��Ԃ�
	if (m_pTextureArray[arrayIdx] == nullptr) return nullptr;

	// ��v�����̂Ń|�C���^��Ԃ�
	return m_pTextureArray[arrayIdx];

}


