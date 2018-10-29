//*****************************************************************************
//
//		�h���[�V���b�g�˒��͈�
//												Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _DRAWRANGE_H_
#define _DRAWRANGE_H_

#include "main.h"
#include "Object3D.h"

class Player;


class DrawRange : public Object3D
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	DrawRange();
	DrawRange(Object::TYPE type);
	virtual ~DrawRange();


	//----- ��{�I�Ȋ֐� -----
	static DrawRange* Create(Player* pPlayer);
	virtual void Init(Player* pPlayer);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);


	//----- �������� -----

	//----- �ݒ菈�� -----
	void SetPlayer_DrawRange(Player* pPlayer) { m_pPlayer = pPlayer; }	// �e�v���C���[�̐ݒ�

	//----- �f�[�^��Ԃ����� -----


private:
	//----- �f�[�^ -----
	Player* m_pPlayer;	// �e�v���C���[

};

#endif

