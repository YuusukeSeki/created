//*****************************************************************************
//
// ���͏��� [input.cpp]
// Author : Yusuke Seki
//
//*****************************************************************************
#include "main.h"
#include "input.h"
#include "renderer.h"


// �ÓI�ϐ��̏�����
LPDIRECTINPUT8       Input::m_pInput         = nullptr; // DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 Input::m_pDevJoystick   = nullptr; // ���̓f�o�C�X(�W���C�X�e�B�b�N)�ւ̃|�C���^
DIDEVCAPS			 Input::m_diJoystickCaps = {};	    // �W���C�X�e�B�b�N�̔\��



//=============================================================================
// ���͏���
// ����
Input* Input::Create(HINSTANCE hInstance, HWND hWnd)
{
	Input* pInput = new Input;
	pInput->Init( hInstance, hWnd );

	return pInput;
}


// ������
HRESULT Input::Init(HINSTANCE hInstance, HWND hWnd)
{
	if(m_pInput == NULL){
		// DirectInput�I�u�W�F�N�g�̍쐬
		if(FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
										IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
			return E_FAIL;
		}
	}

#ifdef _USE_KEYBOARD
	// �L�[�{�[�h�̓��͐���
	if(FAILED(InitKeyboard(hInstance,hWnd))){
		MessageBox(hWnd,"�L�[�{�[�h�̓��͐���̏������Ɏ��s���܂���","�x���I",MB_OK | MB_ICONERROR);
		return E_FAIL;
	}
#endif

	// �}�E�X�̓��͐���
#ifdef _USE_MOUSE
	if(FAILED(InitMouse(hInstance,hWnd))){
		MessageBox(hWnd,"�}�E�X�̓��͐���̏������Ɏ��s���܂���","�x���I",MB_OK | MB_ICONERROR);
		return E_FAIL;
	}
#endif

	// �W���C�X�e�B�b�N�̓��͐���
#ifdef _USE_JOYSTICK
	if(FAILED(InitJoystick(hInstance,hWnd))){
		//MessageBox(hWnd,"�W���C�X�e�B�b�N�̓��͐���̏������Ɏ��s���܂���", "�x���I" ,MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
#endif

	return S_OK;
}


// �I��
void Input::Uninit(void)
{
#ifdef _USE_JOYSTICK
	// �W���C�X�e�B�b�N�̓��͐���
	UninitJoystick();
#endif

#ifdef _USE_MOUSE
	// �}�E�X�̓��͐���
	UninitMouse();
#endif

#ifdef _USE_KEYBOARD
	// �L�[�{�[�h�̓��͐���
	UninitKeyboard();
#endif

	// DirectInput�I�u�W�F�N�g�̊J��
	if(m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

	delete this;
}


// �X�V
void Input::Update(void)
{
#ifdef _USE_KEYBOARD
	// �L�[�{�[�h�X�V
	UpdateKeyboard();
#endif

#ifdef _USE_MOUSE
	// �}�E�X�X�V
	UpdateMouse();
#endif

#ifdef _USE_JOYSTICK
	// �W���C�X�e�B�b�N�X�V
	UpdateJoystick();
#endif
}



#ifdef _USE_KEYBOARD
//=============================================================================
// �L�[�{�[�h
// ������
HRESULT Input::InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// �f�o�C�X�̍쐬
	if(FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if(FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if(FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevKeyboard->Acquire();

	//�@�ϐ��̏�����
	for (int i = 0; i < NUM_KEY_MAX; i++) {
		m_aKeyState[i]            = 0;
		m_aKeyStateTrigger[i]     = 0;
		m_aKeyStateWTrigger[i]    = 0;
		m_aKeyStateRelease[i]     = 0;
		m_aKeyStateRepeat[i]      = 0;
		m_aKeyStateWTriggerCnt[i] = 0;
		m_aKeyStateRepeatCnt[i]   = 0;
	}

	return S_OK;
}


// �I��
void Input::UninitKeyboard(void)
{
	if(m_pDevKeyboard != NULL)
	{// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		m_pDevKeyboard->Unacquire();

		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}
}


// �X�V
void Input::UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	// �f�o�C�X����f�[�^���擾
	if(SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for(int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// �L�[ �g���K�[���̐���
			m_aKeyStateTrigger[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];

			// �L�[ �����[�X���̐���
			m_aKeyStateRelease[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & m_aKeyState[nCnKey];

			// �L�[ ���s�[�g���̐���
			if(aKeyState[nCnKey]){
				if(m_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT){
					m_aKeyStateRepeatCnt[nCnKey]++;

					if(m_aKeyStateRepeatCnt[nCnKey] == 1 || m_aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT){
						m_aKeyStateRepeat[nCnKey] = aKeyState[nCnKey];
					}
					else{
						m_aKeyStateRepeat[nCnKey] = 0;
					}
				}
			}
			else{
				m_aKeyStateRepeat[nCnKey] = 0;
				m_aKeyStateRepeatCnt[nCnKey] = 0;
			}
			//----- �{�^���̃_�u���g���K�[���̐��� -----
			// �J�E���^�[����Ă�H
			if (m_aKeyStateWTriggerCnt[nCnKey]) {
				m_aKeyStateWTriggerCnt[nCnKey]++;

				// ������x�g���K�[�������ꂽ��_�u���g���K�[�Ƃ��Ĕ��肷��
				if (m_aKeyStateTrigger[nCnKey]) {
					m_aKeyStateWTrigger[nCnKey] = aKeyState[nCnKey];

					m_aKeyStateWTriggerCnt[nCnKey] = 0;
				}

				// �J�E���^�[��臒l����������t���O���~�낷
				if (m_aKeyStateWTriggerCnt[nCnKey] >= LIMIT_COUNT_WTRIGGER) {
					m_aKeyStateWTriggerCnt[nCnKey] = 0;
				}

			}
			// �g���K�[�������ꂽ��J�E���^�[���񂵎n�߂�
			else if (m_aKeyStateTrigger[nCnKey]) m_aKeyStateWTriggerCnt[nCnKey]++;

			// �J�E���^�[�����Z�b�g����
			else m_aKeyStateWTrigger[nCnKey] = 0;


			// �L�[�v���X����ۑ�
			m_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		m_pDevKeyboard->Acquire();
	}
}


// �擾 : �����Ă��邩
bool Input::GetKeyboardPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true: false;
	//return (m_aKeyState[nKey] & 0x01) ? true: false;	// �O�̃t���[���ŉ����ꂽ�L�[���擾
}


// �擾 : �������u�Ԃ�
bool Input::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true: false;
}


// �擾 : �������u�Ԃ�
bool Input::GetKeyboardRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}


// �擾 : �h���N�G�I�ȃA��
bool Input::GetKeyboardRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0x80) ? true: false;
}


