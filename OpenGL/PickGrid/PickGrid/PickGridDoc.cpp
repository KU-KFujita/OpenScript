// PickGridDoc.cpp : CPickGridDoc �N���X�̎���
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


// CPickGridDoc �R���X�g���N�V����/�f�X�g���N�V����

CPickGridDoc::CPickGridDoc()
{
	// TODO: ���̈ʒu�� 1 �x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CPickGridDoc::~CPickGridDoc()
{
}

BOOL CPickGridDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}




// CPickGridDoc �V���A����

void CPickGridDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �i�[����R�[�h�������ɒǉ����Ă��������B
	}
	else
	{
		// TODO: �ǂݍ��ރR�[�h�������ɒǉ����Ă��������B
	}
}


// CPickGridDoc �f�f

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


// CPickGridDoc �R�}���h
