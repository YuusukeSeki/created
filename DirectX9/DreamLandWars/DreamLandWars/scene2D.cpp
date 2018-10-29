//*****************************************************************************
//
//		2D�|���S��
//												Autohr : Yusuke Seki
//*****************************************************************************
#include "scene2D.h"
#include "renderer.h"
#include "texture.h"


//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Scene2D::Scene2D(int priority, TYPE type):Scene(priority, type)
{
	// �����o�ϐ�������
	ZeroMemory( &m_halfSize , sizeof(D3DXVECTOR3) );	// �����̑傫��
	m_pVtxBuff = NULL;									// ���_�o�b�t�@
	m_pTexture = NULL;									// �e�N�X�`���|�C���^
	m_color.color = 0xffffffff;

	m_pTexture = nullptr;
}


//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
Scene2D::~Scene2D()
{
	// ���_�o�b�t�@�̔j��
	if( m_pVtxBuff != NULL ){
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}


//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
Scene2D* Scene2D::Create( D3DXVECTOR3 pos , D3DXVECTOR3 size )
{
	Scene2D* pScene2D = new Scene2D(2, TYPE_2D);
	pScene2D->Init( pos , size );

	return pScene2D;
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT Scene2D::Init( D3DXVECTOR3 pos , D3DXVECTOR3 size )
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// �ʒu��ݒ�
	Scene::SetPos(pos);

	// �傫����ݒ�
	m_halfSize = size * 0.5f;

	// ���_�o�b�t�@�̐���
	if( m_pVtxBuff == NULL ){
		if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_2D ) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
										  D3DPOOL_MANAGED, &m_pVtxBuff, NULL ) )){
			MessageBox( NULL , "���_�o�b�t�@�������s" , "Scene2D::Init( D3DXVECTOR3 pos , D3DXVECTOR3 size )" , MB_OK );
		}
	}

	// ���_����ݒ�
	VERTEX_2D* pVtx;

	// VRAM�̉��z�A�h���X�擾
	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0 );

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3( pos.x - m_halfSize.x , pos.y - m_halfSize.y , 0.0f);
	pVtx[1].pos = D3DXVECTOR3( pos.x + m_halfSize.x , pos.y - m_halfSize.y , 0.0f);
	pVtx[2].pos = D3DXVECTOR3( pos.x - m_halfSize.x , pos.y + m_halfSize.y , 0.0f);
	pVtx[3].pos = D3DXVECTOR3( pos.x + m_halfSize.x , pos.y + m_halfSize.y , 0.0f);

	// 
	pVtx[0].rhw = 
	pVtx[1].rhw = 
	pVtx[2].rhw = 
	pVtx[3].rhw = 1.0f;

	// ���_�F�̐ݒ�
	pVtx[0].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[1].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[2].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[3].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	// �e�N�X�`��UV�l�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2( 0.0f , 0.0f );
	pVtx[1].tex = D3DXVECTOR2( 1.0f , 0.0f );
	pVtx[2].tex = D3DXVECTOR2( 0.0f , 1.0f );
	pVtx[3].tex = D3DXVECTOR2( 1.0f , 1.0f );

	// VRAM�̉��z�A�h���X���
	m_pVtxBuff->Unlock();

	return S_OK;
}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void Scene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if( m_pVtxBuff != NULL ){
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void Scene2D::Update(void)
{
}


//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void Scene2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource( 0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_2D );

	// �e�N�X�`���̐ݒ�
	if (m_pTexture != nullptr) pDevice->SetTexture(0, m_pTexture->GetTexture());
	else                       pDevice->SetTexture(0, nullptr);

	// �|���S���̕`��
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );				
}


//-----------------------------------------------------------------------------
// ���W�̈ړ�
//-----------------------------------------------------------------------------
void Scene2D::MovePos( D3DXVECTOR3 move )
{
	// ���W�̈ړ�
	Scene::MovePos(move);
	D3DXVECTOR3 newPos = Scene::GetPos();

	// ���_�o�b�t�@�̏�������
	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0 );

	pVtx[0].pos = D3DXVECTOR3( newPos.x - m_halfSize.x , newPos.y - m_halfSize.y , 0.0f);
	pVtx[1].pos = D3DXVECTOR3( newPos.x + m_halfSize.x , newPos.y - m_halfSize.y , 0.0f);
	pVtx[2].pos = D3DXVECTOR3( newPos.x - m_halfSize.x , newPos.y + m_halfSize.y , 0.0f);
	pVtx[3].pos = D3DXVECTOR3( newPos.x + m_halfSize.x , newPos.y + m_halfSize.y , 0.0f);

	m_pVtxBuff->Unlock();
}


//-----------------------------------------------------------------------------
// ���W�̐ݒ�
//-----------------------------------------------------------------------------
void Scene2D::SetPos( D3DXVECTOR3 pos )
{
	// ���W�̈ړ�
	Scene::SetPos(pos);
	D3DXVECTOR3 newPos = Scene::GetPos();

	// ���_�o�b�t�@�̏�������
	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0 );

	pVtx[0].pos = D3DXVECTOR3( newPos.x - m_halfSize.x , newPos.y - m_halfSize.y , 0.0f);
	pVtx[1].pos = D3DXVECTOR3( newPos.x + m_halfSize.x , newPos.y - m_halfSize.y , 0.0f);
	pVtx[2].pos = D3DXVECTOR3( newPos.x - m_halfSize.x , newPos.y + m_halfSize.y , 0.0f);
	pVtx[3].pos = D3DXVECTOR3( newPos.x + m_halfSize.x , newPos.y + m_halfSize.y , 0.0f);

	m_pVtxBuff->Unlock();
}


//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
void Scene2D::SetColor(unsigned int rgba)
{
	// �F�ݒ�
	m_color.color = rgba;

	// ���_����ݒ�
	VERTEX_2D* pVtx;

	// VRAM�̉��z�A�h���X�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�F�̐ݒ�
	pVtx[0].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[1].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[2].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[3].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);

	// VRAM�̉��z�A�h���X���
	m_pVtxBuff->Unlock();
}


//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
void Scene2D::SetUV(float U, float V, float width, float height)
{
	// ���_����ݒ�
	VERTEX_2D* pVtx;

	// VRAM�̉��z�A�h���X�擾
	m_pVtxBuff->Lock( 0, 0, (void**)&pVtx, 0 );

	// �e�N�X�`��UV�l�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2( U        , V          );
	pVtx[1].tex = D3DXVECTOR2( U + width, V          );
	pVtx[2].tex = D3DXVECTOR2( U        , V + height );
	pVtx[3].tex = D3DXVECTOR2( U + width, V + height );

	// VRAM�̉��z�A�h���X���
	m_pVtxBuff->Unlock();
}


