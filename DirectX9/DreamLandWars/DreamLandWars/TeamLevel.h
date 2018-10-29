//*****************************************************************************
//
//		�`�[�����x��
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _TEAMLEVEL_H_
#define _TEAMLEVEL_H_

#include "main.h"
#include "Object2D.h"


class TeamLevel : public Object2D
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	TeamLevel() {}
	TeamLevel(Object::TYPE type);
	~TeamLevel();

	//----- ��{�I�Ȋ֐� -----
	static TeamLevel* Create(D3DXVECTOR3& position, D3DXVECTOR3& size);
	void Init(D3DXVECTOR3& position, D3DXVECTOR3& size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Release(void) { delete this; }

	//----- �������� -----

	//----- �ݒ菈�� -----

	//----- �f�[�^��Ԃ����� -----


private:
	//----- �f�[�^ -----
	Object2D* m_pLabel_YOURTEAM;		// �y���x���z"Lv"
	Object2D* m_pLabel_ENEMY;			// �y���x���z"Lv"
	Object2D* m_pTeamLevel_YOURTEAM;	// �y�`�[�����x���z����
	Object2D* m_pTeamLevel_ENEMY;		// �y�`�[�����x���z����

};

#endif
#pragma once
