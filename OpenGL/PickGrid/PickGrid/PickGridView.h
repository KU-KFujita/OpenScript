// PickGridView.h : CPickGridView クラスのインターフェイス
//


#pragma once

#include <gl/gl.h>
#include <gl/glu.h>

#define BUFSIZE 512

class CPickGridView : public CView
{
protected: // シリアル化からのみ作成します。
	CPickGridView();
	DECLARE_DYNCREATE(CPickGridView)

// 属性
public:
	CPickGridDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 実装
public:
	virtual ~CPickGridView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HGLRC m_hGLRC;
	UINT_PTR m_timerID;
	int m_iNumVertex;
	GLfloat (*m_vertices)[3];
	int m_iNumLine;
	int (*m_ivLine)[2];
	GLuint m_iPickedIDV;
	double m_dPickedZdepth;
	bool m_bPicking;
	CPoint m_prevPoint;

private:
	bool InitializeOpenGL();
	void InitializeModel(int numGrid);
	void SetModelViewMatrix();
	void DrawModel(GLenum mode);
	void PickVertex(int x, int y);
	void ParseSelectBuf(GLint hits, GLuint buffer[], GLuint* pidv, double* pzdepth);
	double CalibratePickingPoint(double ox0[], double ox1[], double ox2[], double dv[]);
	double DotVec3(double vec1[], double vec2[]);
	void AddVec3(double vec1[], double vec2[], double a, double vec[]);

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // PickGridView.cpp のデバッグ バージョン
inline CPickGridDoc* CPickGridView::GetDocument() const
   { return reinterpret_cast<CPickGridDoc*>(m_pDocument); }
#endif

