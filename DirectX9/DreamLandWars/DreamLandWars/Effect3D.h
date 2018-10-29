//*****************************************************************************
//	
//		�G�t�F�N�g�i3D�j
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_

#include "main.h"
#include "EffectManager.h"


class Effect3D : public EffectManager
{
public:
	//----- �񋓌^�̒�` -----
	enum TYPE {	// ���
		TYPE_FIRE,	// ��

		__TYPEMAX,	// �� ��ނ̍ő吔
	};


public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	Effect3D() {}
	Effect3D(EffectManager::TYPE type);
	virtual ~Effect3D();

	
	//----- ��{�I�Ȋ֐� -----
	static Effect3D* Create(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Init(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);


	//----- �������� -----
	void MovePosition(D3DXVECTOR3& movePosition);																				// ���W�̈ړ�
	void MoveSize(D3DXVECTOR3& moveSize);																						// �傫���̑���
	void MoveRotate(D3DXVECTOR3& moveRotate);																					// ��]���̑���
	void MoveScale(D3DXVECTOR3& moveScale);																						// �g�k���̑���
	void MoveAccelerate(D3DXVECTOR3& moveAccelerate) { m_accelerate += moveAccelerate; }										// �����x�̑���
	void MoveNormal(D3DXVECTOR3& moveNormal0, D3DXVECTOR3& moveNormal1, D3DXVECTOR3& moveNormal2, D3DXVECTOR3& moveNormal3);	// �@���̑���
	void MoveColor(float r, float g, float b, float a);																			// �F�̑���
	void MoveUV_StartPoint(D3DXVECTOR2& moveUV_StartPoint);																		// UV�J�n�_�̑���
	void MoveUV_Size(D3DXVECTOR2& moveUV_Size);																					// UV�傫���̑���


	//----- �ݒ菈�� -----
	static void SetEffect(D3DXVECTOR3& position, D3DXVECTOR3& vecZ, Effect3D::TYPE effectType);								// �G�t�F�N�g�̔���
	void SetPosition(D3DXVECTOR3& position);																				// ���W�̐ݒ�
	void SetSize(D3DXVECTOR3& size);																						// �傫���̐ݒ�
	void SetRotate(D3DXVECTOR3& rotate);																					// ��]���̐ݒ�
	void SetScale(D3DXVECTOR3& scale);																						// �g�k���̐ݒ�
	void SetAccelerate(D3DXVECTOR3& accelerate) { m_accelerate = accelerate; }												// �����x�̐ݒ�
	void SetNormal(D3DXVECTOR3& moveNormal0, D3DXVECTOR3& moveNormal1, D3DXVECTOR3& moveNormal2, D3DXVECTOR3& moveNormal3);	// �@���̐ݒ�
	void SetColor(int r, int g, int b, int a);																				// �F�̐ݒ�
	void SetUV_StartPoint(D3DXVECTOR2& UV_StartPoint);																		// UV�J�n�_�̐ݒ�
	void SetUV_Size(D3DXVECTOR2& UV_Size);																					// UV�傫���̐ݒ�
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }													// �e�N�X�`���̐ݒ�


