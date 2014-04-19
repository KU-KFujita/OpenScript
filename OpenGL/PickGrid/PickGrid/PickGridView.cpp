// PickGridView.cpp : CPickGridView クラスの実装
//

#include "stdafx.h"
#include "PickGrid.h"

#include "PickGridDoc.h"
#include "PickGridView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// CPickGridView

IMPLEMENT_DYNCREATE(CPickGridView, CView)

BEGIN_MESSAGE_MAP(CPickGridView, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CPickGridView コンストラクション/デストラクション

CPickGridView::CPickGridView()
{
	// TODO: 構築コードをここに追加します。
	m_iPickedIDV = -1;
	m_bPicking = false;
	m_timerID = 0;
}

CPickGridView::~CPickGridView()
{
}

BOOL CPickGridView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	return CView::PreCreateWindow(cs);
}

// CPickGridView 描画

void CPickGridView::OnDraw(CDC* /*pDC*/)
{
	CPickGridDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}


// CPickGridView 印刷

BOOL CPickGridView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CPickGridView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CPickGridView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}


// CPickGridView 診断

#ifdef _DEBUG
void CPickGridView::AssertValid() const
{
	CView::AssertValid();
}

void CPickGridView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPickGridDoc* CPickGridView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPickGridDoc)));
	return (CPickGridDoc*)m_pDocument;
}
#endif //_DEBUG


// CPickGridView メッセージ ハンドラ

int CPickGridView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ここに特定な作成コードを追加してください。
	InitializeOpenGL();
	InitializeModel(4);
	m_timerID = SetTimer(1, 26, NULL);

	return 0;
}

void CPickGridView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: ここにメッセージ ハンドラ コードを追加します。
	KillTimer(m_timerID);
	CClientDC dc(this);
	::wglMakeCurrent(dc.GetSafeHdc(), m_hGLRC);
	::wglMakeCurrent(NULL, NULL);
	
	if (m_hGLRC != NULL) {
		::wglDeleteContext(m_hGLRC);
	}
	free(m_vertices);
}

void CPickGridView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ここにメッセージ ハンドラ コードを追加します。
	// コンテキスト設定
	CClientDC dc(this);
	::wglMakeCurrent(dc.GetSafeHdc(), m_hGLRC);
	::glEnable(GL_DEPTH_TEST);

	::glViewport(0, 0, cx, cy);

	// 透視変換
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPerspective(45.0, (double)cx / (double)cy, 0.1, 100.0);

	// 投影変換
	SetModelViewMatrix();

	// 後処理
	::wglMakeCurrent(NULL, NULL);

}

void CPickGridView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	PickVertex(point.x, point.y);
	if (m_iPickedIDV>=0)
	{
		m_bPicking = true;
		m_prevPoint = point;
		SetCapture();
	}
	CView::OnLButtonDown(nFlags, point);
}

void CPickGridView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	if (m_bPicking)
	{
		m_bPicking = false;
		m_iPickedIDV = -1;
		::ReleaseCapture();
	}
	CView::OnLButtonUp(nFlags, point);
}

bool CPickGridView::InitializeOpenGL()
{
    static PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
        PFD_TYPE_RGBA,
        24,
        0, 0, 0,
		0, 0, 0,
        0, 0,
        0, 0, 0, 0, 0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

	CClientDC dc(this);

    int pfdID = ::ChoosePixelFormat(dc.GetSafeHdc(), &pfd);
	if (pfdID == 0) {
        return false;
    }

	BOOL bResult = ::SetPixelFormat(dc.GetSafeHdc(), pfdID, &pfd);
	if (bResult == false) {
        return false;
	}

	m_hGLRC = ::wglCreateContext(dc.GetSafeHdc());
	if (m_hGLRC == NULL) {
		return false;
	}

	::wglMakeCurrent(dc.GetSafeHdc(), m_hGLRC);
	return true;
}

void CPickGridView::SetModelViewMatrix()
{
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::gluLookAt(1.5, -3.0, 1.5, 1.5, 1.5, 0.0, 0.0, 0.0, 1.0);
}

