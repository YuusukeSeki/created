//*****************************************************************************
//
//		キャラクターパラメータ表
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
		// 設定パラメータ
		const float initialVelosity    =  0.f;	// 初速
		const float acceleration       =  0.f;	// 加速度
		const float avoidDistance      = 15.f;	// 回避距離

		const int   straightShotDamage =   150;	// SSの威力
		const float straightShotSpeed  =   5.f;	// SSの速度
		const float straightShotRange  = 100.f;	// SSの射程

		const int   drawShotDamage     =   70;	// DSの威力
		const float drawShotSpeed      =   3.f;	// DSの速度
		const float drawShotRange      = 150.f;	// DSの射程
		const float drawShotLength     = 300.f;	// DSの描ける長さ

		const int   breakPower         =   5;	// 拠点を殴る強さ

		const int   cooldown_Avoid     =  45;	// 【硬直時間】避ける
		const int   cooldown_EmAvoid   = 160;	// 【硬直時間】緊急回避
		const int   cooldown_StShot    =  40;	// 【硬直時間】SS
		const int   cooldown_DrShot    =  90;	// 【硬直時間】DS

		const int   maxLife            = 100;	// 【最大値】体力
		const float maxMoveSpeed       =  2.f;	// 【最大値】速度

		// 実際に設定する
		pPlayer->SetInirtialVelocity(initialVelosity);		// 初速
		pPlayer->SetAcceleration(acceleration);				// 加速度
		pPlayer->SetAvoidDiatance(avoidDistance);			// 回避距離

		pPlayer->SetStraightShotDamage(straightShotDamage);	// SSの威力
		pPlayer->SetStraightShotSpeed(straightShotSpeed);	// SSの速度
		pPlayer->SetStraightShotRange(straightShotRange);	// SSの射程

		pPlayer->SetDrawShotDamage(drawShotDamage);			// DSの威力
		pPlayer->SetDrawShotSpeed(drawShotSpeed);			// DSの速度
		pPlayer->SetDrawShotRange(drawShotRange);			// DSの射程
		pPlayer->SetDrawShotLength(drawShotLength);			// DSの描ける長さ

		pPlayer->SetBreakPower(breakPower);					// 拠点を殴る強さ
	
		pPlayer->SetCooldown_Avoid(cooldown_Avoid);			// 【硬直時間】避ける
		pPlayer->SetCooldown_EmAvoid(cooldown_EmAvoid);		// 【硬直時間】緊急回避
		pPlayer->SetCooldown_StShot(cooldown_StShot);		// 【硬直時間】SS
		pPlayer->SetCooldown_DrShot(cooldown_DrShot);		// 【硬直時間】DS
		pPlayer->SetMaxLife(maxLife);						// 【最大値】体力
		pPlayer->SetMaxMoveSpeed(maxMoveSpeed);				// 【最大値】速度


		pPlayer->SetPosture(T::POSTURE::POSTURE_NONE);		// 体勢
		pPlayer->SetLife(maxLife);							// 現在の体力


	}


};


#endif