	//----- �f�[�^��Ԃ����� -----
	D3DXMATRIX*        GetWorldMatrix()        { return &m_WorldMatrix; }		// ���[���h�}�g���N�X��Ԃ�
	D3DXVECTOR3*       GetSize()               { return &(m_halfSize * 2); }	// �傫����Ԃ�
	D3DXVECTOR3*       GetHalfSize()           { return &m_halfSize; }			// �����̑傫����Ԃ�
	D3DXVECTOR3*       GetRotate()             { return &m_rotate; }			// ��]����Ԃ�
	D3DXVECTOR3*       GetScale()              { return &m_scale; }				// �g�k����Ԃ�
	float              GetRadius()             { return m_radius; }				// ���a��Ԃ�
	D3DXVECTOR3*       GetAccelerate()         { return &m_accelerate; }		// �����x��Ԃ�
	D3DXVECTOR3*       GetNormal_LeftTop()     { return &m_normal[0]; }			// �@����Ԃ�
	D3DXVECTOR3*       GetNormal_RightTop()    { return &m_normal[1]; }			// �@����Ԃ�
	D3DXVECTOR3*       GetNormal_LeftBottom()  { return &m_normal[2]; }			// �@����Ԃ�
	D3DXVECTOR3*       GetNormal_RightBottom() { return &m_normal[3]; }			// �@����Ԃ�
	//unsigned int       GetColor()              { return m_color.color; }		// �F��Ԃ�
	D3DXVECTOR2*       GetUV_StartPoint()      { return &m_UV_StartPoint; }		// UV�J�n�_��Ԃ�
	D3DXVECTOR2*       GetUV_Size()            { return &m_UV_Size; }			// UV�̑傫����Ԃ�
	LPDIRECT3DTEXTURE9 GetTexture()            { return m_pTexture; }			// �e�N�X�`����Ԃ�


protected:
	//----- �f�[�^��Ԃ����� -----
	const bool GetInstance() { return m_bInstance; }	// �g�p���t���O��Ԃ��Ftrue �Ŏg�p��


protected:
	//----- �ݒ菈�� -----
	virtual void SetEffect_Protected(D3DXVECTOR3& position, D3DXVECTOR3& vecZ, Effect3D::TYPE effectType);							// �G�t�F�N�g�̐ݒ�
	        void SetUpdateVertexBuf(bool bUpdateVertexBuf)     { m_bUpdateVertexBuf = bUpdateVertexBuf; }		// true �Œ��_�o�b�t�@�̍X�V����������
	        void SetUpdateWorldMatrix(bool bUpdateWorldMatrix) { m_bUpdateWorldMatrix = bUpdateWorldMatrix; }	// true �Ń��[���h�}�g���N�X�̍X�V����������


private:
	//----- �֐� -----
	        void MakeVertexBuf();		// ���_�o�b�t�@�̐���
	        void UpdateVertexBuf();		// ���_�o�b�t�@�̍X�V
	virtual void UpdateWorldMatrix();	// ���[���h�}�g���N�X�̍X�V

	//----- �f�[�^ -----
	D3DXMATRIX  m_WorldMatrix;		// ���[���h�}�g���N�X
	D3DXVECTOR3 m_halfSize;			// �����̑傫��
	D3DXVECTOR3 m_rotate;			// ��]��
	D3DXVECTOR3 m_scale;			// �g�k��
	float       m_radius;			// ���a
	D3DXVECTOR3 m_accelerate;		// �����x
	D3DXVECTOR3 m_normal[4];		// �@��
	float       m_color_R;			// �ԐF
	float       m_color_G;			// �ΐF
	float       m_color_B;			// �F
	float       m_color_A;			// ���ߐF
	D3DXVECTOR2 m_UV_StartPoint;	// UV�J�n�_
	D3DXVECTOR2 m_UV_Size;			// UV�傫��

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9      m_pTexture;	// �e�N�X�`��

	bool m_bUpdateVertexBuf;	// true �Œ��_�o�b�t�@�̍X�V������
	bool m_bUpdateWorldMatrix;	// true �Ń��[���h�}�g���N�X�̍X�V������
	bool m_bInstance;			// true �Ŏg�p��


	//----- �f�[�^ -----
	unsigned int m_life;							// ����
	D3DXVECTOR3  m_ChangeRotateByFrame;			// �t���[���Ԃ̉�]���ω���
	D3DXVECTOR3  m_ChangeScaleByFrame;			// �t���[���Ԃ̊g�k���ω���
	D3DXVECTOR3  m_ChangeAccelerateByFrame;		// �t���[���Ԃ̉����x�ω���
	float        m_ChangeRedByFrame;			// �t���[���Ԃ̒��_�F�E�ԁA�ω���
	float        m_ChangeGreenByFrame;			// �t���[���Ԃ̒��_�F�E�΁A�ω���
	float        m_ChangeBlueByFrame;			// �t���[���Ԃ̒��_�F�E�A�ω���
	float        m_ChangeAlphaByFrame;			// �t���[���Ԃ̒��_�F�E���ߒl�A�ω���
	D3DXVECTOR2  m_ChangeUVStartPointByFrame;	// �t���[���Ԃ�UV�J�n�_�ω���
	D3DXVECTOR2  m_ChangeUVSizeByFrame;			// �t���[���Ԃ�UV�T�C�Y�ω���

};

#endif

