//*****************************************************************************
//
//		アイコン
//													Author : Yusuke Seki
//*****************************************************************************
#include "Icon.h"
#include "MainGame.h"
#include "list_LoadTexture_MainGame.h"
#include "Effect3D.h"
#include "tower.h"



//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
Icon::Icon() : ObjectBillboard(Object::TYPE::TYPE_3D_BILLBOARD_ICON)
{
	// データのクリア

}


//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
Icon::~Icon()
{
	// 終了処理
	Uninit();

}


//-----------------------------------------------------------------------------
// 実体の生成
//-----------------------------------------------------------------------------
Icon* Icon::Create(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera, Object::GROUP group)
{
	// 実体の生成
	Icon* pIcon = new Icon;

	// 実体の初期化
	pIcon->Init(position, size, pCamera, group);

	// 生成されたタイマーのポインタを返す
	return pIcon;
}


//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void Icon::Init(D3DXVECTOR3& position, D3DXVECTOR3& size, Camera* pCamera, Object::GROUP group)
{
	// データの初期化
	{
		// 継承データの初期化
		ObjectBillboard::Init(position, size, pCamera);

		SetGroup(group);

		if      (group == Object::GROUP_A) SetColor(0xff0000b0);
		else if (group == Object::GROUP_B) SetColor(0x00ffffb0);

	}

}


//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void Icon::Uninit(void)
{
	// 継承データの終了処理
	ObjectBillboard::Uninit();

}


//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void Icon::Update(void)
{

}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void Icon::Draw(void)
{
	// 描画処理
	ObjectBillboard::Draw();

}



//=============================================================================
// 増減


//=============================================================================
// 設定


