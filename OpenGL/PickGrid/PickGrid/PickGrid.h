// PickGrid.h : PickGrid �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��


// CPickGridApp:
// ���̃N���X�̎����ɂ��ẮAPickGrid.cpp ���Q�Ƃ��Ă��������B
//

class CPickGridApp : public CWinApp
{
public:
	CPickGridApp();


// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPickGridApp theApp;