void CPickGridView::InitializeModel(int numGrid)
{
	// 頂点の座標値セット
	m_iNumVertex = numGrid*numGrid;
	m_vertices =(GLfloat(*)[3])malloc(m_iNumVertex*3*sizeof(GLfloat));
	int i,j,k;
	k = 0;
	for(i=0; i<numGrid; i++) {
		for(j=0;j<numGrid;j++) {
			m_vertices[k][0] = (GLfloat) j;
			m_vertices[k][1] = (GLfloat) i;
			m_vertices[k][2] = 0.0f;
			k = k+1;
		}
	}

	// 線分を構成する頂点番号セット
	m_iNumLine = numGrid*(numGrid-1)*2;
	m_ivLine =(int(*)[2])malloc(m_iNumLine*2*sizeof(int));
	k = 0;
	for(i=0; i<numGrid; i++) {
		for(j=0;j<numGrid-1;j++) {
			m_ivLine[k][0] = i*numGrid+j;
			m_ivLine[k][1] = i*numGrid+j+1;
			k = k+1;
		}
	}
	for(i=0; i<numGrid-1; i++) {
		for(j=0;j<numGrid;j++) {
			m_ivLine[k][0] = i*numGrid+j;
			m_ivLine[k][1] = (i+1)*numGrid+j;
			k = k+1;
		}
	}
}

void CPickGridView::DrawModel(GLenum mode)
{
	// 頂点描画
	::glPointSize(5.0f);
	::glColor3f(1.0f, 1.0f, 0.0f);
	for(int i=0;i<m_iNumVertex;i++) {
		if (mode==GL_SELECT) ::glLoadName(i);
		if (i==m_iPickedIDV) ::glColor3f(1.0f, 0.0f, 0.0f);
		::glBegin(GL_POINTS);
			::glVertex3fv(m_vertices[i]);
		::glEnd();
		if (i==m_iPickedIDV) ::glColor3f(1.0f, 1.0f, 0.0f);
	}

	// 線分はオブジェクト選択対象外
	if (mode==GL_SELECT) return;

	// 線分描画
	::glColor3f(0.0f, 0.0f, 1.0f);
	for(int i=0;i<m_iNumLine;i++) {
		::glBegin(GL_LINES);
			::glVertex3fv(m_vertices[m_ivLine[i][0]]);
			::glVertex3fv(m_vertices[m_ivLine[i][1]]);
		::glEnd();
	}
}

void CPickGridView::PickVertex(int x, int y)
{
	GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];

	// コンテキスト設定
	CClientDC dc(this);
	::wglMakeCurrent(dc.GetSafeHdc(), m_hGLRC);
	::glEnable(GL_DEPTH_TEST);

	// オブジェクト選択の前処理
	::glGetIntegerv (GL_VIEWPORT, viewport);
	::glSelectBuffer(BUFSIZE, selectBuf);
	(void) ::glRenderMode(GL_SELECT);
	::glInitNames();
	::glPushName(0);

	// オブジェクト選択用の透視変換処理
	::glMatrixMode(GL_PROJECTION);
	::glPushMatrix();
	::glLoadIdentity();
	::gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3]-y),
		10.0, 10.0, viewport);
	::gluPerspective(45.0, (double)viewport[2] / (double)viewport[3], 
		0.1, 100.0);

	// オブジェクト選択用の投影変換処理
	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();

	// オブジェクト選択
	DrawModel(GL_SELECT);
	hits = glRenderMode(GL_RENDER);
	ParseSelectBuf(hits, selectBuf, &m_iPickedIDV, &m_dPickedZdepth);

	// 透視変換復元
	::glMatrixMode(GL_PROJECTION);
	::glPopName();
	::glPopMatrix();

	// 投影変換復元
	::glMatrixMode(GL_MODELVIEW);
	::glPopMatrix();

	// 後処理
	::wglMakeCurrent(NULL, NULL);
}

