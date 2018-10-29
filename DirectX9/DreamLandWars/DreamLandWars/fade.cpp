//*****************************************************************************
//
// �t�F�[�h
// Author : Yusuke Seki
//
//*****************************************************************************
#include "fade.h"
#include "renderer.h"


//=============================================================================
//	
//=============================================================================
Fade::Fade()
{
	m_numFrame    = 60;         // �t�F�[�h�C�� / �A�E�g�ɂ�����܂ł̃t���[����
	m_FadeState   = FADE_NONE;	// �t�F�[�h���
	m_color.color = 0xffffff00;	// �t�F�[�h�F
	m_pVtxBuff    = nullptr;	// ���_�o�b�t�@
}


//=============================================================================
//	
//=============================================================================
Fade::~Fade()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr) {
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}


//=============================================================================
//	
//=============================================================================
Fade* Fade::Create()
{
	// �t�F�[�h�̎��̂𐶐�
	Fade* pFade = new Fade;

	// ���̂̏�����
	pFade->Init();

	// �������ꂽ���̂̃|�C���^��Ԃ�
	return pFade;
}


//=============================================================================
//	
//=============================================================================
void Fade::Release()
{
	// ���̂̏I������
	Uninit();

	// ���̂̔j��
	delete this;
}


//=============================================================================
//	
//=============================================================================
void Fade::Init()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// ���_�o�b�t�@�̐���
	if (m_pVtxBuff == nullptr) {
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
			D3DPOOL_MANAGED, &m_pVtxBuff, NULL))) {
			MessageBox(NULL, "���_�o�b�t�@�������s", "Scene2D::Init( D3DXVECTOR3 pos , D3DXVECTOR3 size )", MB_OK);
		}
	}

	// 2D�|���S���̈ʒu�ƃT�C�Y�̐ݒ�
	D3DXVECTOR3 pos ((SCREEN_WIDTH >> 1), (SCREEN_HEIGHT >> 1), 0); // ��ʂ̒��S
	D3DXVECTOR3 size((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0); // �N���C�A���g�̈�S��

	// VRAM�̉��z�A�h���X�擾
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x * 0.5f, pos.y - size.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x * 0.5f, pos.y - size.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x * 0.5f, pos.y + size.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x * 0.5f, pos.y + size.y * 0.5f, 0.0f);

	// 
	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw =
	pVtx[3].rhw = 1.0f;

	// ���_�F�̐ݒ�
	pVtx[0].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[1].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[2].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[3].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);

	// �e�N�X�`��UV�l�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// VRAM�̉��z�A�h���X���
	m_pVtxBuff->Unlock();

}


//=============================================================================
//	
//=============================================================================
void Fade::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr) {
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

}


