//*****************************************************************************
//	
//		�|���S���}�l�[�W���[
//													Author : Yusuke Seki
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

//----- �C���N���[�h�t�@�C��
#include "main.h"


//----- �N���X�̒�`
class Scene
{
public:
	// �萔
	static const int NUM_TYPE  = 3; // Model, 3D, 2D
	//static const int MAX_SCENE = 0x00000ffff; // �eScene�̍ő吶����
	static const int MAX_SCENE = 1; // �eScene�̍ő吶����

	// �F
	union Color {
		unsigned int color;
		unsigned char rgba[4];
	};

	// �^�C�v
	enum TYPE { // �`�揇�����p
		TYPE_MODEL,	       // �����f��
		TYPE_MODEL_PLAYER, // �v���C���[
		TYPE_MODEL_ENEMY,  // �G�l�~�[
		TYPE_3D,           // ��3D�|���S��
		TYPE_3D_FIELD,	   // �t�B�[���h
		TYPE_3D_BILLBOARD, // �r���{�[�h
		TYPE_3D_SKYBOX,    // �X�J�C�{�b�N�X
		TYPE_3D_SPHERE,    // ����
		TYPE_BB_BULLET,    // �o���b�g
		TYPE_2D,           // ��2D�|���S��
		TYPE_MAX,
	};

	// �O���[�v
	enum GROUP {
		GROUP_NONE,
		GROUP_A,
		GROUP_B,
	};

	// �R���X�g���N�^ / �f�X�g���N�^
	Scene(){}
	Scene(int priority, Scene::TYPE type);
	virtual ~Scene(){}

	// ��{�I�Ȋ֐�
	virtual void Init(void){}
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	void Release(void);

	// ALL
	static void UninitAll();
	static void UpdateAll();
	static void DrawAll();
	static void ReleaseAll();

	// ����
	virtual void MovePos(D3DXVECTOR3 move) { m_pos += move; }

	// �ݒ�
	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetGroup(GROUP group) { m_group = group; }

	// �擾
	static Scene* GetScene(Scene::TYPE type, int arrayIdx1, int arrayIdx2);
	D3DXVECTOR3 GetPos() { return m_pos; }
	Scene::TYPE GetType() { return m_sceneType; }
	GROUP GetGroup() { return m_group; }


protected:


private:
	// �ϐ�
	static Scene* m_pScene[NUM_TYPE][MAX_SCENE];
	D3DXVECTOR3 m_pos;
	TYPE m_sceneType;

	GROUP m_group;

};

#endif

