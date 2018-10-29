//*****************************************************************************
//
//		��
//												Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"
#include "ObjectCube.h"

class Wall : public ObjectCube
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	Wall();
	Wall(Object::TYPE type);
	virtual ~Wall();


	//----- ��{�I�Ȋ֐� -----
	static Wall* Create(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Init(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

};

#endif

