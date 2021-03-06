//*****************************************************************************
//
//		プレイヤー
//												Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "ObjectModel.h"
#include "MainGame.h"

class DrawLine;
class Camera;
class Tower;
class Castle;
class Part;

class Player : public ObjectModel
{
public:
	//----- 列挙型の定義 -----
	enum CHARACTER {	// キャラクター
		CHARACTER_KIBITSU,
	};

	enum POSTURE {	// 体勢（モーションと併用）
		POSTURE_NONE,		// 正常
		POSTURE_RUN,		// 走る
		POSTURE_AVOID,		// 避ける
		POSTURE_EMAVOID,	// 緊急回避
		POSTURE_BACKWORD,	// のけ反る
		POSTURE_TUMBLE,		// 倒れる
		POSTURE_DEATH,		// 死ぬ
		POSTURE_REVIVE,		// 生き返る
		POSTURE_STREADY,	// ストレート準備
		POSTURE_DRREADY,	// ドロー準備
		POSTURE_STSHOT,		// ストレート攻撃
		POSTURE_DRSHOT,		// ドロー攻撃
		POSTURE_BREAK,		// 拠点を殴る
	};


public:
	Player() {}
	Player(Object::TYPE type, Player::CHARACTER character);
	virtual ~Player();

	static Player* Create(D3DXVECTOR3& position, Camera* pCamera, const char* modelPass, Player::CHARACTER character);
	void Init(D3DXVECTOR3& position, Camera* pCamera, const char* modelPass);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 座標の移動
	void MovePosition(D3DXVECTOR3& movePosition);

	// 体力の増減
	void MoveLife(int move);

	// 兵士撃破数加算
	void PlusScore_CrushSoldier() { _score_crushSoldier++; }

	// 体勢の設定
	void SetPosture(Player::POSTURE posture);

	// 体力の設定
	void SetLife(float life);

	Player::CHARACTER GetCharacter() { return m_character; }
	Player::POSTURE GetPosture() { return m_posture; }
	float GetLife() { return m_life; }
	float GetAvDist() { return m_avDist; }
	float GetStraightShotDamage() { return m_straightShotDamage; }
	float GetStraightShotSpeed() { return m_straightShotSpeed; }
	float GetStraightShotRange() { return m_straightShotRange; }
	float GetDrawShotDamage() { return m_drawShotDamage; }
	float GetDrawShotSpeed() { return m_drawShotSpeed; }
	float GetDrawShotRange() { return m_drawShotRange; }
	Camera* GetCamera() { return m_pCamera; }


	void Run(float moveX, float moveZ);		// 走る
	void Avoid(float moveX, float moveZ);	// 避ける
	void EmAvoid(float moveX, float moveZ);	// 緊急回避
	void STReady();							// SS準備
	void STShot();							// SS攻撃
	void DRReady(bool bTrigger);			// DS準備
	void DRShot(bool bRelease);				// DS攻撃
	void BreakBasePoint();					// 拠点を殴る

	int GetScore_CrushSoldier() { return _score_crushSoldier; }	// 兵士撃破数


	//----- その他リスト読み込み時のみの設定処理 -----
	void SetInirtialVelocity(float inirtialVelocity)   { m_InitialVelosity    = inirtialVelocity; }	// 初速の設定
	void SetAcceleration(float acceleration)           { m_Acceleration       = acceleration; }		// 加速度の設定
	void SetAvoidDiatance(float avoidDistance)         { m_avDist             = avoidDistance; }	// 回避距離の設定

	void SetStraightShotDamage(float straightShotDamage) { m_straightShotDamage = straightShotDamage; }	// SS威力の設定
	void SetStraightShotSpeed(float straightShotSpeed) { m_straightShotSpeed  = straightShotSpeed; }	// SS速度の設定
	void SetStraightShotRange(float straightShotRange) { m_straightShotRange  = straightShotRange; }	// SS射程距離の設定

	void SetDrawShotDamage(float drawShotDamege)         { m_drawShotDamage     = drawShotDamege; }	// DS威力の設定
	void SetDrawShotSpeed(float drawShotSpeed)         { m_drawShotSpeed      = drawShotSpeed; }	// DS速度の設定
	void SetDrawShotRange(float drawShotRange)         { m_drawShotRange      = drawShotRange; }	// DS射程距離の設定
	void SetDrawShotLength(float drawShotLength)       { m_drawShotLength     = drawShotLength; }	// DS描画線の最大の長さの設定