//=============================================================================
//	
//=============================================================================
void Fade::Update()
{
	// ��Ԃ�"�t�F�[�h��������"�H
	if (m_FadeState == FADE_NONE) { // ��������
		// �X�V�������I������
		return;
	}


	// ���l�̈ꎞ�i�[�̈�
	short alpha = 0;

	// ��ԑJ��
	switch (m_FadeState)
	{
	// �t�F�[�h�A�E�g
	case FADE_OUT:
		// ���ɓ��ߗ��O�Ȃ��Ԃ��t�F�[�h�A�E�g�I���ɕύX
		if (m_color.rgba[0] == 255) {
			// ��Ԃ�"�t�F�[�h�A�E�g�I��"�ɕύX
			m_FadeState = FADE_OUT_FINISH;

			break;
		}

		// ���l�̑���
		alpha = m_color.rgba[0] + (255 / m_numFrame);

		// ���l��255�ȏ�ɂȂ����H
		if (alpha >= 255) { // �Ȃ���
			// ���l��255�ɏC��
			// ���ߗ��O��`���Ԃɔ��f���Ă���t�F�[�h�A�E�g�I���ɐ؂�ւ���
			m_color.rgba[0] = 255;

		}
		else { // �Ȃ��ĂȂ�
			// ���l���X�V
			m_color.rgba[0] = (unsigned char)alpha;
		}

		// ���_�o�b�t�@�ɔ��f
		UpdateVtxBuf();

		// �t�F�[�h�A�E�g�X�V�����I��
		break;


	// �t�F�[�h�C��
	case FADE_OUT_FINISH:
		// ��Ԃ�"�t�F�[�h�C��"�ɕύX
		m_FadeState = FADE_IN;

		// ���̂܂܃t�F�[�h�C��������


	// �t�F�[�h�C��
	case FADE_IN:
		// ���l�̌���
		alpha = m_color.rgba[0] - (255 / m_numFrame);

		// ���l��0�ȉ��ɂȂ����H
		if (alpha <= 0) { // �Ȃ���
			// ���l��0�ɏC��
			m_color.rgba[0] = 0;

			// ��Ԃ�"�t�F�[�h��������"�ɕύX
			m_FadeState = FADE_NONE;

		}
		else { // �Ȃ��ĂȂ�
			// ���l���X�V
			m_color.rgba[0] = (unsigned char)alpha;
		}

		// ���_�o�b�t�@�ɔ��f
		UpdateVtxBuf();

		// �t�F�[�h�C���X�V�����I��
		break;


	}


}


//=============================================================================
//	
//=============================================================================
void Fade::Draw()
{
	// ��Ԃ�"�t�F�[�h��������"�H
	if (m_FadeState == FADE_NONE) { // ��������
		// �`�揈�����I������
		return;
	}


	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource( 0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_2D );

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture( 0 , nullptr );

	// �|���S���̕`��
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );				
}


//=============================================================================
//	�F�ݒ�
//=============================================================================
void Fade::SetColor(unsigned char r, unsigned char g, unsigned char b)
{
	// �F�̍X�V
	m_color.rgba[3] = r;
	m_color.rgba[2] = g;
	m_color.rgba[1] = b;

	// ���_�o�b�t�@�ɐݒ�
	UpdateVtxBuf();

}


//=============================================================================
//	�t�F�[�h�A�E�g�J�n
//=============================================================================
void Fade::Start_FadeOut(unsigned int numFrame)
{
	// ���݃t�F�[�h�C�� / �A�E�g��ԁH
	if (m_FadeState != FADE_NONE) { // �t�F�[�h�C�� / �A�E�g���
		// �t�F�[�h�ݒ���s�킸�ɏ������I������
		return;
	}

	// �t���[������0�H
	if (numFrame == 0) numFrame = 1; // �l���o�O��̂�1�ɕύX

	// �t�F�[�h�C�� / �A�E�g�ɂ�����t���[�����̐ݒ�
	m_numFrame = numFrame;

	// ��Ԃ�"�t�F�[�h�A�E�g"�ɕύX
	m_FadeState = FADE_OUT;


}


//=============================================================================
//	�t�F�[�h�A�E�g�I������H
//=============================================================================
bool Fade::Finish_FadeOut()
{
	// �t�F�[�h�A�E�g�I������H
	if(m_FadeState == FADE_OUT_FINISH){ // �͂�
		// �I����Ă��
		return true;
	}

	// �I����ĂȂ���
	return false;
}


//=============================================================================
//	���_�o�b�t�@�̍X�V
//=============================================================================
void Fade::UpdateVtxBuf()
{
	// VRAM�̉��z�A�h���X�擾
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�F�̐ݒ�
	pVtx[0].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[1].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[2].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);
	pVtx[3].color = D3DCOLOR_RGBA(m_color.rgba[3], m_color.rgba[2], m_color.rgba[1], m_color.rgba[0]);

	// �e�N�X�`��UV�l�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// VRAM�̉��z�A�h���X���
	m_pVtxBuff->Unlock();


}