// �擾 : 2��A���ŉ����ꂽ�u�Ԃ̂�
bool Input::GetKeyboardWTrigger(int nKey)
{
	return (m_aKeyStateWTrigger[nKey] & 0x80) ? true : false;

}

#endif



#ifdef _USE_MOUSE
//=============================================================================
// �}�E�X
// ������
HRESULT Input::InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	// �f�o�C�X�̍쐬
	if(FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevMouse, NULL)))
	{
		MessageBox(hWnd, "�}�E�X���˂��I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if(FAILED(m_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		MessageBox(hWnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if(FAILED(m_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�}�E�X�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// ����	���L�̓o�b�t�@�����O���͂�ǂݎ��ꍇ�̐ݒ�
	//		��L�ŃC�x���g�ʒm�ɂ��ǂݎ��ݒ���s���ꍇ�͕s�v�B
	// �o�b�t�@�[�T�C�Y�̐ݒ�
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize		= sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj		= 0;
	dipdw.diph.dwHow		= DIPH_DEVICE;
	dipdw.dwData			= 100;

	// ����������
	//diprop.dwData = DIPROPAXISMODE_REL; // ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j    
	//pDIMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	if(FAILED(m_pDevMouse->SetProperty(DIPROP_BUFFERSIZE,&dipdw.diph)))
	{
		MessageBox(hWnd, "�}�E�X�̃o�b�t�@�[�T�C�Y��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevMouse->Acquire();

	// �ϐ��̏�����
	for (int i = 0; i < NUM_MOUSE_MAX; i++) {
		m_diMouseState.rgbButtons[i]         = 0;
		m_diMouseStateTrigger.rgbButtons[i]  = 0;
		m_diMouseStateWTrigger.rgbButtons[i] = 0;
		m_diMouseStateRelease.rgbButtons[i]  = 0;
		m_diMouseStateRepeat.rgbButtons[i]   = 0;
		m_diMouseStateWTriggerCnt[i]         = 0;
		m_diMouseStateRepeatCnt[i]           = 0;
	}


	return S_OK;
}


// �I��
void Input::UninitMouse(void)
{
	if(m_pDevMouse != NULL)
	{// ���̓f�o�C�X�̊J��
		// �}�E�X�ւ̃A�N�Z�X�����J��(���͐���I��)
		m_pDevMouse->Unacquire();

		m_pDevMouse->Release();
		m_pDevMouse = NULL;
	}
}


// �X�V
void Input::UpdateMouse(void)
{
	DIMOUSESTATE2 diMouseState;

	// �f�o�C�X����f�[�^���擾
	if(SUCCEEDED(m_pDevMouse->GetDeviceState(sizeof(m_diMouseState), &diMouseState)))
	{
		for(int nCnKey = 0; nCnKey < NUM_MOUSE_MAX; nCnKey++)
		{
			m_diMouseState.lX = diMouseState.lX;
			m_diMouseState.lY = diMouseState.lY;
			m_diMouseState.lZ = diMouseState.lZ;

			// �}�E�X�̃g���K�[���̐���
			m_diMouseStateTrigger.rgbButtons[nCnKey] =
				(m_diMouseState.rgbButtons[nCnKey] ^ diMouseState.rgbButtons[nCnKey]) & diMouseState.rgbButtons[nCnKey];

			// �}�E�X�̃����[�X���̐���
			m_diMouseStateRelease.rgbButtons[nCnKey] =
				(m_diMouseState.rgbButtons[nCnKey] ^ diMouseState.rgbButtons[nCnKey]) & m_diMouseState.rgbButtons[nCnKey];

			// �}�E�X�̃��s�[�g���̐���
			if(diMouseState.rgbButtons[nCnKey])
			{
				if(m_diMouseStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					m_diMouseStateRepeatCnt[nCnKey]++;

					if(m_diMouseStateRepeatCnt[nCnKey] == 1 || m_diMouseStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{
						m_diMouseStateRepeat.rgbButtons[nCnKey] = diMouseState.rgbButtons[nCnKey];
					}
					else
					{
						m_diMouseStateRepeat.rgbButtons[nCnKey] = 0;
					}
				}
			}
			else
			{
				m_diMouseStateRepeat.rgbButtons[nCnKey] = 0;
				m_diMouseStateRepeatCnt[nCnKey] = 0;
			}
		
			//----- �{�^���̃_�u���g���K�[���̐��� -----
			// �J�E���^�[����Ă�H
			if (m_diMouseStateWTriggerCnt[nCnKey]) {
				m_diMouseStateWTriggerCnt[nCnKey]++;

				// ������x�g���K�[�������ꂽ��_�u���g���K�[�Ƃ��Ĕ��肷��
				if (m_diMouseStateTrigger.rgbButtons[nCnKey]) {
					m_diMouseStateWTrigger.rgbButtons[nCnKey] = diMouseState.rgbButtons[nCnKey];

					m_diMouseStateWTriggerCnt[nCnKey] = 0;
				}

				// �J�E���^�[��臒l����������t���O���~�낷
				if (m_diMouseStateWTriggerCnt[nCnKey] >= LIMIT_COUNT_WTRIGGER) {
					m_diMouseStateWTriggerCnt[nCnKey] = 0;
				}

			}
			// �g���K�[�������ꂽ��J�E���^�[���񂵎n�߂�
			else if (m_diMouseStateTrigger.rgbButtons[nCnKey]) m_diMouseStateWTriggerCnt[nCnKey]++;
			else m_diMouseStateWTrigger.rgbButtons[nCnKey] = 0;


			// �}�E�X�̃v���X����ۑ�
			m_diMouseState.rgbButtons[nCnKey] = diMouseState.rgbButtons[nCnKey];
		}
	}
	else
	{
		// �}�E�X�ւ̃A�N�Z�X�����擾
		m_pDevMouse->Acquire();
	}

}


// �擾 : �����Ă��邩
bool Input::GetMousePress(int nKey)
{
	return (m_diMouseState.rgbButtons[nKey] & 0x80) ? true: false;
	//return (m_diMouseState.rgbButtons[nKey] & 0x01) ? true: false;	// �O�̃t���[���ŉ����ꂽ�{�^�����擾
}


// �擾 : �������u�Ԃ�
bool Input::GetMouseTrigger(int nKey)
{
	return (m_diMouseStateTrigger.rgbButtons[nKey] & 0x80) ? true: false;
}


// �擾 : �������u�Ԃ�
bool Input::GetMouseRelease(int nKey)
{
	return (m_diMouseStateRelease.rgbButtons[nKey] & 0x80) ? true: false;
}


// �擾 : �h���N�G�I�ȃA��
bool Input::GetMouseRepeat(int nKey)
{
	return (m_diMouseStateRepeat.rgbButtons[nKey] & 0x80) ? true : false;
}


// �擾 : 2��A���ŉ����ꂽ�u�Ԃ̂�
bool Input::GetMouseWTrigger(int nKey)
{
	return (m_diMouseStateWTrigger.rgbButtons[nKey] & 0x80) ? true : false;
}

#endif



#ifdef _USE_JOYSTICK
//=============================================================================
// �W���C�X�e�B�b�N
// ������
HRESULT Input::InitJoystick(HINSTANCE hInstance, HWND hWnd)
{
	// �e�l0�N���A
	ZeroMemory(&m_diJoystickState,sizeof(m_diJoystickState));
	ZeroMemory(&m_diJoystickStateTrigger,sizeof(m_diJoystickStateTrigger));
	ZeroMemory(&m_diJoystickStateRelease,sizeof(m_diJoystickStateRelease));
	ZeroMemory(&m_diJoystickStateRepeat,sizeof(m_diJoystickStateRepeat));
	ZeroMemory(&m_diJoystickStateWTrigger, sizeof(m_diJoystickStateWTrigger));

	for(int i = 0; i<NUM_JOYSTICK_MAX; i++)
	{
		m_diJoystickStateRepeatCnt[i] = 0;
		m_diJoystickStateWTriggerCnt[i] = 0;
	}


	// �f�o�C�X�̍쐬
	if (FAILED(m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY)))
	{
		MessageBox(hWnd, "�W���C�X�e�B�b�N�̔��ʂ��ł��܂���ł���", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}
	
	// �ڑ��m�F
	if(m_pDevJoystick == NULL)
	{
		// �W���C�X�e�B�b�N�̐ڑ��t���O�ݒ�
		m_bConnectJoystick = false;
		//MessageBox(hWnd,"�W���C�X�e�B�b�N�̐ڑ����m�F�ł��܂���ł���\n"
		//				"�W���C�X�e�B�b�N���g�p�������ꍇ�͈�x�Q�[�����I�����A�ڑ����Ă���ĂыN���������Ă�������", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}
	else
	{
		// �W���C�X�e�B�b�N�̐ڑ��t���O�ݒ�
		m_bConnectJoystick = true;
	}

	// ���͈̔͐ݒ�
	if(FAILED(m_pDevJoystick->EnumObjects( EnumAxesCallback, NULL, DIDFT_AXIS )))
	{
		MessageBox(hWnd, "�W���C�X�e�B�b�N�̓��͒l�̐ݒ肪�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if(FAILED(m_pDevJoystick->SetDataFormat(&c_dfDIJoystick2)))
	{
		MessageBox(hWnd, "�W���C�X�e�B�b�N�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if(FAILED(m_pDevJoystick->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�W���C�X�e�B�b�N�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �o�b�t�@�[�T�C�Y�̐ݒ�
	DIPROPDWORD	dipdwJoystick;
	dipdwJoystick.diph.dwSize		= sizeof(dipdwJoystick);
	dipdwJoystick.diph.dwHeaderSize = sizeof(dipdwJoystick.diph);
	dipdwJoystick.diph.dwObj		= 0;
	dipdwJoystick.diph.dwHow		= DIPH_DEVICE;
	dipdwJoystick.dwData			= 100;

	if(FAILED(m_pDevJoystick->SetProperty(DIPROP_BUFFERSIZE,&dipdwJoystick.diph)))
	{
		MessageBox(hWnd, "�W���C�X�e�B�b�N�̃o�b�t�@�[�T�C�Y��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �W���C�X�e�B�b�N�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevJoystick->Acquire();

	return S_OK;
}


// �I��
void Input::UninitJoystick(void)
{
	if(m_pDevJoystick != NULL)
	{// ���̓f�o�C�X�̊J��
		// �W���C�X�e�B�b�N�ւ̃A�N�Z�X�����J��(���͐���I��)
		m_pDevJoystick->Unacquire();

		m_pDevJoystick->Release();
		m_pDevJoystick = NULL;
	}
}


// �X�V
void Input::UpdateJoystick(void)
{
	// ���ڑ��ōX�V��������
	if (!m_bConnectJoystick) return;

	DIJOYSTATE2 diJoystickState;

	// �f�o�C�X�ɒl�̎擾������ʒm
	m_pDevJoystick->Poll();

	// �f�o�C�X�̒l���擾
	if(SUCCEEDED(m_pDevJoystick->GetDeviceState( sizeof(DIJOYSTATE2), &diJoystickState )))
	{
		for(int nCnKey = 0; nCnKey < NUM_JOYSTICK_MAX; nCnKey++)
		{
			// �{�^���̃g���K�[���̐���
			m_diJoystickStateTrigger.rgbButtons[nCnKey] =
				(m_diJoystickState.rgbButtons[nCnKey] ^ diJoystickState.rgbButtons[nCnKey]) & diJoystickState.rgbButtons[nCnKey];

			// �{�^���̃����[�X���̐���
			m_diJoystickStateRelease.rgbButtons[nCnKey] =
				(m_diJoystickState.rgbButtons[nCnKey] ^ diJoystickState.rgbButtons[nCnKey]) & m_diJoystickState.rgbButtons[nCnKey];

			// �{�^���̃��s�[�g���̐���
			if(diJoystickState.rgbButtons[nCnKey])
			{
				if(m_diJoystickStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					m_diJoystickStateRepeatCnt[nCnKey]++;

					if(m_diJoystickStateRepeatCnt[nCnKey] == 1 || m_diJoystickStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{
						m_diJoystickStateRepeat.rgbButtons[nCnKey] = diJoystickState.rgbButtons[nCnKey];
					}
					else
					{
						m_diJoystickStateRepeat.rgbButtons[nCnKey] = 0;
					}
				}
			}
			else{
				m_diJoystickStateRepeat.rgbButtons[nCnKey] = 0;
				m_diJoystickStateRepeatCnt[nCnKey] = 0;
			}

			//----- �{�^���̃_�u���g���K�[���̐��� -----
			// �J�E���^�[����Ă�H
			if (m_diJoystickStateWTriggerCnt[nCnKey]) {
				m_diJoystickStateWTriggerCnt[nCnKey]++;

				// ������x�g���K�[�������ꂽ��_�u���g���K�[�Ƃ��Ĕ��肷��
				if (m_diJoystickStateTrigger.rgbButtons[nCnKey]) {
					m_diJoystickStateWTrigger.rgbButtons[nCnKey] = diJoystickState.rgbButtons[nCnKey];

					m_diJoystickStateWTriggerCnt[nCnKey] = 0;
				}

				// �J�E���^�[��臒l����������t���O���~�낷
				if (m_diJoystickStateWTriggerCnt[nCnKey] >= LIMIT_COUNT_WTRIGGER) {
					m_diJoystickStateWTriggerCnt[nCnKey] = 0;
				}

			}
			// �g���K�[�������ꂽ��J�E���^�[���񂵎n�߂�
			else if (m_diJoystickStateTrigger.rgbButtons[nCnKey]) m_diJoystickStateWTriggerCnt[nCnKey]++;
			else m_diJoystickStateWTrigger.rgbButtons[nCnKey] = 0;


			// �{�^���̃v���X����ۑ�
			m_diJoystickState.rgbButtons[nCnKey] = diJoystickState.rgbButtons[nCnKey];
		}
	}
	else
	{
		// �W���C�X�e�B�b�N�ւ̃A�N�Z�X�����擾
		m_pDevJoystick->Acquire();
	}

}


// �擾 : ���X�e�B�b�N�̌X��
D3DXVECTOR2 Input::GetJoystickLeftAxis(void)
{
	if(m_bConnectJoystick == true)
	{
		DIJOYSTATE2 DevJoystick;

		m_pDevJoystick->GetDeviceState( sizeof(DIJOYSTATE2), &DevJoystick );

		return D3DXVECTOR2( (float)DevJoystick.lX, (float)DevJoystick.lY );
	}

	return D3DXVECTOR2(0,0);

}


// �擾 : �E�X�e�B�b�N�̌X��
D3DXVECTOR2 Input::GetJoystickRightAxis(void)
{
	if(m_bConnectJoystick == true)
	{
		DIJOYSTATE2 DevJoystick;

		m_pDevJoystick->GetDeviceState( sizeof(DIJOYSTATE2), &DevJoystick );

		return D3DXVECTOR2( (float)DevJoystick.lZ, (float)DevJoystick.lRz );
	}

	return D3DXVECTOR2(0,0);
}


// �擾 : �����Ă��邩
bool Input::GetJoystickPress(int nKey)
{
	return (m_diJoystickState.rgbButtons[nKey] & 0x80) ? true: false;
	//return (m_diJoystickState.rgbButtons[nKey] & 0x01) ? true: false;	// �O�̃t���[���ŉ����ꂽ�L�[���擾
}


// �擾 : �������u�Ԃ�
bool Input::GetJoystickTrigger(int nKey)
{
	return (m_diJoystickStateTrigger.rgbButtons[nKey] & 0x80) ? true: false;
}


// �擾 : �������u�Ԃ�
bool Input::GetJoystickRelease(int nKey)
{
	return (m_diJoystickStateRelease.rgbButtons[nKey] & 0x80) ? true : false;
}


// �擾 : �h���N�G�I�ȃA��
bool Input::GetJoystickRepeat(int nKey)
{
	return (m_diJoystickStateRepeat.rgbButtons[nKey] & 0x80) ? true: false;
}


// �擾 : 2��A���ŉ����ꂽ�u�Ԃ̂�
bool Input::GetJoystickWTrigger(int nKey)
{
	return (m_diJoystickStateWTrigger.rgbButtons[nKey] & 0x80) ? true : false;

}


// �ڑ�����Ă���W���C�X�e�B�b�N�̔���
BOOL CALLBACK Input::EnumJoysticksCallback(const DIDEVICEINSTANCE* pDevInstance, LPVOID lpContext )
{
	UNREFERENCED_PARAMETER(pDevInstance);
	UNREFERENCED_PARAMETER(lpContext);

	// �񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾
	if(FAILED(m_pInput->CreateDevice(pDevInstance->guidInstance, &m_pDevJoystick, NULL)))
	{
		MessageBox(NULL, "�W���C�X�e�B�b�N�̐ڑ����m�F�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return DIENUM_CONTINUE;
	}
	
	// �W���C�X�e�B�b�N�̔\�͂��擾
	m_diJoystickCaps.dwSize = sizeof(DIDEVCAPS);
	if(FAILED(m_pDevJoystick->GetCapabilities(&m_diJoystickCaps)))
	{
		// �W���C�X�e�B�b�N�\�͂̎擾�Ɏ��s
		MessageBox(NULL, "�W���C�X�e�B�b�N�̔\�͂̎擾���ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		UninitJoystick();
		return DIENUM_CONTINUE;
	}
	
	return DIENUM_STOP;
}


// �X�e�B�b�N�̊e���̐ݒ�
BOOL CALLBACK Input::EnumAxesCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID lpvRef )
{
	// ���̒l�͈̔͂�ݒ�i-1000�`1000�j
	DIPROPRANGE diprg;
	ZeroMemory( &diprg, sizeof(diprg) );
	diprg.diph.dwSize       = sizeof(diprg); 
	diprg.diph.dwHeaderSize = sizeof(diprg.diph); 
	diprg.diph.dwObj        = lpddoi->dwType;
	diprg.diph.dwHow        = DIPH_BYID;
	diprg.lMin              = -1000;
	diprg.lMax              = +1000;

	// �ݒ�l���W���C�X�e�B�b�N�f�o�C�X�֔��f
	if(FAILED(m_pDevJoystick->SetProperty( DIPROP_RANGE, &diprg.diph )))
	{
		MessageBox(NULL, "�擾�����W���C�X�e�B�b�N�ɒl��ݒ肷�邱�Ƃ��ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return DIENUM_STOP;
	}
	
	return DIENUM_CONTINUE;
}

#endif


