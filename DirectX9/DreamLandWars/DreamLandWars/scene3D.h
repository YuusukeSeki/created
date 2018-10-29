//*****************************************************************************
//
//		3D�|���S��
//												Autohr	:	Yusuke Seki
//*****************************************************************************
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"
#include "texture.h"


class Scene3D : public Scene
{
public:
	// �R���X�g���N�^ / �f�X�g���N�^
	virtual ~Scene3D();

	// ��{�I�Ȋ֐�
	static	Scene3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 scl); // ���̂̐���
	virtual HRESULT	Init( D3DXVECTOR3 pos , D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 scl );
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	// ����
	void MoveSize(D3DXVECTOR3 move);
	void MoveRot(D3DXVECTOR3 move) { m_rot += move; }
	void MoveScl(D3DXVECTOR3 move) { m_scl += move; }

	// �ݒ�
	void SetSize(D3DXVECTOR3 size);
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetScl(D3DXVECTOR3 scl) { m_scl = scl; }
	void SetNormal(D3DXVECTOR3 normalLT, D3DXVECTOR3 normalRT, D3DXVECTOR3 normalLB, D3DXVECTOR3 normalRB);
	void SetColor(unsigned int color);
	void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }
	void SetDraw(bool bDraw) { m_bDraw = bDraw; }

	// �擾
	D3DXVECTOR3 GetSize(void)   { return m_size; }
	D3DXVECTOR3 GetRotate(void) { return m_rot;  }
	D3DXVECTOR3 GetScall(void)  { return m_scl;  }
	Texture* GetTexture() { return m_pTexture; }


protected:
	// �R���X�g���N�^ / �f�X�g���N�^
	Scene3D() {}
	Scene3D(int priority, TYPE type);


private:
	// �ϐ�
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scl;
	Color m_color;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	Texture* m_pTexture;

	bool m_bDraw;

};

#endif

