//*****************************************************************************
//
//		�L�����N�^�[�p�����[�^�\
//												Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _LIST_CHARAPARAMETERS_H_
#define _LIST_CHARAPARAMETERS_H_

#include "main.h"
#include "soldier.h"
#include "list_LoadTexture_MainGame.h"
#include "MainGame.h"



class List_CharacterParameters
{
public:
	template <typename T>
	static void InitParameter(T* pPlayer)
	//static void InitParameter(OLMDL_Player* pPlayer)
	{
		switch (pPlayer->GetCharacter()) {
		case T::CHARACTER::CHARACTER_KIBITSU:
			InitKibitsu(pPlayer);
			break;
		}


	}
//	static void InitParameter(Soldier* pSoldier)
//	{
//		switch (pSoldier->GetCharacter()) {
//		case Soldier::CHARACTER::CHARACTER_NORMAL:
////			InitSoldier_Normal(pSoldier);
//			break;
//		}
//
//
//	}


protected:


private:
	template <typename T>
	static void InitKibitsu(T* pPlayer)
	{
		// �ݒ�p�����[�^
		const float initialVelosity    =  0.f;	// ����
		const float acceleration       =  0.f;	// �����x
		const float avoidDistance      = 15.f;	// �������

		const int   straightShotDamage =   150;	// SS�̈З�
		const float straightShotSpeed  =   5.f;	// SS�̑��x
		const float straightShotRange  = 100.f;	// SS�̎˒�

		const int   drawShotDamage     =   70;	// DS�̈З�
		const float drawShotSpeed      =   3.f;	// DS�̑��x
		const float drawShotRange      = 150.f;	// DS�̎˒�
		const float drawShotLength     = 300.f;	// DS�̕`���钷��

		const int   breakPower         =   5;	// ���_�����鋭��

		const int   cooldown_Avoid     =  45;	// �y�d�����ԁz������
		const int   cooldown_EmAvoid   = 160;	// �y�d�����ԁz�ً}���
		const int   cooldown_StShot    =  40;	// �y�d�����ԁzSS
		const int   cooldown_DrShot    =  90;	// �y�d�����ԁzDS

		const int   maxLife            = 100;	// �y�ő�l�z�̗�
		const float maxMoveSpeed       =  2.f;	// �y�ő�l�z���x

		// ���ۂɐݒ肷��
		pPlayer->SetInirtialVelocity(initialVelosity);		// ����
		pPlayer->SetAcceleration(acceleration);				// �����x
		pPlayer->SetAvoidDiatance(avoidDistance);			// �������

		pPlayer->SetStraightShotDamage(straightShotDamage);	// SS�̈З�
		pPlayer->SetStraightShotSpeed(straightShotSpeed);	// SS�̑��x
		pPlayer->SetStraightShotRange(straightShotRange);	// SS�̎˒�

		pPlayer->SetDrawShotDamage(drawShotDamage);			// DS�̈З�
		pPlayer->SetDrawShotSpeed(drawShotSpeed);			// DS�̑��x
		pPlayer->SetDrawShotRange(drawShotRange);			// DS�̎˒�
		pPlayer->SetDrawShotLength(drawShotLength);			// DS�̕`���钷��

		pPlayer->SetBreakPower(breakPower);					// ���_�����鋭��
	
		pPlayer->SetCooldown_Avoid(cooldown_Avoid);			// �y�d�����ԁz������
		pPlayer->SetCooldown_EmAvoid(cooldown_EmAvoid);		// �y�d�����ԁz�ً}���
		pPlayer->SetCooldown_StShot(cooldown_StShot);		// �y�d�����ԁzSS
		pPlayer->SetCooldown_DrShot(cooldown_DrShot);		// �y�d�����ԁzDS
		pPlayer->SetMaxLife(maxLife);						// �y�ő�l�z�̗�
		pPlayer->SetMaxMoveSpeed(maxMoveSpeed);				// �y�ő�l�z���x


		pPlayer->SetPosture(T::POSTURE::POSTURE_NONE);		// �̐�
		pPlayer->SetLife(maxLife);							// ���݂̗̑�


	}


};


#endif
