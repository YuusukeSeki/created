//*****************************************************************
//
//		�X�J�C�{�b�N�X
//										Autohr : Yusuke Seki
//
//*****************************************************************
#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "main.h"
#include "scene.h"
#include "Object.h"
#include "texture.h"



class SkyBox : public Object
{
public:
	// �R���X�g���N�^ / �f�X�g���N�^
	virtual ~SkyBox();

	// ��{�I�Ȋ֐�
	static SkyBox* Create(D3DXVECTOR3 pos, float width);
	HRESULT Init(D3DXVECTOR3 pos, float width);
	void Uninit();
	void Update();
	void Draw();

	// ����
	void MovePos(D3DXVECTOR3 move);

	// �ݒ�
	void SetPos(D3DXVECTOR3 pos);
	void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }
	

protected:


private:
	// �R���X�g���N�^ / �f�X�g���N�^
	SkyBox(){}
	SkyBox(Object::TYPE type);

	// �֐�
	void MakeVertexBuf();

	// �ϐ�
	D3DXMATRIX m_mtxWorld; // ���[���h�s��
	float m_width;         // ��ӂ̒���

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	Texture* m_pTexture;                // �e�N�X�`��


};

#endif
