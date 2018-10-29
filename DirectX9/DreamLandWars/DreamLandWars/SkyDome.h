//*****************************************************************************
//
//		�X�J�C�h�[��
//													Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _SKYDOME_H_
#define _SKYDOME_H_

#include "main.h"
#include "ObjectModel.h"


class SkyDome : public ObjectModel
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	SkyDome();
	SkyDome(Object::TYPE type);
	virtual ~SkyDome();

	
	//----- ��{�I�Ȋ֐� -----
	static SkyDome* Create(D3DXVECTOR3& position, const char* FileName);
	virtual void Init(D3DXVECTOR3& position, const char* FileName);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

};

#endif

