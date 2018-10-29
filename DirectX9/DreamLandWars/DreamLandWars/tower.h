//*****************************************************************************
//
//		��
//													Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _TOWER_H_
#define _TOWER_H_

#include "main.h"
#include "ObjectModel.h"

class Hold;
class LifeGauge;
class Icon;


class Tower : public ObjectModel
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	Tower();
	Tower(Object::TYPE type);
	virtual ~Tower();


	//----- ��{�I�Ȋ֐� -----
	static Tower* Create(D3DXVECTOR3& position, const char* FileName, Object::GROUP group);
	void Init(D3DXVECTOR3& position, const char* FileName, Object::GROUP group);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ���_�Ƀ_���[�W��^����
	// breakPower : �^����_���[�W
	// �y�Ԃ�l�z	true  : ���_����ꂽ
	//				false : ���_�����ĂȂ�
	bool BrowTower(float breakPower);

	// ���������͈͂Ƃ̓����蔻��
	// position : �ΏۃL���X�g�̈ʒu
	// �y�Ԃ�l�z	true  : �����
	//				false : ����Ȃ�
	bool CollisionBrowRange(D3DXVECTOR3& position);

	// �̗͂�Ԃ�
	// �y�Ԃ�l�z���݂̗̑�
	float GetLife() { return m_life; }

	// "Hold"�̎��̂�Ԃ�
	// �y�Ԃ�l�z"Hold"�̎���
	Hold* GetHold() { return m_pHold; }

	// �ړ�����
	void MovePosition(D3DXVECTOR3& movePosition);


private:
	//----- �f�[�^ -----
	float m_life;		// ���݂̗̑�
	float m_browRange;	// �����͈�

	Hold*      m_pHold;			// "HOLD"
	LifeGauge* m_pLifeGauge;	// �̗̓Q�[�W
	Icon*      m_pIcon;			// �A�C�R��
	
	int m_cntFrame;	// ���m�����p�J�E���^�[


};

#endif