void CPickGridView::ParseSelectBuf(GLint hits, GLuint buffer[], 
									 GLuint* pidv, double* pzdepth)
{
    int i, j;
    GLuint names, *ptr, name;
	GLuint z1, z2;

	// 初期化
	*pzdepth = 0;
	*pidv = -1;
    ptr = (GLuint *) buffer;

	// バッファ読み出し
    for (i = 0; i < hits; i++) {
        names = *ptr; ptr++;	// 頂点数
        z1 = *ptr; ptr++;		// 最大デプス
        z2 = *ptr; ptr++;		// 最小デプス
		if (z2<=*pzdepth || i==0) {
			*pzdepth = (double) z2/0xffffffff;	// デプス計算
			*pidv = *ptr;		// 頂点番号
		}
        for (j=0; j<names; j++) {
            name = *ptr; ptr++;
        }
    }
}

void CPickGridView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	// コンテキスト設定
	CClientDC dc(this);
	::wglMakeCurrent(dc.GetSafeHdc(), m_hGLRC);
	::glEnable(GL_DEPTH_TEST);

	// 背景描画
	::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// モデル描画
	DrawModel(GL_RENDER);
	::glFlush();
	::SwapBuffers(dc.GetSafeHdc());

	// 後処理
	::wglMakeCurrent(NULL, NULL);

	CView::OnTimer(nIDEvent);
}

void CPickGridView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	CView::OnMouseMove(nFlags, point);
	CRect rect;
	GetClientRect(&rect);
	if (!rect.PtInRect(point)) {
		// 頂点選択解除
		m_bPicking = false;
		m_iPickedIDV = -1;
		::ReleaseCapture();
	}
	if (m_bPicking && m_iPickedIDV>=0){

		// コンテキスト取得
		CClientDC dc(this);
		::wglMakeCurrent(dc.GetSafeHdc(), m_hGLRC);

		// 投影透視変換取得
		GLdouble model[16], proj[16];
		GLint viewport[4];
		GLdouble ox0[3], ox1[3], ox2[3];
		GLdouble dv[3] = {0.0, 0.0, 1.0};
		glGetDoublev(GL_MODELVIEW_MATRIX, model);
		glGetDoublev(GL_PROJECTION_MATRIX, proj);
		glGetIntegerv(GL_VIEWPORT, viewport);

		// 投影透視の逆変換
		gluUnProject(point.x, viewport[3] - point.y, m_dPickedZdepth, 
			model, proj, viewport, &ox1[0], &ox1[1], &ox1[2]);

		/*
		// 頂点移動 補正しない場合
		m_vertices[m_iPickedIDV][2] = (GLfloat) ox1[2];
		*/

		// 補正する場合（不要なら削除）
		gluUnProject(point.x, viewport[3] - point.y, 0.0, 
			model, proj, viewport, &ox2[0], &ox2[1], &ox2[2]);
		ox0[0] = (double) m_vertices[m_iPickedIDV][0];
		ox0[1] = (double) m_vertices[m_iPickedIDV][1];
		ox0[2] = (double) m_vertices[m_iPickedIDV][2];
		double alfa = CalibratePickingPoint(ox0, ox1, ox2, dv);

		// 頂点移動
		m_vertices[m_iPickedIDV][2] = (GLfloat) ox0[2]+alfa*dv[2];

		// 後処理
		::wglMakeCurrent(NULL, NULL);
	}

}

double CPickGridView::CalibratePickingPoint(double ox0[], double ox1[], 
										   double ox2[], double dv[]){
	double x02[3], x12[3];
	double alfa;

	AddVec3(ox0, ox2, -1.0, x02);
	AddVec3(ox1, ox2, -1.0, x12);

	alfa = (DotVec3(x12,x02)/DotVec3(x12, x12)-DotVec3(dv,x02)/DotVec3(dv,x12))
		/(DotVec3(dv, dv)/DotVec3(dv,x12)-DotVec3(dv,x12)/DotVec3(x12, x12));

	return alfa;
}

double CPickGridView::DotVec3(double vec1[], double vec2[]){
	return vec1[0]*vec2[0]+vec1[1]*vec2[1]+vec1[2]*vec2[2];
}

void CPickGridView::AddVec3(double vec1[], double vec2[], 
							  double a, double vec[]){
	vec[0] = vec1[0]+a*vec2[0];
	vec[1] = vec1[1]+a*vec2[1];
	vec[2] = vec1[2]+a*vec2[2];
}
