//*****************************************************************************
//
//		�Q�[���^�C�g��
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _GAMETITLE_H_
#define _GAMETITLE_H_

#include "main.h"
#include "Object3D_Quaternion.h"


class GameTitle : public Object3D_Quaternion
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	GameTitle();
	GameTitle(Object::TYPE type);
	virtual ~GameTitle();
	
	//----- ��{�I�Ȋ֐� -----
	static GameTitle* Create(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Init(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:


};

#endif
