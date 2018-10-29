//*****************************************************************************
//	
//		�|���S���}�l�[�W���[
//													Author : Yusuke Seki
//*****************************************************************************
#include "scene.h"

//----- �ÓI�����o�ϐ������� -----
Scene* Scene::m_pScene[Scene::NUM_TYPE][Scene::MAX_SCENE] = {};



//-----------------------------------------------------------------------------
//	�R���X�g���N�^
//-----------------------------------------------------------------------------
Scene::Scene(int priority, Scene::TYPE type)
{
	for(int i=0; i<MAX_SCENE; i++){
		if(m_pScene[priority][i] == nullptr){
			m_pScene[priority][i] = this;
			m_pos = D3DXVECTOR3(0,0,0);
			m_sceneType = type;

			m_group = GROUP_NONE;
			break;
		}
	}
}


//-----------------------------------------------------------------------------
//	��������F��
//-----------------------------------------------------------------------------
void Scene::Release()
{
	for( int j=0; j<NUM_TYPE; j++ ){
		for(int i=0; i<MAX_SCENE; i++){
			if(m_pScene[j][i] == this){
				Uninit();
				delete this;
				m_pScene[j][i] = nullptr;
				break;
			}
		}
	}
}


//-----------------------------------------------------------------------------
//	�I������
//-----------------------------------------------------------------------------
void Scene::UninitAll()
{
	for( int j=0; j<NUM_TYPE; j++ ){
		for(int i=0; i<MAX_SCENE; i++){
			if(m_pScene[j][i] != nullptr){
				m_pScene[j][i]->Uninit();
			}
		}
	}
}


//-----------------------------------------------------------------------------
//	�X�V����
//-----------------------------------------------------------------------------
void Scene::UpdateAll()
{
	for( int j=0; j<NUM_TYPE; j++ ){
		for(int i=0; i<MAX_SCENE; i++){
			if(m_pScene[j][i] != nullptr){
				m_pScene[j][i]->Update();
			}
		}
	}
}


//-----------------------------------------------------------------------------
//	�`�揈��
//-----------------------------------------------------------------------------
void Scene::DrawAll()
{
	for( int j=0; j < NUM_TYPE; j++ ){
		for(int i=0; i < MAX_SCENE; i++){
			if(m_pScene[j][i] != nullptr){
				m_pScene[j][i]->Draw();
			}
		}
	}
}


//-----------------------------------------------------------------------------
//	�������
//-----------------------------------------------------------------------------
void Scene::ReleaseAll()
{
	for( int j=0; j<NUM_TYPE; j++ ){
		for(int i=0; i<MAX_SCENE; i++){
			if(m_pScene[j][i] != nullptr){
				m_pScene[j][i]->Release();
			}
		}
	}
}


//-----------------------------------------------------------------------------
//	
//-----------------------------------------------------------------------------
Scene* Scene::GetScene(Scene::TYPE type, int arrayIdx1, int arrayIdx2)
{
	// ���̂�������� nullptr ��Ԃ�
	if (m_pScene[arrayIdx2][arrayIdx1] == nullptr) return nullptr;

	// �^�C�v���Ⴆ�� nullptr ��Ԃ�
	if (m_pScene[arrayIdx2][arrayIdx1]->m_sceneType != type) return nullptr;

	// ��v�����̂Ń|�C���^��Ԃ�
	return m_pScene[arrayIdx2][arrayIdx1];

}


