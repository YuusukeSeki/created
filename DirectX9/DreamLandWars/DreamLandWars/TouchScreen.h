//*****************************************************************************
//
//		�^�b�`�X�N���[��
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _TOUCHSCREEN_H_
#define _TOUCHSCREEN_H_

#include "main.h"
#include "Object3D_Quaternion.h"


class TouchScreen : public Object3D_Quaternion
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	TouchScreen();
	TouchScreen(Object::TYPE type);
	virtual ~TouchScreen();

	//----- ��{�I�Ȋ֐� -----
	static TouchScreen* Create(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Init(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:


};

#endif
