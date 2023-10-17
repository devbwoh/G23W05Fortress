
// G23W05FortressView.h: CG23W05FortressView 클래스의 인터페이스
//

#pragma once

#define GROUND		50
#define BOMB_RADIUS	30
#define TARGET_SIZE	100

class CG23W05FortressView : public CView
{
protected: // serialization에서만 만들어집니다.
	CG23W05FortressView() noexcept;
	DECLARE_DYNCREATE(CG23W05FortressView)

// 특성입니다.
public:
	CG23W05FortressDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CG23W05FortressView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFire();
	void CalculateCoordinate(int angle, int power, int t, int* x, int* y);
	void DrawBackground(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // G23W05FortressView.cpp의 디버그 버전
inline CG23W05FortressDoc* CG23W05FortressView::GetDocument() const
   { return reinterpret_cast<CG23W05FortressDoc*>(m_pDocument); }
#endif

