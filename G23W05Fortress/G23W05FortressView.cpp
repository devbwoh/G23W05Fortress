
// G23W05FortressView.cpp: CG23W05FortressView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "G23W05Fortress.h"
#endif

#include "G23W05FortressDoc.h"
#include "G23W05FortressView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CG23W05FortressView

IMPLEMENT_DYNCREATE(CG23W05FortressView, CView)

BEGIN_MESSAGE_MAP(CG23W05FortressView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_FIRE, &CG23W05FortressView::OnFire)
END_MESSAGE_MAP()

// CG23W05FortressView 생성/소멸

CG23W05FortressView::CG23W05FortressView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CG23W05FortressView::~CG23W05FortressView()
{
}

BOOL CG23W05FortressView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CG23W05FortressView 그리기

#define GROUND	50
#define TARGET_SIZE	100

void CG23W05FortressView::OnDraw(CDC* pDC)
{
	CG23W05FortressDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	DrawBackground(pDC);
}

void CG23W05FortressView::OnFire()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//MessageBox(L"발사");
	int x = 0, y = 0;
	CG23W05FortressDoc* pDoc = GetDocument();

	int a = pDoc->GetAngle();
	int p = pDoc->GetPower();

	CRect rect;
	GetClientRect(&rect);

	CClientDC dc(this);

	//dc.Ellipse(100, 100, 300, 300);

	for (int t = 0; t < 100; t++) {
		CalculateCoordinate(a, p, t, &x, &y);
		y = rect.bottom - y - GROUND;
		if (y > rect.bottom - GROUND)
			break;

		dc.Ellipse(x - 30, y - 30, x + 30, y + 30);
		Sleep(50);

		dc.FillSolidRect(rect, RGB(255, 255, 255));
		DrawBackground(&dc);
	}
}


void CG23W05FortressView::CalculateCoordinate(int angle, int power, int t, int* x, int* y)
{
	const double g = 9.8;
	const double pi = 3.141592;

	double theta = angle * pi / 180.;
	double v0 = (double)power;

	*x = (int)(v0 * t * cos(theta));
	*y = (int)(v0 * t * sin(theta) - g * t * t / 2.);
}

void CG23W05FortressView::DrawBackground(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->MoveTo(rect.left, rect.bottom - GROUND);
	pDC->LineTo(rect.right, rect.bottom - GROUND);

	CG23W05FortressDoc* pDoc = GetDocument();

	CString str;
	str.Format(L"Angle = %d, Power = %d", pDoc->GetAngle(), pDoc->GetPower());
	pDC->TextOutW(10, 10, str);

	// Target
	int target = pDoc->GetTarget();
	pDC->Rectangle(target - TARGET_SIZE / 2, rect.bottom - GROUND - TARGET_SIZE,
		target + TARGET_SIZE / 2, rect.bottom - GROUND);
}

// CG23W05FortressView 인쇄

BOOL CG23W05FortressView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CG23W05FortressView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CG23W05FortressView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CG23W05FortressView 진단

#ifdef _DEBUG
void CG23W05FortressView::AssertValid() const
{
	CView::AssertValid();
}

void CG23W05FortressView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CG23W05FortressDoc* CG23W05FortressView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CG23W05FortressDoc)));
	return (CG23W05FortressDoc*)m_pDocument;
}
#endif //_DEBUG


// CG23W05FortressView 메시지 처리기

