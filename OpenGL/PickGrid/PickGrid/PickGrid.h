// PickGrid.h : PickGrid アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// CPickGridApp:
// このクラスの実装については、PickGrid.cpp を参照してください。
//

class CPickGridApp : public CWinApp
{
public:
	CPickGridApp();


// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPickGridApp theApp;