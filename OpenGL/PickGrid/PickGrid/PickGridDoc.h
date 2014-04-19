// PickGridDoc.h : CPickGridDoc クラスのインターフェイス
//


#pragma once


class CPickGridDoc : public CDocument
{
protected: // シリアル化からのみ作成します。
	CPickGridDoc();
	DECLARE_DYNCREATE(CPickGridDoc)

// 属性
public:

// 操作
public:

// オーバーライド
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 実装
public:
	virtual ~CPickGridDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
};


