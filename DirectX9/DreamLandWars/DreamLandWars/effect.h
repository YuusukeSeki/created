//*****************************************************************************
//	
//		�G�t�F�N�g
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _EFFECT_H_
#define _EFFECT_H_

//----- �C���N���[�h�t�@�C�� -----
#include "main.h"
#include "scene.h"


//----- �O���錾 -----
class Texture;


//----- �N���X�̒�` -----
class Effect : public Scene
{
public:
	// �R���X�g���N�^ / �f�X�g���N�^
	virtual ~Effect();

	// ��{�I�Ȋ֐�
	static	Effect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 scl); // ���̂̐���
	virtual HRESULT	Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	// �ݒ�
	bool SetEffect(D3DXVECTOR3 pos);
	void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }

	// �擾


protected:
	// �R���X�g���N�^ / �f�X�g���N�^
	Effect() {}
	Effect(int priority, TYPE type);


private:
	// �萔
	static const int ELASE_TIME = 240;

	// �ϐ�
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_size, m_rot, m_scl, m_move;
	Scene::Color m_color;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	Texture* m_pTexture;

	float m_radius, m_angle, m_colorAlphaValue, m_radiusValue;
	int   m_life;
	bool  m_bUse;

};

#endif

