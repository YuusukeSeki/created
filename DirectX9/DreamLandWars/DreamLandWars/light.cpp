//*****************************************************************************
//	���C�g[light.cpp]
//	Autohr	:	Yusuke Seki
//*****************************************************************************

//-----------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "light.h"
#include "renderer.h"

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
Light::Light()
{
	// �����o�ϐ�������
	ZeroMemory( &m_light , sizeof( D3DLIGHT9   ) );
	ZeroMemory( &m_vecDir, sizeof( D3DXVECTOR3 ) );
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
Light::~Light()
{
	Uninit();
}

//-----------------------------------------------------------------------------
// ���̂̐���
//-----------------------------------------------------------------------------
Light* Light::Create(void)
{
	Light* pLight = new Light;
	pLight->Init();

	return pLight;
}
	

//-----------------------------------------------------------------------------
// �������
//-----------------------------------------------------------------------------
void Light::Release(void)
{
	delete this;
}


//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
void Light::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// ���C�g�̐ݒ�
	m_light.Type		= D3DLIGHT_DIRECTIONAL;							// ���s����
	m_light.Diffuse		= D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );			// �g�U���i light.Type�̐F �j
	m_light.Ambient		= D3DXCOLOR( 0.7f, 0.7f, 0.7f, 1.0f );			// ����
	m_light.Specular	= D3DXCOLOR( 0.7f, 0.7f, 0.7f, 1.0f );			// ���ʌ�
	m_vecDir			= D3DXVECTOR3( 0.f , -1.0f , 0.f );				// ���C�g�̌���
	D3DXVec3Normalize( ( D3DXVECTOR3* )&m_light.Direction, &m_vecDir );	// �P�ʃx�N�g����
	pDevice->SetLight( 0, &m_light );									// ���C�g��ݒ�
	pDevice->LightEnable( 0, TRUE );									// �g���܂�
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );					// �S�̂̃��C�g��L���ɂ���
}

//-----------------------------------------------------------------------------
//	�I��
//-----------------------------------------------------------------------------
void Light::Uninit(void)
{
}

//-----------------------------------------------------------------------------
//	�X�V
//-----------------------------------------------------------------------------
void Light::Update(void)
{
}

//-----------------------------------------------------------------------------
//	�g�U���ύX
//-----------------------------------------------------------------------------
void Light::SetDiffuse(float r, float g, float b, float a)
{
	m_light.Diffuse.r = r;
	m_light.Diffuse.g = g;
	m_light.Diffuse.b = b;
	m_light.Diffuse.a = a;
}

//-----------------------------------------------------------------------------
//	�����ύX
//-----------------------------------------------------------------------------
void Light::SetAmbient(float r, float g, float b, float a)
{
	m_light.Ambient.r = r;
	m_light.Ambient.g = g;
	m_light.Ambient.b = b;
	m_light.Ambient.a = a;
}

//-----------------------------------------------------------------------------
//	���ʌ��ύX
//-----------------------------------------------------------------------------
void Light::SetSpecular(float r, float g, float b, float a)
{
	m_light.Specular.r = r;
	m_light.Specular.g = g;
	m_light.Specular.b = b;
	m_light.Specular.a = a;
}

// �����̐ݒ�
// vecDirection : �ݒ肵��������
void Light::SetVectorDirection(D3DXVECTOR3& vecDirection)
{
	m_vecDir = vecDirection;
	D3DXVec3Normalize((D3DXVECTOR3*)&m_light.Direction, &m_vecDir);
	Renderer::GetDevice()->SetLight(0, &m_light);

}
