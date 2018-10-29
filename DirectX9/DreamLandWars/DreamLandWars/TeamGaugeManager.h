//*****************************************************************************
//
//		�`�[���Q�[�W�}�l�[�W���[
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _TEAMGAUGE_MANAGER_H_
#define _TEAMGAUGE_MANAGER_H_

#include "main.h"
#include "Object2D.h"

class TeamGauge;


class TeamGaugeManager : public Object2D
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	TeamGaugeManager() {}
	TeamGaugeManager(Object::TYPE type);
	~TeamGaugeManager();

	//----- ��{�I�Ȋ֐� -----
	static TeamGaugeManager* Create(D3DXVECTOR3& position, D3DXVECTOR3& size);
	void Init(D3DXVECTOR3& position, D3DXVECTOR3& size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Release(void) { delete this; }

	//----- �������� -----

	//----- �ݒ菈�� -----

	//----- �f�[�^��Ԃ����� -----
	static TeamGauge* GetTeamGauge_YOURTEAM() { return m_pTeamGauge_YOURTEAM; }
	static TeamGauge* GetTeamGauge_ENEMY()    { return m_pTeamGauge_ENEMY; }


private:
	//----- �f�[�^ -----
	Object2D*  m_pLabel_YOURTEAM;		// �y���x���z"YOUR TEAM"
	Object2D*  m_pLabel_ENEMY;			// �y���x���z"ENEMY"
	static TeamGauge* m_pTeamGauge_YOURTEAM;	// �y�Q�[�W�z"YOUR TEAM"
	static TeamGauge* m_pTeamGauge_ENEMY;		// �y�Q�[�W�z"ENEMY"

};

#endif
