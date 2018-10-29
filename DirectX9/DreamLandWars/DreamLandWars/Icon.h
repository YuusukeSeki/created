//*****************************************************************************
//
//		�A�C�R��
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _ICON_H_
#define _ICON_H_

#include "main.h"
#include "ObjectBillboard.h"
#include "ObjectModel.h"

class Camera;


class Icon : public ObjectBillboard
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	Icon();
	~Icon();

	//----- ��{�I�Ȋ֐� -----
	static Icon* Create(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera, Object::GROUP group);
	void Init(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera, Object::GROUP group);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//----- �������� -----

	//----- �ݒ菈�� -----

	//----- �f�[�^��Ԃ����� -----


private:
	//----- �f�[�^ -----

};

#endif

