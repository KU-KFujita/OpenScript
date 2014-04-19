// PickGridDoc.cpp : CPickGridDoc クラスの実装
//

#include "stdafx.h"
#include "PickGrid.h"

#include "PickGridDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPickGridDoc

IMPLEMENT_DYNCREATE(CPickGridDoc, CDocument)

BEGIN_MESSAGE_MAP(CPickGridDoc, CDocument)
END_MESSAGE_MAP()


// CPickGridDoc コンストラクション/デストラクション

CPickGridDoc::CPickGridDoc()
{
	// TODO: この位置に 1 度だけ呼ばれる構築用のコードを追加してください。

}

CPickGridDoc::~CPickGridDoc()
{
}

BOOL CPickGridDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}




// CPickGridDoc シリアル化

void CPickGridDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 格納するコードをここに追加してください。
	}
	else
	{
		// TODO: 読み込むコードをここに追加してください。
	}
}


// CPickGridDoc 診断

#ifdef _DEBUG
void CPickGridDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPickGridDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPickGridDoc コマンド