	void SetBreakPower(float breakPower)				   { m_breakPower         = breakPower; }		// 拠点を殴る強さの設定

	void SetCooldown_Avoid(int cooldown_Avoid)         { m_cooldown_Avoid     = cooldown_Avoid; }	// 【硬直時間の設定】回避体勢
	void SetCooldown_EmAvoid(int cooldown_EmAvoid)     { m_cooldown_EmAvoid   = cooldown_EmAvoid; }	// 【硬直時間の設定】緊急回避体勢
	void SetCooldown_StShot(int cooldown_StShot)       { m_cooldown_StShot    = cooldown_StShot; }	// 【硬直時間の設定】SS体勢
	void SetCooldown_DrShot(int cooldown_DrShot)       { m_cooldown_DrShot    = cooldown_DrShot; }	// 【硬直時間の設定】DS体勢

	void SetMaxLife(float maxLife)                       { m_maxLife            = maxLife; }			// 【最大値】体力の設定
	void SetMaxMoveSpeed(float maxMoveSpeed)           { m_maxMoveSpeed       = maxMoveSpeed; }		// 【最大値】移動速度の設定


private:
	//----- メソッド -----
	void CollisionTower();
	void CollisionCastle();
	void CollisionWall();
	void UpdateInverseMatrix();
	bool CollisionCursor_Player(D3DXVECTOR3* pOut);
	Tower* CollisionCursor_BasePoint();


	//----- 定数 ----
	       const float INIRTIA      = 0.70f;	// 慣性
	static const int   NUM_DSBUF    = 0xf;		// DS配列数
	static const int   NUM_DRAWLINE = 1;		// 描画線配列数
	static const int   NON_DRAW     = 10;		// 描画線としてカウントしない距離

	//----- データ -----
	Player::CHARACTER m_character;	// 種類
	Player::POSTURE m_posture;		// 体勢

	float       m_life;					// 現在の体力
	D3DXVECTOR3 m_movePosition;			// 移動量バッファ
	float       m_InitialVelosity;		// 初速
	float       m_Acceleration;			// 加速度
	float       m_avDist;				// 回避距離

	float       m_straightShotDamage;	// SSの威力
	float       m_straightShotSpeed;	// SSの速度
	float       m_straightShotRange;	// SSの射程

	float       m_drawShotDamage;		// DSの威力
	float       m_drawShotSpeed;		// DSの速度
	float       m_drawShotRange;		// DSの射程
	float       m_drawShotLength;		// DSの描ける長さ

	float       m_breakPower;			// 拠点を殴る強さ

	int         m_cntCooldownFrame;		// 硬直時間計測用カウンター
	int         m_cooldown_Avoid;		// 【硬直時間】避ける
	int         m_cooldown_EmAvoid;		// 【硬直時間】緊急回避
	int         m_cooldown_StShot;		// 【硬直時間】SS攻撃
	int         m_cooldown_DrShot;		// 【硬直時間】DS攻撃
	float       m_maxLife;				// 【最大値】体力
	float       m_maxMoveSpeed;			// 【最大値】速度
	
	DrawLine*   m_pDL_StartPos;	// 描画線の始点のバッファ
	float       m_DL_Length;	// 描画線の長さのバッファ
	D3DXVECTOR3 m_DL_PrePos;	// 描画線の前座標のバッファ
	float       m_DL_PreLength;	// 描画線の更新前の長さのバッファ

	D3DXVECTOR3 m_prePosion;	// 前フレームの座標

	float currentFront, targetFront;	// 現在の向き, 目標の向き

	// 仮想ベクトルの設定用
	Camera* m_pCamera;	// カメラ
	D3DXMATRIX m_InverseMatrix;
	
	// score
	int _score_crushSoldier;	// 兵士撃破数
	
	Part *m_Part[10];

public:
	struct KEY {
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Rotation;
	};

	struct KEY_FRAME {
		int Frame;
		KEY Key[10];
	};

private:
	KEY_FRAME *m_KeyFrame;
	int m_Key;
	int m_Frame;

	void TempInput();

};


#endif
